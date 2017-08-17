#include<stdio.h>
#include<string.h>
#include"assert.h"
#include<stdlib.h>
#include<stdarg.h>
#include<time.h>

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

int rnd() 
{
    int i;
    int min = 5, max =10;
    for(i=0;i<100;i++)
       printf("%d\t",1+rand()%(max-min)+min);
}
char* outstring() 
{
    //char s[] = "hello world\n";
    char* s =(char *)malloc(sizeof(char)*20);
    strcpy(s,"hello world\n");
    return s; 
}
int main()
{
    extern int ext;
    assert(ext==5);

    printf("ext = %d\n",ext);
    int sum = add(2,3,7);

    printf("sum = %d\n",sum);
    srand(time(NULL));
    //rnd();
    printf("%s\n",outstring());
    printf("end");

}

