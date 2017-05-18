#include "stdlib.h"
#include "string.h"
#include "stdio.h"
 
 
int main(void)
{
	char cmd[80];
	FILE *fp;
	fp = fopen("output.txt", "w");
	while (strcmp(cmd, "end\n") != 0)
	{
		printf("请输入文本并回车，end结束:");
		fgets(cmd, 80, stdin);
		fputs(cmd, fp);
	}
	fclose(fp);
	printf("保存到文件output.txt.\n");
	system("pause");
	return 0;
}
