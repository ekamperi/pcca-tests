#!/usr/pkg/bin/ruby
#
# ARGV[0] is the path the tfile.xml file
# ARGV[1] is the name of the function
#
# The scipt parses the XML file and returns the names of those test cases that
# use the audited function.

require 'rexml/document'
include REXML

xmlfile = File.new(ARGV[0], "r")
doc = Document.new(xmlfile)

XPath.each(doc.root,
           '//test/calls/function[text()=$function]',
           {},
           {"function"=>"#{ARGV[1]}"}) { |e|
    test = e.parent.parent
    binary = XPath.first(test, 'binary')
    puts binary.text
}

xmlfile.close
