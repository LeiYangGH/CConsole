#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>

#define MAX_WORDS 1000
//char en[MAX_WORDS][20];
//int encount[MAX_WORDS];
//int encnt = 0;

typedef struct
{
	char word[20];
	long int indexes[20];
	int count;
}wrong;
wrong allwrongs[100];
int allwrongscount = 0;

int maxcount = 0;
FILE *fp;

char dic[100][20];// = { "i","am","is","be" };
int diclen = 0;

//int place = 0;

void spell_check(char word[20], long int place)
{
	int i, found = 0, recorded = 0;
	for (i = 0; i < strlen(word); i++)
	{
		word[i] = tolower(word[i]);
	}
	for (i = 0; i < diclen; i++)
	{
		if (strcmp(word, dic[i]) == 0)
		{
			found = 1;
			break;
		}
	}
	if (!found)
	{
		for (i = 0; i < allwrongscount; i++)
		{
			if (strcmp(word, allwrongs[i].word) == 0)
			{
				allwrongs[i].indexes[allwrongs[i].count++] = place;
				recorded = 1;
				break;
			}
		}
		if (!recorded)
		{
			wrong w;
			strcpy(w.word, word);
			w.count = 1;
			w.indexes[0] = place;
			allwrongs[allwrongscount++] = w;
		}
	}
}

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
	long int tell = ftell(fp) - strlen(word);
	//printf("%s\t%ld\n", word, tell);
	spell_check(word, tell);
	//puts(word);
	return strdup(word);
}



void interate_words()
{
	int i, exist;
	char *word;

	while (word = getword())
	{
		//puts(word);
	}


}

void init()
{
	int i;
	allwrongscount = 0;
	for (i = 0; i < allwrongscount; i++)
	{
		allwrongs[i].count = 0;
	}
}

void showresult()
{
	int i, j;
	for (i = 0; i < allwrongscount; i++)
	{
		printf("%s ", allwrongs[i].word);
		for (j = 0; j < allwrongs[i].count; j++)
		{
			printf("%ld ", allwrongs[i].indexes[j]);
		}
		printf("\n");
	}
}

void readdic()
{
	char line[200];
	FILE *fpd = fopen("dictionary.txt", "r");
	if (fpd == NULL)
	{
		printf("\n打开文件%s失败!", "dictionary.txt");
	}
	else
	{
		diclen = 0;

		while (fgets(line, 20, fpd) != NULL)
		{
			line[strcspn(line, "\r\n")] = 0;
			strcpy(dic[diclen++], line);
		}
		//printf("\n已读入字典文件!");
	}
	fclose(fpd);
}

int main(int argc, char *argv[])
{
	int i, j, exist;

	readdic();

	fp = fopen("article.txt", "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!");
		getchar();
		exit(1);
	}
	init();
	interate_words();
	fclose(fp);
	showresult();
	system("pause");
	return 0;
}

