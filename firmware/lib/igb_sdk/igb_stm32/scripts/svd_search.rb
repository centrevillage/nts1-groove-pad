require 'rexml/document'

class SVDSearch
  def self.search(dir, path)
    puts "searching dir = #{dir}"
    Dir[dir].each do |filename|
      puts "searching file = #{filename}"
      open(filename) do |file|
        doc = REXML::Document.new(file)
        REXML::XPath.match(doc, path).each do |matched|
          puts "[#{filename}] == "
          puts matched
        end
      end
    end
  end
end

if __FILE__ == $0
  SVDSearch.search ARGV[0], ARGV[1]
end
