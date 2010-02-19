#!/usr/bin/ruby

require 'rexml/document'
include REXML

Dir.chdir("#{ARGV[0]}")
#puts Dir.pwd

file = File.new("tfile.xml")
doc = Document.new(file)

log_passed           = File.open("log.passed", "w+")
log_failed_buildtime = File.open("log.failed-buildtime", "w+")
log_failed_runtime   = File.open("log.failed-runtime", "w+")
log_killed           = File.open("log.killed", "w+")

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
        binary     = elms_h['binary']
        timeout    = elms_h['timeout'].to_f
        optional   = elms_h['optional']
        iterations = elms_h['iterations'].to_i

        cnt = 0
        iterations.times {
                cnt = cnt + 1
                # Defaults
                timeout = 10 if timeout < 10

                # If it's a shell script, let it handle the output on its own.
                if ! (binary =~ /\.sh$/)
                        print "[#{cnt}/#{iterations}] "
                        print "/" + File.basename(Dir.pwd) + "/" + binary + ": "
                        print "[optional] " if optional == "true"
                end

                # If we can't find the binary, most likely it failed to build during.
                # We treat this as a failed test case, by logging it as such.
                if ! File.exists?(binary)
                        puts "failed (test case doesn't exist)"
                        log_failed_buildtime.write(binary + "\n")
                        break
                end

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
                        sleep 0.1
                        #puts "sleep"
                end


                # If what we executed was a shell script, we don't log anything
                # and delegate the responsibility to the script itself.
                # E.g., uleader.sh
                if binary =~ /\.sh$/
                        next
                end

                if (done == 1)
                        Process.wait(pid)
                        if ($?.exitstatus == 0)
                                log_passed.write(binary + "\n")
                        else
                                log_failed_runtime.write(binary + "\n")
                        end
                else
                        Process.kill("KILL", pid);
                        log_killed.write(binary + "\n")
                        puts "killed (test case timed out)"
                end

                # Flush buffers or else they me cloned across fork() and
                # duplicate output be written to disk!
                log_passed.flush
                log_failed_buildtime.flush
                log_failed_runtime.flush
                log_killed.flush
        }
}

log_passed.close
log_failed_buildtime.close
log_failed_runtime.close
log_killed.close

file.close
