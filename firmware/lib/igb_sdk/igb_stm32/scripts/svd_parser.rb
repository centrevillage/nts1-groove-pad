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

    @periph_to_group = {}

    @cpp_structs = {}
    @bus_names = Set.new
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
      end

      #pp @parsed

      gen_structs
      update_structs_for_bus_clock

      #@cpp_structs.delete_if { |group_name, structs| !structs || structs.empty? }

      #pp @cpp_structs
    end
  end

  # : ペリフェラルの定義から対応するハッシュマップを構築
  def scan_peripheral(peripheral)
    parent_doc_name = peripheral.attribute("derivedFrom")&.value
    # TODO: 毎回親ペリフェラルを検索するのは重いのでキャッシュする
    parent_doc = if parent_doc_name
      REXML::XPath.first(@doc, "/device/peripherals/peripheral/name[text()='#{parent_doc_name}']/parent::peripheral")
    end
    #debug "parent - #{parent_doc.elements['name'].text}" if parent_doc
    peripheral_name = peripheral.elements['name'].text
    group_name = peripheral.elements['groupName']&.text || parent_doc&.elements['groupName']&.text || peripheral_name

    peripheral_name = fix_ambiguous_peripheral_name(peripheral_name)

    debug "[#{group_name}] #{peripheral_name}"
    
    group_name = group_name.to_sym
    peripheral_name = peripheral_name.to_sym

    @parsed[group_name] ||= {}
    @parsed[group_name][peripheral_name] ||= {}

    @parsed[group_name][peripheral_name] = _scan_peripheral(parent_doc) if parent_doc
    @parsed[group_name][peripheral_name].update(_scan_peripheral(peripheral))

    @periph_to_group[peripheral_name] = group_name
  end

  def _scan_peripheral(peripheral)
    result = {}
    peripheral.elements.each do |elem|
      if elem.text && elem.text.size > 0
        result[elem.name.to_sym] = elem.text
      end
    end

    result[:addressBlock] = scan_address_block(peripheral.elements['addressBlock']) if peripheral.elements['addressBlock']

    result[:registers] = {}
    REXML::XPath.match(peripheral, "registers/register").each do |register|
      reg  = scan_register(register)
      result[:registers][reg[:name].to_sym] = reg
    end

    result[:interrupts] = {}
    REXML::XPath.match(peripheral, "interrupt").each do |interrupt|
      intr = scan_interrupt(interrupt)
      result[:interrupts][intr[:name]] = intr
    end

    result
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

  def scan_address_block(address_block)
    Hash[*(
      address_block.elements.flat_map {|elem|
        [elem.name.to_sym, elem.text]
      }
    )]
  end

  def scan_register(register)
    register_attrs = Hash[*(
      register.elements.select{|elem| elem&.text }.flat_map {|elem|
        [elem.name.to_sym, elem.text]
      }
    )]

    fields = []
    REXML::XPath.match(register, "fields/field").each do |field|
      fields << Hash[*(field.elements.flat_map {|elem| [elem.name.to_sym, elem&.text]})]
    end
    register_attrs[:fields] = fields

    return register_attrs
  end

  def scan_interrupt(interrupt)
    Hash[*(
      interrupt.elements.flat_map {|elem|
        [elem.name.to_sym, elem.text]
      }
    )]
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
        struct[:periph] = peripheral_name if struct
        case group_name.to_sym
        when :GPIO
          struct[:attrs][:p_gpio][:value] = peripheral_name
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
        when :RCC
          struct[:attrs][:p_rcc][:value] = peripheral_name
        when :I2C
          struct[:attrs][:p_i2c][:value] = peripheral_name
        when :SPI
          struct[:attrs][:p_spi][:value] = peripheral_name
        when :USART
          struct[:attrs][:p_usart][:value] = peripheral_name
        when :ADC
          struct[:attrs][:p_adc][:value] = peripheral_name
        when :DAC
          struct[:attrs][:p_dac][:value] = peripheral_name
        else
          next
        end
        @cpp_structs[group_name] << struct
      end
    end
  end

  BUSNAME_TO_PERIPHNAME = {
    IOPA: :GPIOA, IOPB: :GPIOB, IOPC: :GPIOC, IOPD: :GPIOD,
    IOPE: :GPIOE, IOPF: :GPIOF, IOPG: :GPIOG, IOPH: :GPIOH,
    IOPI: :GPIOI, IOPJ: :GPIOJ, IOPK: :GPIOK, IOPL: :GPIOL,
    IOPM: :GPIOM, IOPN: :GPION, IOPO: :GPIOO, IOPP: :GPIOP,
    ADC:  :ADC1   
  }

  def update_structs_for_bus_clock
    %i(AHB APB1 APB2 APB3 APB4).each do |bus_name|
      if enr = @parsed[:RCC][:RCC][:registers][:"#{bus_name}ENR"]
        @bus_names << bus_name
        enr[:fields].each do |field|
          bus_periph_name = field[:name][0..-3].to_sym
          if periph_name = BUSNAME_TO_PERIPHNAME[bus_periph_name] || bus_periph_name
            if group_name = @periph_to_group[periph_name]
              if periph_struct = @cpp_structs[group_name].find {|elem| elem[:periph].to_sym == periph_name }
                periph_struct[:bus] = {
                  name: bus_name,
                  bit_offset: field[:bitOffset].to_i,
                }
              end
            end
          end
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
