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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void)
{
	void *handle;
	int (*pstrcmp)(const char *s1, const char *s2);

	/* Open shared object. */
	handle = dlopen("libc.so", RTLD_LAZY);
	assert(handle != NULL);

	/* Get the address of strcmp(3). */
	*(void **)(&pstrcmp) = dlsym(handle, "strcmp");
	assert(dlerror() == NULL);

	/* Invoke strcmp(). */
	assert((*pstrcmp)("abc", "abc") == 0);
	assert((*pstrcmp)("a", "b") < 0);
	assert((*pstrcmp)("b", "a") > 0);

	/* Try to get the address of a non existent symbol. */
	dlsym(handle, "ifthisexistsinlibcillmemorizeissue7alongwithallthe"
	      "technicalcorrigendumsissuedbyopengroupsincetheverybeginning");
	assert(dlerror() != NULL);

	/*
	 * Since we are here let's test dlerror() as well.
	 * If no dynamic linking errors have occurred since the last invocation
	 * of dlerror(), dlerror() will return NULL.
	 */
	assert(dlerror() == NULL);

	/* Close shared object. */
	assert(dlclose(handle) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
