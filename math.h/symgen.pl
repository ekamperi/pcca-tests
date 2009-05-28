#! /usr/pkg/bin/perl

# This script parses a specification file of the following form:
#
# FEATURE_TEST_MACRO1 VALUE {
#	SYMBOL1
#	SYMBOL2
#	...
# }
#
# FEATURE_TEST_MACRO2 VALUE {
#	SYMBOL1
#	SYMBOL2
#	...
# }
#
# And generates a compilable C file of the form:
#
# #ifndef SYMBOL1
#	printf("FEATURE_TEST_MACRO1: Missing symbol: %s", "SYMBOL1");
# #endif
#	...
#
# It also constructs a gcc command of the form:
# gcc -DFEAUTURE_TEST_MACRO1=VALUE -DFEAUTURE_TEST_MACRO=VALUE

use warnings;
use strict;

# Open file with specs for parsing.
open SPECFILE, "<", $ARGV[0] or die "Can't open $ARGV[0]";

# Open target file for code generation.
open TOFILE, ">", "$ARGV[0].c";

# Include the necessary headers.
print TOFILE "#include <stdio.h>\n";
print TOFILE "#include <stdlib.h>\n";

# The first line of the spec file contains the header file we examine.
my $include = <SPECFILE>;
chomp $include;
print TOFILE "#include <$include>\n\n";

# Here comes the main()
print TOFILE "int main(void) {\n";

# Parse file.
my @ret;
my $gcc_cmd = "gcc -Wall -W -ansi -pedantic -o r$ARGV[0] $ARGV[0].c ";

while (my $line = <SPECFILE>) {
    # Ignore void lines.
    if ($line !~ /\S/) {
	next;
    } elsif ($line =~ m/\{$/) {	# Mark the opening brace.
	@ret = split " ", $line;	# Split at whitespace.

	print TOFILE "\t/* $ret[0] */\n";
	$gcc_cmd = $gcc_cmd . "-D$ret[0]=$ret[1] ";

    } elsif ($line =~ m/\}$/) {	# Mark the closing brace.
	print TOFILE "\t/* Done with $ret[0] */\n\n";
    }
    else {
	# Remove the trailing \n
	chomp($line);

	# Remove whitespace
	$line =~ s/^\s+|\s+$//g;

	print TOFILE "\t#ifndef $line\n";
	print TOFILE "\t\tprintf(\"$ret[0]: Missing symbol: %s\\n\", \"$line\");\n";
	print TOFILE "\t#endif\n\n";
    }
}

print TOFILE "\treturn (EXIT_SUCCESS);\n}\n";

# Done -- close the files.
close SPECFILE;
close TOFILE;

print "$gcc_cmd\n";
