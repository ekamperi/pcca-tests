#!/usr/bin/ruby

require 'rexml/document'
include REXML

file = File.new("test.xml")
doc = Document.new(file)

log_passed = File.open("log.passed", "w+")
log_failed = File.open("log.failed", "w+")
log_killed = File.open("log.killed", "w+")
log_stderr = File.open("log.stderr", "w+")

doc.root.each_element('//test/binary') { |binary|
        name    = binary.text
        timeout = binary.attributes['timeout'].to_f

        print name + ": "

        done = 0
        Signal.trap("CHLD") {
                done = 1
        }
        pid = fork {
                begin
                        exec("./" + name)
                rescue StandardError => error
                        puts "#{error}\n"
                        log_stderr.write(name + "\n")
                        raise
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
                        log_passed.write(name + "\n")
                else
                        log_failed.write(name + "\n")
                end
        else
                log_killed.write(name + "\n")
                Process.kill("KILL", pid);
                puts "Test case timed out"
        end
}

log_passed.close()
log_failed.close()
log_killed.close()
log_stderr.close()
