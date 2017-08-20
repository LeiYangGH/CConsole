#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "readstruct.h"
int allstudentscount;
//extern student allstudents[20];
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student b;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(b.name, part);
			break;
		case 2:
			b.age = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return b;
}
void readallstudents(char* filename, student allstudents[20])
{
	char line[200];
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("\nopen %s fail!", filename);
	}
	else
	{
		allstudentscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allstudents[allstudentscount++] = getstudentfromline(line);
		}
		printf("\n read file %s done!", filename);
	}
}
