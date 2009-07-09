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

	/* Close shared object. */
	assert(dlclose(handle) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
