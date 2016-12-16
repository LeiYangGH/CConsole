#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define MAX_STRLEN 80
#define LEFT_MBracket "["
#define Right_MBracket "]"
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void readinput(char *s)
{
	int c, i = 0;
	FILE *fp;
	fp = fopen(INPUT_FILE, "r");
	if (fp)
	{
		while ((c = getc(fp)) != EOF)
			s[i++] = c;
		fclose(fp);
	}
	else
		printf("没找到input.txt\n");
}

void formatandwrite(char *input, char *output)
{
	FILE *fp;
	char* s;
	char *sp = "\n";
	char *part;
	fp = fopen(OUTPUT_FILE, "w+");
	if (fp)
	{
		s = strtok(input, LEFT_MBracket);
		fprintf(fp, "{\n  [\n");

		s = strtok(NULL, Right_MBracket);

		part = strtok(s, sp);
		while (part != NULL)
		{
			fprintf(fp, "    %s\n", part);
			part = strtok(NULL, sp);
		}
		fprintf(fp, "  ]\n}\n");
	}
	else
		printf("不能创建output.txt\n");
}

int main0()
{
	char input[MAX_STRLEN] = "";
	char output[MAX_STRLEN] = "";
	readinput(input);
	formatandwrite(input, output);
	system("pause");
	return 0;
}
