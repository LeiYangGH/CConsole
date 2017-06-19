#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int isnum(char input[80])
{
	int i;
	for (i = 0; i < strlen(input); i++)
	{
		if (!isdigit(input[i]))
			return 0;
	}
	return 1;

}

void input1()
{
	char input[80] = "";
	int num = 0;
	float f = 0;
	fgets(input, 80, stdin);
	//strtok(input, "\n");
	input[strcspn(input, "\r\n")] = 0;//删除末尾的回车换行符
	if (!strcmp(input, "") == 0 && isnum(input))//如果不为空、且全是数字
	{
		num = atoi(input);
		printf("n=%d\n", num);
	}
	else
		printf("is not a number\n", num);
}

void input2()
{
	char input[80] = "";
	int num = 0;
	float f = 0;
	fgets(input, 80, stdin);
	//strtok(input, "\n");
	input[strcspn(input, "\r\n")] = 0;//删除末尾的回车换行符
	num = atoi(input);
	while (!(!strcmp(input, "") == 0 && isnum(input) && num > 0))
	{
		printf("NA\n", num);
		fgets(input, 80, stdin);
		input[strcspn(input, "\r\n")] = 0;//删除末尾的回车换行符
		num = atoi(input);
	}
	printf("n=%d\n", num);

}

int main()
{
	input1();
	input2();

	system("pause");
	return 0;
}

