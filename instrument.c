#include <stdio.h>
#include <stdlib.h>

void main_constructor(void)
    __attribute__ ((no_instrument_function, constructor));

void main_destructor(void)
    __attribute__ ((no_instrument_function, destructor));

void __cyg_profile_func_enter(void *, void *)
    __attribute__ ((no_instrument_function));

void __cyg_profile_func_exit(void *, void *)
    __attribute__ ((no_instrument_function));

static FILE *fp;

void main_constructor(void)
{
    fp = fopen("trace.txt", "w");
    if (fp == NULL)
    {
        exit(-1);
    }
}

void main_deconstructor(void)
{
    fclose(fp);
}

void __cyg_profile_func_enter(void *this, void *callsite)
{
    fprintf(fp, "E%p\n", (int *)this);
}

void __cyg_profile_func_exit(void *this, void *callsite)
{
    fprintf(fp, "X%p\n", (int *)this);
}
