#!/usr/bin/ruby

tests = Dir.glob("#{ARGV[0]}/t_*_prot.c")

tests.each { |t|
        pid = Process.fork {
                exec("gcc -std=c99 -Werror #{t} >/dev/null 2>/dev/null")
        }

        Process.wait(pid)
        print "#{t}: "
        if ($?.exitstatus == 0)
                puts "passed"
        else
                puts "failed"
        end
}
