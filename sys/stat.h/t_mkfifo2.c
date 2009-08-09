/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFOPATH	"sandbox/t_mkfifo2"

int main(void)
{
	char msg[] = "Where I am, I don't know, I'll never know, in the silence"
	    "you don't know, you must go on, I can't go on, I'll go on."
	    "Samuel Beckett, The Unnamable";
	char buf[sizeof(msg)];
	int rfd;
	int wfd;

	/* Create a new named FIFO. */
	assert(mkfifo(FIFOPATH, S_IRWXU) != -1);

        /*
	 * Open named FIFO for reading in non-blocking mode.
	 * This will normally succeed, even if noone has opened on the write
	 * side yet.
	 */
        rfd = open(FIFOPATH, O_RDONLY | O_NONBLOCK);
        assert(rfd != -1);

	/* Open named FIFO for writing. */
	wfd = open(FIFOPATH, O_WRONLY);
	assert(wfd != -1);

	/* Write message, read and verify message integrity. */
	assert(write(wfd, msg, sizeof(msg)) != -1);
	assert(read(rfd, buf, sizeof(buf)) != -1);
	assert(strcmp(buf, msg) == 0);

	/* We are done -- cleanup. */
	assert(close(rfd) != -1);
	assert(close(wfd) != -1);
	assert(unlink(FIFOPATH) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
