#!/usr/bin/ruby
#
# ARGV[0] is the path the tfile.xml file
# ARGV[1] is the name of the function
#
# The scipt parses the XML file and returns the names of those test cases that
# use the audited function.

require 'find'
require 'rexml/document'
include REXML

def queryxml(xmlfile, function)
        f = File.new(xmlfile, "r")
        doc = Document.new(f)

        binaries = []
        XPath.each(doc.root,
                   "//test/calls/function[text()='#{function}']") { |e|
                test = e.parent.parent
                binary = XPath.first(test, 'binary')
                binaries << [File.dirname(xmlfile), binary.text]
        }

        f.close

        return binaries
end

def queryfunction(function)
        binaries = []
        Find.find("../") { |p|
                # Skip .git
                if FileTest.directory?(p) && File.basename(p) == ".git"
                        Find.prune
                else
                        if File.basename(p) == "tfile.xml"
                                tmp = queryxml(p, function)
                                binaries << tmp if tmp != []
                        end
                end
        }

        return binaries
end

def querytests(binaries)
        # There are no test cases -- inconclusive
        return 0 if binaries.empty?

        # If there are test cases, and _at least_ one of them managed to
        # _build_, we assume the function is implemented.
        binaries[0].each { |b|
                f = File.new("#{b[0]}/log.passed", 'r')
                while (line = f.gets)
                        return 1 if line.include? b[1]
                end
                f.close

                f = File.new("#{b[0]}/log.failed-runtime", 'r')
                while (line = f.gets)
                        return 1 if line.include? b[1]
                end
                f.close
        }

        # Require at least 2 failing test cases.
        return 0 if binaries[0].size < 2

        return -1
end

Find.find("../grp.h") { |p|
        # Skip .git
        if FileTest.directory?(p) && File.basename(p) == ".git"
                Find.prune
        else
                if File.basename(p) == "functions.list"
                        f = File.new(p, 'r')
                        while (line = f.gets)
                                line = line.chomp

                                next if line == ""
                                next if line =~ /\.h$/
                                #puts ">>> #{line}"
                                rv = querytests(queryfunction(line))
                                case rv
                                when 1
                                        puts "UPDATE psx_functions SET implemented = 'yes' WHERE function_name '#{line}'"
                                when -1
                                        puts "UPDATE psx_functions SET implemented = 'no' WHERE function_name '#{line}'"
                                when 0
                                        # puts "Pending"
                                end
                                STDOUT.flush
                        end
                        f.close
                end
        end
}
