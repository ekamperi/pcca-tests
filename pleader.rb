#!/usr/bin/ruby

Dir.chdir("#{ARGV[0]}")

log_passed = File.open("prototypes/log.passed-prototypes", "w+")
log_failed = File.open("prototypes/log.failed-prototypes", "w+")

tests = Dir.glob("t_*_prot.c")

tests.each { |t|
        pid = Process.fork {
                exec("gcc -std=c99 -Werror #{t} >/dev/null 2>/dev/null")
        }

        Process.wait(pid)
        print "[1/1] /#{File.basename(Dir.pwd)}/prototypes/#{t}: "
        if ($?.exitstatus == 0)
                puts "passed"
                log_passed.puts "#{File.basename(t, '.c')}"
        else
                puts "failed"
                log_failed.puts "#{File.basename(t, '.c')}"
        end
}

log_passed.close
log_failed.close
