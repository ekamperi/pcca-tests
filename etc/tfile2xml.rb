#!/usr/bin/ruby

tfile   = File.new("#{ARGV[0]}", "r")
xmlfile = File.new("#{ARGV[0]}.xml", "w")

xmlfile.puts '<?xml version="1.0"?>'
xmlfile.puts "<list-of-tests>"

while (line = tfile.gets)
        xmlfile.puts "\t<test>"

        xmlfile.puts "\t\t<desc></desc>"
        xmlfile.puts "\t\t<binary>#{line.chop}</binary>"
        xmlfile.puts "\t\t<timeout>10</timeout>"
        xmlfile.puts "\t\t<iterations>1</iterations>"
        xmlfile.puts "\t\t<optional>false</optional>"

        xmlfile.puts "\t</test>"
        xmlfile.puts
end

xmlfile.puts "</list-of-tests>"

tfile.close
xmlfile.close
