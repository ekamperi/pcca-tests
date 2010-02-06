dlfcn.h

int     dlclose(void *);
char  * dlerror(void);
void  * dlopen(const char *, int);
void  * dlsym(void *restrict, const char *restrict);
