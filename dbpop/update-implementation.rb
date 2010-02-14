#!/usr/pkg/bin/ruby
#
# This script generates SQL statements of the form:
# UPDATE psx_functions SET implemented = 'xxx' WHERE function_name = 'yyy';#
#
# It does so, for every POSIX function as found in the various per-header
# `function.list' files.
#
# In order to determine whether a function is implemented or not, we search
# across the entire repository for any possible tests that use it.
#     - If there's none, we simply delegate the decision as 'pending'.
#
#     - If there's at least one (possibly out of many), that succeeds at
#       building, linking and running, we mark the function as implemented.
#
#     - If there's none that succeeds and there are at least 2 tests,
#       we consider that the common failing denominator is the function.
#       This can of course, lead to false positive results. Increasing the
#       threshold to 3 or more, will eventually make the problem go away.
#

require 'rubygems'
require 'find'
require 'nokogiri'

#
# Extract all test cases from `xmlfile', that use `function'.
# The results are return as an array of the form:
# [['../mqueue.h', 't_mq_open'], ...]
#
def queryxml(xmlfile, function)
        f = File.new(xmlfile, "r")
        doc = Nokogiri::XML(f)

        binaries = []
        doc.xpath("//test/calls/function[text()='#{function}']").each { |e|
                test = e.parent.parent
                binary = test.xpath('binary').first
                binaries << [File.dirname(xmlfile), binary.text]
        }

        f.close

        return binaries
end

#
# Search across the whole repository (i.e., across all `tfile.xml' files) for
# test that use `function'.
#
def queryfunction(function)
        binaries = []
        Find.find("../") { |p|
                # Skip .git
                if FileTest.directory?(p) && File.basename(p) == ".git"
                        Find.prune
                else
                        if File.basename(p) == "tfile.xml"
                                tmp = queryxml(p, function)
                                binaries.concat(tmp)
                        end
                end
        }

        return binaries
end

#
# For all the tests that we have gathered (if any), check their build, link, run
# outcome and decide accordingly whether the function is implemented or not.
#
def querytests(binaries)
        # There are no test cases -- inconclusive.
        return 0 if binaries.empty?

        # If there are test cases, and _at least_ one of them managed to
        # _pass_, we assume the function is implemented.
        binaries.each { |b|
                f = File.new("#{b[0]}/log.passed", 'r')
                while (line = f.gets)
                        return 1 if line.include? b[1]
                end
                f.close
        }

        # Require at least 2 failing test cases.
        # XXX: Increase this to eliminate false positive results.
        return 0 if binaries.size < 2

        # The function is not implemented.
        return -1
end

Find.find("../") { |p|
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
                                        puts "UPDATE psx_functions SET implemented = 'yes' WHERE function_name = '#{line}';"
                                when -1
                                        puts "UPDATE psx_functions SET implemented = 'no'  WHERE function_name = '#{line}';"
                                when 0
                                        puts "UPDATE psx_functions SET implemented = 'pending' WHERE function_name = '#{line}';"
                                end
                                STDOUT.flush
                        end
                        f.close
                end
        end
}
