#!/usr/pkg/bin/ruby
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

    XPath.each(doc.root,
               "//test/calls/function[text()='#{function}']") { |e|
        test = e.parent.parent
        binary = XPath.first(test, 'binary')
        puts binary.text
    }

    f.close
end

Find.find("../") { |p|
    # Skip .git
    if FileTest.directory?(p) && File.basename(p) == ".git"
        Find.prune
    else
        if File.basename(p) == "tfile.xml"
            queryxml(p, "#{ARGV[0]}")
        end
    end
}
