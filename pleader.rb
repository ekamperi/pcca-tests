#!/usr/bin/ruby

log_passed = File.open("#{ARGV[0]}/log.passed", "w+")
log_failed = File.open("#{ARGV[0]}/log.failed", "w+")

tests = Dir.glob("#{ARGV[0]}/t_*_prot.c")

tests.each { |t|
        pid = Process.fork {
                exec("gcc -std=c99 -Werror #{t} >/dev/null 2>/dev/null")
        }

        Process.wait(pid)
        print "#{t}: "
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
