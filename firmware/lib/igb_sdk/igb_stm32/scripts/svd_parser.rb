# vim:set fileencoding=utf-8

require 'rexml/document'
require 'set'
require 'erb'
require 'pathname'

require_relative '_schema'
require_relative '_name_config'

# 覚環境に応じたDeviceInfo 構造体のコードを生成する。
# また、各機能が有効かどうか判定するためのマクロを自動生成する
class SVDParser
  def initialize(filename)
    @filename = filename

    # ペリフェラルをグループごとにざっくり分割
    @parsed = {}

    @cpp_structs = {}
  end

  def debug(text)
    puts text
  end

  def parse
    open(@filename) do |file|
      @doc = REXML::Document.new(file)
      REXML::XPath.match(@doc, "/device/peripherals/peripheral").each do |peripheral|
#         debug "[peripheral] name = #{peripheral.elements['name'].text}"
        scan_peripheral(peripheral)
        REXML::XPath.match(peripheral, "registers/register").each do |register|
          #debug "[register] name = #{register.elements['name']}"
          scan_register(peripheral, register)
        end
      end

      gen_structs
    end
  end

  # TODO: ペリフェラルの定義から対応するハッシュマップを構築
  def scan_peripheral(peripheral)
    parent_doc_name = peripheral.attribute("derivedFrom")&.value
    parent_doc = if parent_doc_name
      REXML::XPath.first(@doc, "/device/peripherals/peripheral/name[text()='#{parent_doc_name}']/parent::peripheral")
    end
    #debug "parent - #{parent_doc.elements['name'].text}" if parent_doc
    peripheral_name = peripheral.elements['name'].text
    group_name = peripheral.elements['groupName']&.text || parent_doc&.elements['groupName']&.text || peripheral_name

    peripheral_name = fix_ambiguous_peripheral_name(peripheral_name)

    debug "[#{group_name}] #{peripheral_name}"

    @parsed[group_name] ||= {}
    @parsed[group_name][peripheral_name] ||= {}

    if parent_doc
      parent_doc.elements.each do |elem|
        if elem.text && elem.text.size > 0
          @parsed[group_name][peripheral_name][elem.name.to_sym] = elem.text
        end
      end
    end
    peripheral.elements.each do |elem|
      if elem.text && elem.text.size > 0
        @parsed[group_name][peripheral_name][elem.name.to_sym] = elem.text
      end
    end
  end

  # 表記揺れの補正
  def fix_ambiguous_peripheral_name(name)
    case name.to_s
    when 'ADC'
      'ADC1'
    else
      name
    end
  end

  def scan_register(peripheral, register)
  end

  def gen_structs
    @parsed.each do |group_name, group|
      @cpp_structs[group_name] ||= []

      @parsed[group_name].keys.sort_by {|k|
        if k.to_s =~ /\d+\z/
          k.to_s.gsub(/\D/, '').to_i
        else
          k
        end
      }.each do |peripheral_name|
        struct = CppStructSchema.create(group_name)
        case group_name.to_sym
        when :GPIO
          struct[:attrs][:p_gpio][:value] = peripheral_name
          @cpp_structs[group_name] << struct
        when :TIM
          struct[:attrs][:p_tim][:value] = peripheral_name
          description = @parsed[group_name][peripheral_name][:description]
          if description =~ /\AAdvanced/
            struct[:attrs][:type][:value] = 'TIMType::ADVANCED'
          elsif description =~ /\AGeneral/
            struct[:attrs][:type][:value] = 'TIMType::GENERAL'
          elsif description =~ /\ABasic/
            struct[:attrs][:type][:value] = 'TIMType::BASIC'
          else
            #struct[:attrs][:type][:value] = 'TIMType::UNKNOWN'
            raise "Unknown Timer [description=#{description}]"
          end
          @cpp_structs[group_name] << struct
        when :RCC
          struct[:attrs][:p_rcc][:value] = peripheral_name
          @cpp_structs[group_name] << struct
        when :I2C
          struct[:attrs][:p_i2c][:value] = peripheral_name
          @cpp_structs[group_name] << struct
        when :SPI
          struct[:attrs][:p_spi][:value] = peripheral_name
          @cpp_structs[group_name] << struct
        when :USART
          struct[:attrs][:p_usart][:value] = peripheral_name
          @cpp_structs[group_name] << struct
        when :ADC
          struct[:attrs][:p_adc][:value] = peripheral_name
          @cpp_structs[group_name] << struct
        when :DAC
          struct[:attrs][:p_dac][:value] = peripheral_name
          @cpp_structs[group_name] << struct
        end
      end
    end
  end

  def gen_mcu_header_file
    file_symbol = Pathname.new(@filename).basename('.svd').to_s
    include_guard_name = "IGB_STM32_DEVICE_SVD_#{file_symbol.upcase}_H"
    header_file_name = "#{file_symbol}.hpp".downcase
    schema = CppStructSchema::SCHEMA
    open(Pathname.new(__dir__).join('..', 'base', 'svd', header_file_name), 'w') do |hpp_file|
      open(Pathname.new(__dir__).join('_peripheral_tmpl.hpp.erb')) do |erb_file|
        erb = ERB.new(erb_file.read, trim_mode: "<>")
        hpp_file.print erb.result(binding)
      end
    end
  end

end

def get_periheral_names
  peripheral_names = Set.new
  
  # fetch group name (= peripheral name)
  Dir["#{__dir__}/../svd/*.svd"].each do |svd_file_name|
  #Dir["#{__dir__}/svd/STM32F072x.svd"].each do |svd_file_name|
    puts "svd_file_name = #{svd_file_name}"
    open(svd_file_name) do |file|
      doc = REXML::Document.new(file)
      peripheral_names += REXML::XPath.match(doc, "/device/peripherals/peripheral").map {|peripheral|
        peripheral.elements['groupName']&.text # || peripheral.elements['name']&.text
      }.compact
    end
  end
  peripheral_names
end

def process_all_svd
  #Dir["#{__dir__}/svd/*.svd"].each do |svd_file_name|
  Dir["#{__dir__}/../svd/STM32F072x.svd"].each do |svd_file_name|
    parser = SVDParser.new(svd_file_name)
    parser.parse
    parser.gen_mcu_header_file
  end

#   NameConfig.available_mcu.each do |mcu|
    mcu = :stm32f072xb
    mcu_header_name = "#{mcu.to_s.downcase}.hpp"
    svd_header_name = "#{NameConfig.mcu_to_svd(mcu).to_s.downcase}.hpp"
    include_guard_name = "IGB_STM32_DEVICE_MCU_#{mcu.to_s.upcase}_H"
    open(Pathname.new(__dir__).join('..', 'base', 'mcu', mcu_header_name), 'w') do |hpp_file|
      open(Pathname.new(__dir__).join('_mcu_tmpl.hpp.erb')) do |erb_file|
        erb = ERB.new(erb_file.read, trim_mode: "<>")
        hpp_file.print erb.result(binding)
      end
    end
#   end
end

if __FILE__ == $0
  #peripheral_names = get_periheral_names
  #puts "[peripheral names] #{peripheral_names}"

  process_all_svd
end
