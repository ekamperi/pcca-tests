#! /usr/pkg/bin/perl
#
# This script parses a specification file of the following form:
#
# FEATURE_TEST_MACRO1 VALUE {
#	SYMBOL1		# This is a comment
#	# This is also a comment
#	SYMBOL2
#	...
# }
#
#	# Comments may reside outside of a { } block,
#	# but not in the same line and prior to an opening brace!
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
#

use warnings;
use strict;

use File::Basename;
use Getopt::Long;

# Command line options.
my $less = '';		# Look for missing symbols.
my $more = '';		# Look for overexposed symbols.
my $help = '';		# Print usage.

GetOptions('less'	=> \$less,
	   'more'	=> \$more,
	   'help|?'	=> \$help);

# Print usage.
exitusage() if ($help);

# Make sure the user has supplied a specifications file.
exitusage() if (!$ARGV[0]);

# We can't allow both --more AND --less at the same time.
exitusage() if ($less && $more);

# ... on the other hand at least of them must be given.
exitusage() if (!$less && !$more);

# Open file with specs for parsing.
open my $specfile, "<", $ARGV[0] or die "Can't open $ARGV[0]";

# Get the basename of the specfile.
# For instance ./math.h/math.h.spec file becomes math.h.spec.
my $basefile = basename($ARGV[0]);

# Ignore the .h.spec extension. Also prepend `r' to the file,
# e.g. for math.h.spec the file rmath.c is created.
my @inpfile = split(/\./, $basefile);
open my $tofile, ">", "r$inpfile[0].c";

# Construct a specially crafted gcc invocation, but don't run it. Just print it.
# Warning flags, etc will be removed once we get the script right.
my $gcc_cmd = "gcc -Wall -W -ansi -pedantic -o r$inpfile[0] r$inpfile[0].c ";

# Include the necessary headers.
print $tofile "#include <stdio.h>\n";
print $tofile "#include <stdlib.h>\n";	# For EXIT_FAILURE.

# The first line of the spec file contains the header file we examine.
my $include = <$specfile>;
chomp $include;
print $tofile "#include <$include>\n\n";

# Here comes the main(), durururu, here comes the main()
# ... and I say it's all right!
print $tofile "int main(void) {\n";

# Parse file.
my @ret;

while (my $line = <$specfile>) {
    # Before we start processing the current line, we ignore any comments.
    $line =~ s/#.*//;

    # We ignore empty lines both in and out of blocks.
    if ($line !~ /\S/) {
	next;
    } elsif ($line =~ m/\{$/) {		# Opening brace encountered.
	@ret = split " ", $line;	# Split at whitespace.

	# Print a comment to know where we are.
	print $tofile "\t/* $ret[0] */\n";

	# In --less mode we need to add the appropriate -Dmacro=definition
	# parts in the gcc command.
	if ($less) {
	    $gcc_cmd = $gcc_cmd . "-D$ret[0]=$ret[1] ";
	} elsif ($more) {
	    # Whereas in --more mode we add some sanity cheks,
	    # just in case someone else defines a feature test macro,
	    # that shouldn't be defined.
	    print $tofile "#if ($ret[0] - 0) < $ret[1]\n";
	}
    } elsif ($line =~ m/\}$/) {		# Closing brace encountered.
	# Print a comment to know where we are.
	print $tofile "\t/* Done with $ret[0] */\n\n";

	if ($more) {
	    print $tofile "#else\n";
	    print $tofile "\tprintf(\"The test may be unreliable\");\n";
	    print $tofile "#endif\n";
	}
    }
    else {
	# Remove the trailing \n.
	chomp($line);

	# Remove whitespace.
	$line =~ s/^\s+|\s+$//g;

	# Align output.
	my $aret = $ret[0];
	$aret = $aret . '  ' if ($aret eq '_XOPEN_SOURCE');

	if ($less) {
	    print $tofile "\t#ifndef $line\n";
	    print $tofile "\t\tprintf(\"$aret: Missing symbol: %s\\n\", \"$line\");\n";
	    print $tofile "\t#endif\n\n";
	} elsif ($more) {
	    print $tofile "\t#ifdef $line\n";
	    print $tofile "\t\tprintf(\"$aret: Overexposing symbol: %s\\n\", \"$line\");\n";
	    print $tofile "\t#endif\n\n";
	}
    }
}

print $tofile "\treturn (EXIT_SUCCESS);\n}\n";

# Done -- close the files.
close $specfile;
close $tofile;

#print "$gcc_cmd\n";
system($gcc_cmd);
system("./r$inpfile[0]");
system("rm ./r$inpfile[0]*");

# Print a message (optional), then usage and then exit.
sub exitusage
{
    print $_[0] if ($_[0]);

    print "Usage: symgen.pl [--less | --more] specfile\n";
    print "\t--less: check for missing symbols\n";
    print "\t--more: check for overexposed symbols\n";
    print "Exactly one out of --less, --more must be specified.\n";

    exit;
}
