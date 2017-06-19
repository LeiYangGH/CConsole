#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
int main()
{
	char input[10] = "";
	int num = 0;
	float f = 0;
	while (num <= 0 || num != f)
	{
		printf("请输入一个正整数:");
		fseek(stdin, 0, SEEK_END);
		fgets(input, 80, stdin);
		num = atoi(input);
		f = atof(input);
	}
	printf("num=%d\n", num);
	system("pause");
	return 0;
}

