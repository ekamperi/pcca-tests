#!/usr/bin/ruby

Dir.chdir("#{ARGV[0]}")

log_passed = File.open("prototypes/log.passed-prototypes", "w+")
log_failed = File.open("prototypes/log.failed-prototypes", "w+")

cfiles = Dir.glob("prototypes/t_*_prot.c")

cfiles.each { |cfile|
        pid = Process.fork {
                exec("gcc -std=c99 -Werror -c #{cfile} >/dev/null 2>/dev/null")
        }

        tname = File.basename(cfile, '.c')
        tpath = File.basename(Dir.pwd)
        print "[1/1] /#{tpath}/prototypes/#{tname}: "

        Process.wait(pid)
        if ($?.exitstatus == 0)
                puts "passed"
                log_passed.puts "#{tname}"
        else
                puts "failed"
                log_failed.puts "#{tname}"
        end
}

log_passed.close
log_failed.close
