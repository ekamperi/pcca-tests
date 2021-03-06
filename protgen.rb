#!/usr/pkg/bin/ruby

def getfunc(line)
        s = -1
        e = -1

        # Go forward until we meet the first (
        for k in 0..line.length-1
                if (line[k, 1] == '(')
                        e = k-1
                        break
                end
        end

        # Go backwards until we meet the first whitespace
        k = e-1
        while k > 0 do
                if (line[k, 1] == ' ')
                        s = k+1
                        break
                end
                k=k-1
        end

        return line[s..e]
end

def crtest(header, prot, func)
        protpath = File.dirname(ARGV[0]) + "/prototypes"
        testfile = File.new("#{protpath}/t_#{func}_prot.c", "w")

        re = Regexp.new(func)

        testfile.puts <<HERE
#define _XOPEN_SOURCE 600
#include <#{header}>

#{prot.gsub(re, "(*fp)")}
int
main(void)
{
        fp = #{func};
        return 0;
}
HERE
end

protfile   = File.new("#{ARGV[0]}", "r")

header = protfile.gets.chomp
emptyline = protfile.gets

while (line = protfile.gets)
        func = getfunc(line)
        next if func.length == 0
        crtest(header, line, func)
end

protfile.close
