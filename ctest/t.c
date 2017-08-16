#include<stdio.h>
#include"assert.h"

#include<stdarg.h>

int add(int num,...) 
{
    va_list valist; 
    int sum = 0;
    int i;

    va_start(valist, num);

    for (i = 0; i < num; i++)
    {
       sum += va_arg(valist, int);
    }
    va_end(valist);

    return sum;
}

int main()
{
    extern int ext;
    assert(ext==5);

    printf("ext = %d\n",ext);
    int sum = add(2,3,7);

    printf("sum = %d\n",sum);
    printf("end");

}

