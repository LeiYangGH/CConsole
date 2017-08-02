#include "string.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct pair
{
	int id;
	float value;
}pair;

typedef struct pairfile
{
	char filename[20];
	pair pairs[300];
	int count;
}pairfile;

pairfile pf1;
pairfile pf2;

//split one line of text and return a struct
pair getpairfromline(char *line)
{
	char *part;
	int index = 0;
	pair b;
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

void readallpairs(char *fn, pair cols[], int *cnt)
{
	char line[200];
	FILE *fp = fopen(fn, "r");
	if (fp == NULL)
	{
		printf("\n error open %s!", fn);
	}
	else
	{
		*cnt = 0;
		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 6)
				continue;
			cols[(*cnt)++] = getpairfromline(line);
		}
		fclose(fp);
	}
}

int main()
{
	//printf("len=%d\n", strlen("R_g_hokan.txt"));//13
	strcpy(pf1.filename, "R_g_hokan.txt");
	strcpy(pf2.filename, "R_b_hokan.txt");

	//strcpy(pf1.filename, "f1.dat");
	//strcpy(pf2.filename, "f2.dat");

	//pf1.count = 0;
	//pf2.count = 0;
	//memset(pf1.pairs, 0, 300);
	//memset(pf2.pairs, 0, 300);

	//if reverse the two statements, then read ok
	readallpairs(pf1.filename, pf1.pairs, &pf1.count);
	readallpairs(pf2.filename, pf2.pairs, &pf2.count);

	system("pause");
	return 0;
}
