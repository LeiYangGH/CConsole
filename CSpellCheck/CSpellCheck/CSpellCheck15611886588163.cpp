#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>

#define MAX_WORD_Length 30 //单词最长长度
#define MAX_WRONGWORD_COUNT 100 //最多多少个错误单词
#define MAX_DIC_COUNT 100 //最多多少个字典单词
#define FILE_DICTIONARY "dictionary.txt" //最多多少个字典单词
#define FILE_ARTICAL "article.txt" //最多多少个字典单词
#define FILE_MISS "misspelling.txt" //最多多少个字典单词


typedef struct
{
	char word[MAX_WORD_Length];
	long int indexes[MAX_WORD_Length];
	int count;
}wrong;
wrong allwrongs[MAX_WRONGWORD_COUNT];
int allwrongscount = 0;

FILE *fpa;

char dic[MAX_WRONGWORD_COUNT][MAX_WORD_Length];// = { "i","am","is","be" };
int diclen = 0;

void spell_check(char word[MAX_WORD_Length], long int place)
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

char *getword(char word1[MAX_WORD_Length], long int *place)
{
	char w[MAX_WORD_Length];
	int ch, i = 0;

	while (EOF != (ch = fgetc(fpa)) && !isalpha(ch));
	if (ch == EOF)
		return NULL;
	do
	{
		w[i++] = tolower(ch);
	} while (EOF != (ch = fgetc(fpa)) && isalpha(ch));
	w[i] = '\0';
	*place = ftell(fpa) - strlen(w);
	//printf("%s\t%ld\n", word, tell);
	strcpy(word1, strdup(w));
}

void interate_words()
{
	int i, exist;
	long int place;
	char word[MAX_WORD_Length];

	while (getword(word, &place))
	{
		spell_check(word, place);
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
	FILE *fpr = fopen(FILE_MISS, "w");
	for (i = 0; i < allwrongscount; i++)
	{
		printf("%s ", allwrongs[i].word);
		fprintf(fpr,"%s ", allwrongs[i].word);
		for (j = 0; j < allwrongs[i].count; j++)
		{
			printf("%ld ", allwrongs[i].indexes[j]);
			fprintf(fpr, "%ld ", allwrongs[i].indexes[j]);
		}
		printf("\n");
		fprintf(fpr, "\n");
	}
	fclose(fpr);
}

void readdic()
{
	char d[MAX_DIC_COUNT];
	FILE *fpd = fopen(FILE_DICTIONARY, "r");
	if (fpd == NULL)
	{
		printf("\n打开文件%s失败!", FILE_DICTIONARY);
	}
	else
	{
		diclen = 0;
		while (fgets(d, MAX_WORD_Length, fpd) != NULL)
		{
			d[strcspn(d, "\r\n")] = 0;
			strcpy(dic[diclen++], d);
		}
	}
	fclose(fpd);
}

int main(int argc, char *argv[])
{
	readdic();
	fpa = fopen(FILE_ARTICAL, "r");
	if (fpa == NULL)
	{
		printf("\n打开文件%s失败!", FILE_ARTICAL);
		getchar();
		exit(1);
	}
	init();
	interate_words();
	fclose(fpa);
	showresult();
	system("pause");
	return 0;
}

