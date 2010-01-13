#!/usr/bin/ruby

require 'rexml/document'
include REXML

file = File.new("test.xml")
doc = Document.new(file)

log_passed = File.open("log.passed", "w+")
log_failed = File.open("log.failed", "w+")
log_killed = File.open("log.killed", "w+")

doc.root.each_element('//test') { |t|
        # Convert array of elements to hash table.
        elms_a = t.elements().to_a
        keys = []
        values = []
        elms_a.each { |e|
                keys << e.name
                values << e.text
        }
        elms_h = Hash[*keys.zip(values).flatten]

        # Extract properties
        binary  = elms_h['binary']
        timeout = elms_h['timeout'].to_f
        optional= elms_h['optional']

        # Defaults
        timeout = 10 if timeout < 10

        print "[optional] " if optional
        print binary + ": "

        done = 0
        Signal.trap("CHLD") {
                done = 1
        }
        pid = fork {
                begin
                        exec("./" + binary)
                rescue StandardError => error
                        puts "#{error}\n"
                        exit 1
                end
        }

        start = Time.now
        while ((Time.now - start) < timeout) do
                break if done == 1
                sleep 0.5
                #puts "sleep"
        end

        if (done == 1)
                Process.wait(pid)
                if ($?.exitstatus == 0)
                        log_passed.write(binary + "\n")
                else
                        log_failed.write(binary + "\n")
                end
        else
                log_killed.write(binary + "\n")
                Process.kill("KILL", pid);
                puts "Test case timed out"
        end

        # Flush buffers or else they me cloned across fork() and duplicate output
        # be written to disk!
        log_passed.flush
        log_failed.flush
        log_killed.flush
}

log_passed.close()
log_failed.close()
log_killed.close()
