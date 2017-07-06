#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>

#define MAX_WORDS 1000
char en[MAX_WORDS][20];
int encount[MAX_WORDS];
int encnt = 0;



int maxcount = 0;

FILE *fp;

char *getword()
{
	char word[100];
	int ch, i = 0;

	while (EOF != (ch = fgetc(fp)) && !isalpha(ch));
	if (ch == EOF)
		return NULL;
	do
	{
		word[i++] = tolower(ch);
	} while (EOF != (ch = fgetc(fp)) && isalpha(ch));

	word[i] = '\0';
	return strdup(word);
}


void count_enwords()
{
	int i, exist;
	char *word;

	while (word = getword())
	{
		exist = 0;
		for (i = 0; i < encnt; i++)
		{
			if (strcmp(en[i], word) == 0)
			{
				encount[i]++;
				exist = 1;
				break;
			}
		}
		if (!exist)
		{
			strcpy(en[encnt], word);
			encount[encnt] = 1;
			encnt++;
		}
	}


	for (i = 0; i < encnt; i++)
	{
		if (maxcount < encount[i])
			maxcount = encount[i];
		//printf("%s\t%d\n", en[i], encount[i]);

	}
}


int main(int argc, char *argv[])
{
	int i, j, exist;
	char filename[255] = "input.txt";


	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!");
		getchar();
		exit(1);
	}

	count_enwords();
	fclose(fp);



	for (i = maxcount; i > 0; i--)
	{
		for (j = 0; j < encnt; j++)
		{
			if (encount[j] == i)
				printf("%s\t\t\t%d\n", en[j], encount[j]);
		}

	}

	system("pause");
	return 0;
}

