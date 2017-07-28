#include "memory.h"
#include "math.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "bmp.h"

void setPixel(BYTE bytes[], int w, int x, int y, int r, int g, int b)
{
	int ptr = ((x + (y*w)) * 3);

	bytes[ptr] = b;
	bytes[ptr + 1] = g;
	bytes[ptr + 2] = r;
}

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
		printf("\n error open g!");
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
	}
}

void readallcolorsb()
{
	char line[200];
	FILE *fp = fopen(FILE_b, "r");
	if (fp == NULL)
	{
		printf("\n error open b!");
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
	return 0;
}

float getcolorbidexbyno(int  id)
{
	int i;
	for (i = 0; i < allcolorsbcount; i++)
	{
		if (allcolorsb[i].id == id)
			return allcolorsb[i].value;
	}
	return 0;
}
int main()
{
	int i, id;
	readallcolorsg();
	readallcolorsb();

	BMP bmp;

	bmp.load("t.bmp");//input, width must > height
	int width = bmp.width();
	int height = bmp.height();
	int ch = bmp.channels;
	printf("w=%d\t h=%d\t ch=%d\n", width, height, ch);

	BYTE* bytes = bmp.data();


	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height; h++)
		{
			int ptr = ((w + (h*width)) * 3);

			//bytes[ptr] = b;//red
			bytes[ptr + 1] = getcolorgidexbyno(bytes[ptr + 1]);//green
			bytes[ptr + 2] = getcolorbidexbyno(bytes[ptr + 2]);//blue
		}
	}

	bmp.save("test.bmp");
	system("pause");
	return 0;
}
