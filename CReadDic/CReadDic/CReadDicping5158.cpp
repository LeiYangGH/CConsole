#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_g "R_g_hokan.txt"
#define FILE_b "R_b_hokan.txt"
typedef struct color
{
	int id;
	float value;
}color;

color allcolorsg[300];
int allcolorsgcount = 0;
color allcolorsb[300];
int allcolorsbcount = 0;


color getcolorfromline(char *line)
{
	char *part;
	int index = 0;
	color b;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			b.id = atoi(part);
			break;
		case 2:
			b.value = atof(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return b;
}

void readallcolorsg()
{
	char line[200];
	FILE *fp = fopen(FILE_g, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_g);
	}
	else
	{
		allcolorsgcount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 6)
				continue;
			allcolorsg[allcolorsgcount++] = getcolorfromline(line);
		}
		printf("\n已读入文件!", FILE_g);
	}
}

void readallcolorsb()
{
	char line[200];
	FILE *fp = fopen(FILE_b, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_b);
	}
	else
	{
		allcolorsbcount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 6)
				continue;
			allcolorsb[allcolorsbcount++] = getcolorfromline(line);
		}
		printf("\n已读入文件!", FILE_g);
	}
}

float getcolorgidexbyno(int  id)
{
	int i;
	for (i = 0; i < allcolorsgcount; i++)
	{
		if (allcolorsg[i].id == id)
			return allcolorsg[i].value;
	}
	return 0;//没找到
}

float getcolorbidexbyno(int  id)
{
	int i;
	for (i = 0; i < allcolorsbcount; i++)
	{
		if (allcolorsb[i].id == id)
			return allcolorsb[i].value;
	}
	return 0;//没找到
}

int main()
{
	int i, id;
	readallcolorsg();
	readallcolorsb();
	for (i = 0; i < 3; i++)
	{
		printf("请输入g列1的值：");
		fseek(stdin, 0, SEEK_END);
		scanf("%d", &id);
		float v = getcolorgidexbyno(id);
		printf("value=%f\n", v);
	}
	for (i = 0; i < 3; i++)
	{
		printf("请输入b列1的值：");
		fseek(stdin, 0, SEEK_END);
		scanf("%d", &id);
		float v = getcolorbidexbyno(id);
		printf("value=%f\n", v);
	}
	system("pause");
	return 0;
}

