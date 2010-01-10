#!/usr/bin/ruby

require 'rexml/document'
require 'timeout'
include REXML

file = File.new("test.xml")
doc = Document.new(file)

passed = 0
failed = 0
killed = 0

doc.root.each_element('//test/binary') { |binary|
        name    = binary.text
        timeout = binary.attributes['timeout'].to_f

        print name + ": "

        done = 0
        Signal.trap("CHLD") {
                done = 1
        }
        pid = fork {
                exec("./" + name)
        }

        now = Time.now
        while ((Time.now - now) < timeout) do
                break if done == 1
                sleep 0.5
                #puts "sleep"
        end

        if (done == 1)
                Process.wait(pid)
                if ($?.exitstatus == 0)
                        passed += 1
                else
                        failed += 1
                end
        else
                killed += 1
                Process.kill("KILL", pid);
                puts "Test case timed out"
        end
}

puts "passed #{passed}" 
puts "failed #{failed}"
puts "killed #{killed}"
