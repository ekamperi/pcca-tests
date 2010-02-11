#!/usr/pkg/bin/ruby

tfile   = File.new("#{ARGV[0]}/tfile", "r")
xmlfile = File.new("#{ARGV[0]}/tfile.xml", "w")

xmlfile.puts '<?xml version="1.0"?>'
xmlfile.puts "<list-of-tests>"

while (line = tfile.gets)
        next if line[0].chr == "#"      # Ignore comments in tfiles
        next if line.include? ".sh"     # Also ignore shell scripts
        xmlfile.puts "\t<test>"

        xmlfile.puts "\t\t<desc></desc>"
        xmlfile.puts "\t\t<binary>#{line.chop}</binary>"
        xmlfile.puts "\t\t<timeout>10</timeout>"
        xmlfile.puts "\t\t<iterations>1</iterations>"
        xmlfile.puts "\t\t<optional>false</optional>"
        xmlfile.puts "\t\t<calls>"

        ffile = File.new("#{ARGV[0]}/#{line.chop}.c.cflow", "r")
        while (func = ffile.gets)
                xmlfile.puts "\t\t\t<function>#{func.chop}</function>"
        end
        ffile.close

        xmlfile.puts "\t\t</calls>"
        xmlfile.puts "\t</test>"
        xmlfile.puts
end

xmlfile.puts "</list-of-tests>"

tfile.close
xmlfile.close
