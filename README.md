## SUPPORTED PLATFORMS

A lot of care has been taken to ensure that the test suite runs in as many
environments as possible.

This way we verified the correctness of the test cases and lowered the
probability of relying on some non-standard feature of the host operating
system. Not only did we ran the tests in different OSes, but we spread its
development across them as well.

The suite has been deployed and proved to work (with decreasing levels of
confidence) under DragonFlyBSD, NetBSD, Linux, OpenSolaris, FreeBSD and OpenBSD
both in automated/bulk and manual mode.

## GETTING THE TEST REPOSITORY

The test case repository is (not so much) tight to git. That said, the best way
to get it is to clone it:

    ~% git clone git://gitweb.dragonflybsd.org/~beket/pcca-tests.git

See the "EXPORTING TEST REPOSITORY TO A GIT-LESS HOST" section on how to create
a tar archive and pass it around.

## SETTING UP THE HOST a.k.a. REQUIREMENTS

What you need to run the tests is basically these:

* GNU C Compiler, either 3.x or 4.x.
  Limited tests (namely regarding complex arithmetic support) were conducted
  succesfully with clang/llvm.
* A decent make(1) utility.
* Ruby 1.8.x or 1.9.x.
* A POSIX compliant shell found in /bin/sh.
  If you can't afford one, you can instead try with bash. For example, Solaris
  10 /bin/sh or even /usr/xpg4/bin/sh don't play nice with us. In any case, you
  may have to edit the various scripts (e.g., mktests.sh) to set the path of the
  shell binary.
* The sudo(1) utility.
  This is used by mktests.sh script and various Makefiles to set the suid bit to
  certain test case binaries. The ability of these binaries to escalate their
  privileges is paramount to the test logic.
* A non-root user.
  The user must be listed in the /etc/sudoers file. Some tests, will fail if ran
  by root user. Which is a bad call anyway.
* Please read any README.$os files that refer to your host operating system.
  E.g., mqueue.h/README.freebsd, if you are running the test suite under
  FreeBSD, which describes how to enable POSIX message queues support. For your
  convenience you can retrieve such files (if any) with the help of
  `getreadme.sh' script.
* For dbpop/ to work, you will also need the Nokogiri XML parser, as the default
  one (REXML) is unbearably slow.

If you find a portable way to set the suid bit, without using sudo, please drop
me a note.

## RUNNING THE TESTS - AUTOMATED MODE

You may run the tests in two ways, either automatically via the mktests.sh
script or manually on a per $header.h/ basis. There are some unique aspects
of mktests.sh, rendering it the superior way for running the tests:

* It can recursively run tests, e.g. run all tests associated with the sys/*
  headers.
* It supports job control,meaning that if a test exceeds a specified amount
  of execution time, it gets killed and the rest of the tests continue to run
  normally.
* Log statistics are generated for every $header.h/ directory, which can later
  be retrieved with the getstats.sh script.

Here is a usual workflow:

    pcca-tests% ./mktests.sh -c	     # Clean files from previous build/run
    pcca-tests% ./mktests.sh -s	     # Construct sandbox/ directories
    ...	      		   	             # Messages from the construction
    pcca-tests% ./mktests.sh -b	     # Build test cases
    ...	      		   	             # Messages from compilation
    pcca-tests% ./mktests.sh -r	     # Run tests (if none given, . is assumed
                                     # as the top level directory to start from)
    pcca-tests% ./mktests.sh -r
    /aio.h/t_aio: Assertion failed: (aio_read(&iocb) != -1), function main, file
    t_aio.c, line 56.
    /complex.h/t_cabs: passed
    /complex.h/t_carg: passed
    /complex.h/t_cacos: passed
    ...
    pcca-tests%

Collapsing individual arguments is possible. E.g.,
    pcca-tests% ./mktests.sh -csbr

## RUNNING THE TESTS - MANUAL MODE

In manual mode, one cd's into the directory of interest, types 'make' to
build the tests and 'make run' to run them.

    pcca-tests% cd stdio.h
    pcca-tests/stdio.h% make
    ...				                # Messages from gcc compilation
    pcca-tests/stdio.h% make run
    t_clearerr: passed
    t_ctermid: passed
    ...
    t_tmpfile: passed
    pcca-tests/stdio.h%

If a test fails to build (because the host OS misses a function for example),
make(1) will stop building further targets. If this is the case, please pass
-k option:

    pcca-tests% cd stdio.h
    pcca-tests/stdio.h% make -k
    ...
    pcca-tests/stdio.h%

With -k, when a rule returns an error, make(1) skips the work on the current
target, and continues with other dependency branches that do not depend on it
(on the failed target that is). Note that -k is actually a POSIX mandated
option.

## GETTING STATISTICS

After a bulk run has been completed (or even interrupted, since logs are
generated incrementally) the log statistics can be retrieved via the getstats.sh
script:

    pcca-tests% ./getstats.sh	# If no argument is given, "." is assumed
    >>> Headers
            Audited:       77

    >>> Test files
            tfiles :      195

    >>> Lines of code
            C      :    15955
            make   :     1877
            sh     :      959
            Perl   :      175

    >>> Results from last run
            Passed :      164
            Failed :       31

It is also possible to explicitly set the top level directory. Suppose we need
to know the complex arithmetic support of the host environment:

    pcca-tests% ./getstats.sh ./complex.h
    >>> Headers
            Audited:        1

    >>> Test files
            tfiles :       26

    >>> Lines of code
            C      :     1744
            make   :      194
            sh     :        0
            Perl   :        0

    >>> Results from last run
            Passed :       26
            Failed :        0
    pcca-tests%

## GETTING STATISTICS - WHICH TESTS FAILED ?

A failure may originate from:

* An unmet assertion during the test's execution.
* Test's failure to compile, due to host OS missing some critical stuff.
* Test having exceeded the time slice that was allowed to run.

The only way to differentiate between the above is to look at the output during
test case execution.

In each $header.h/ directory, for which statistics are available, there is a
`log.passed' and a `log.failed' file. These files contain the pathnames of the
test binaries that succeeded or failed respectively. E.g.,

    pcca-tests% cat unistd.h/log.failed
    ./unistd.h/t_access2
    ./unistd.h/t_fchdir_suid
    ...

