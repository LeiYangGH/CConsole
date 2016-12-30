#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void delchar(char *str, char c)
{
	char  *p, *q;
	for (p = str, q = str; *p != '\0'; p++)
		if (*p != c)*q++ = *p;
	*q = *p;
}
int main()
{
	char str[100], c;
	puts("请输入str，回车结束:");
	//有些编译器不支持gets，
	//而scanf又不能输入带空格的字符串
	fgets(str, 100, stdin);
	printf("删除前的字符串：\n%s\n", str);
	//清除缓冲区避免影响后面输入
	fseek(stdin, 0, SEEK_END);
	printf("输入要删除的字符，回车结束:");
	c = getchar();
	delchar(str, c);
	printf("删除后的字符串：\n%s\n", str);
	system("pause");
	return 0;
}

