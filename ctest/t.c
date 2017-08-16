#include<stdio.h>
#include"assert.h"
int main()
{
    extern int ext;
    assert(ext==51);
    printf("ext = %d\n",ext);
    printf("end");

}

