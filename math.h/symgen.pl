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
# Possible values of feauture test macros are:
# _POSIX_C_SOURCE 200112L - Exposes the base POSIX namespace of SUSv3.
# _XOPEN_SOURCE 600       - Exposes the X/Open System Interface (XSI) extension
#			    of SUSv3.
#
# Eventually a compilable C file is generated. The file contains the
# following basic unit:
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
my @inpfile = split /\./, $ARGV[0];
open TOFILE, ">", "r$inpfile[0].c";

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
my $gcc_cmd = "gcc -Wall -W -ansi -pedantic -o r$inpfile[0] r$inpfile[0].c ";

while (my $line = <SPECFILE>) {
    # Ignore empty lines.
    if ($line !~ /\S/) {
	next;
    } elsif ($line =~ m/\{$/) {		# Opening brace encountered.
	@ret = split " ", $line;	# Split at whitespace.

	print TOFILE "\t/* $ret[0] */\n";
	$gcc_cmd = $gcc_cmd . "-D$ret[0]=$ret[1] ";

    } elsif ($line =~ m/\}$/) {		# Closing brace encountered.
	print TOFILE "\t/* Done with $ret[0] */\n\n";
    }
    else {
	# Remove the trailing \n.
	chomp($line);

	# Remove whitespace.
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