For your convenience the `getfailed.sh' script is provided that can list the
failed test cases on a per $header.h basis:

    pcca-tests% ./getfailed.sh unistd.h
    ./unistd.h/t_access2
    ./unistd.h/t_fchdir_suid
    ...
    pcca-tests%

or, more importantly, for the whole repository:

    pcca-tests% ./getfailed.sh
    ./aio.h/t_aio
    ...

## ADDING A NEW TEST CASE

The addition of a new test case is very straightforward. Assuming you have the
actual source code of the test case as a C file, you need to do the following:

* Copy the file over to the proper $header/ directory.
* Add a target in the `Makefile'.
* Add the name of the executable in the `tfile'.
* git add t_foo.c Makefile tfile
* git commit -m "$header.h: Add new t_foo test case."

Both the `Makefile' and `tfile' are located in the $header/ directory. You can
use the existing rules and entries as templates.

You are encouraged, although not required, to name the test case as the
principal function you are testing against. E.g., t_pthread_join.c if you
are writing a test case for the pthread_join() function. This will allow you
to automatically generate SQL commands with dbpop/updatetestcases.sh, if you are
maintaining a POSIX conformance tracking site. 

## SANDBOXES

Various tests need to check against all sort of weird situations like trying
to access a file without search/execute permission or resolve an unresolvable
symbolic link and so on. For this purpose we have introduced the notion of a
sandbox/ directory, which acts as a provider for them.

The sandbox/ directories are created and populated via mktests.sh script. Every
$header.h/ directory that needs one, there must have a file 'need-sandbox' in
it. No need for that file to contain anything at all, just exist. But, it MUST
be tracked by git:

    pcca-tests% mkdir foo.h
    pcca-tests% cd foo.h
    pcca-tests/foo.h% touch need-sandbox
    pcca-tests/foo.h% git add need-sandbox
    pcca-tests/foo.h% git commit -m "foo.h: Add need-sandbox file"
    ...
    pcca-tests%
    pcca-tests% ./mktests.sh -s ./foo.h
    Created ./foo.h/sandbox directory
    pcca-tests%
    pcca-tests% ls ./foo.h/sandbox
    dir000    dir666  dirloop  file000  file666  fileloop  infloop2  notatty
    dir555    dir777  fifo	  file555  file777  infloop   notadir   rootfile600

We could have supplied only one top-level such directory, and have let the tests
refer to it via ../../sandbox/* and so on. The reason for separate $header.h/
sandboxes, is because we wanted the various $header.h/ directories to
be completely self-sufficient. So that one could tar -say- pthread.h/ tests,
send the archive over to a remote machine, untar it, and be able to run the
tests.

On top of that, having all tests use the same exact file structures could
potentially lead to undesired results. For example, among the provided files
there is a FIFO special file. Although it is an unlikely to happen scenario,
what whould be the consequences of two different tests trying to access it
at the same time ?

## POSSIBLE PLACES OF CONFUSION

* The user that runs the test must NOT be root. This is a good practice anyway,
but it's not just that. Some tests require that they are executed in a non-
privileged context, eg. unistd.h/t_access2.
On the other hand, the user MUST belong to the sudoers, because in some places,
we need to set-user-ID bit or change the owner of a file, eg. unistd.t_access2.
XXX: What about Solaris 10 and later?

* In Linux particularly, but in other systems as well, make sure that you don't
mount the medium where the tests reside as 'nosuid' (or similar). Again, this is
because some tests have the set-user-ID bit set, eg. unistd.h/t_access2. Running
them in a context where the uid can't be escalated, it will result in a false
failed test. If you want to get the list of suid binaries in the repository,
after you have built the tests, type:

        pcca-tests% find . -type f \( -perm -4000 -o -perm -2000 \) -exec \
        > ls -lh {} \; 2>/dev/null
        -rwsr-xr-x  1 root  beket   6.9K Aug 12 00:09 ./unistd.h/t_access2
        pcca-tests%

* If you try to grep(1) recursively inside a $header.h directory that contains
a sandbox/ directory, grep may block indefinitely in 'fifoor' state or similar.
This is due to the presence of fifo special file inside the sandbox/ directory,
which will block grep upon opening it. This is a perfectly legitimate behavior
and not some bug of grep. It can be circumvented by passing -O option to grep,
instructing it to skip special files. -O though is non-standard so it may not
be readily available to all systems. In such case, just delete the sandbox/'es
with mktests.sh -c and then grep.

* If you try to find(1) inside a repository that has the sandbox/ directories in
it, errors will be printed to your console:

        pcca-tests% find . -name foo
        find: ./unistd.h/sandbox/dir000: Permission denied
        ...
        pcca-tests%

These are harmless but annoying nonetheless. You can try the following:
* Redirect stderr to null (e.g., find . -name foo 2>/dev/null).
* Delete the sandboxes with mktests.sh -c and then call find.
* Use one of the specialized scripts in the repository (getheaders.sh,
  getheaders.sh, getspecs.sh, etc). These not only silence the error messages,
  but also skip the .git/ directory, which may save you a little bit of
  execution time in low spec machines.

* Log files are generated ONLY when tests are executed via mktests.sh and NOT
manually with make && make run.

        pcca-tests% ./mktests.sh -c
        pcca-tests% cd stdio.h
        pcca-tests/stdio.h% make
        ...
        pcca-tests/stdio.h% make run
        ...
        pcca-tests% ./getstats.sh ./stdio.h
        ...
        >>> Results from last run
                Passed :        0
                Failed :        0
        pcca-tests% ./mktests.sh -r ./stdio.h
        ...
        pcca-tests% ./getstats.sh ./stdio.h
        ...
        >>> Results from last run
                Passed :        7
                Failed :        0
        pcca-tests%

## EXPORTING TEST REPOSITORY TO A GIT-LESS HOST

You may want to run the test suite in a host where git is unavailable. In this
case you need the git-archive command:

    # Exporting the whole repository
    pcca-tests% git archive --format=tar HEAD | gzip > "tests.tar.gz"

    # Exporting only a part of it
    pcca-tests% git archive --format=tar HEAD ./math.h | gzip > "tests.tar.gz"

    # Verifying tar's contents
    pcca-tests% gunzip < tests.tar.gz | tar tf -
    math.h/
    math.h/Makefile
    math.h/NOTES
    math.h/functions.list
    math.h/math.h.spec
    ...
    pcca-tests%

    # Getting the commit ID
    pcca-tests% git get-tar-commit-id < tests.tar
    1b56e96931aa1c58e138b57b8066732a7950f043
    pcca-tests%

If you also need to upload the result to some ssh shell account, you can use
the export.sh script which is found in the root directory of the repository:

    pcca-tests% ./export.sh
    >>> Creating git archive with name pcca-tests-12-08-09.tar.gz
    DONE
    >>> Uploading git archive to beket@leaf.dragonflybsd.org:~/public_html
    pcca-tests-12-08-09.tar.gz                        100%  108KB 108.1KB/s   00:00
    DONE
    pcca-tests%

## TIPS & TRICKS

* If your sleep(1) supports decimal delays, a non standard feature, you may
edit tleaders.sh and replace 'sleep 1' occurences with 'sleep 0.2' or so.
This will decrease the time needed by the test suite to complete a bulk run.
Especially in fast machines.

Solaris 10 doesn't support it, but I've been told that opensolaris ships with
gnu sleep as well, which will work.
