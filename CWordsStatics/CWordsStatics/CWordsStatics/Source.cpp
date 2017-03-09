#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>

#define MAX_WORDS 1000
char en[MAX_WORDS][20] = {};
int encount[MAX_WORDS];
int encnt = 0;

wchar_t ch[MAX_WORDS] = {};
int chcount[MAX_WORDS];
int chcnt = 0;

int maxcount = 0;

FILE *fp;
FILE *fpc;

void count_words(FILE *f)
{
	char x[1024];
	while (fscanf(f, " %1023s", x) == 1)
	{
		puts(x);
	}
}


char *getWord()
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

void fgetwsexample()
{
	wchar_t line[100];
	while (fgetws(line, 100, fp) != NULL)
	{
		for (int i = 0; i < wcslen(line); i++)
		{
			int d = line[i];
			if (d >= 19968 && d <= 40869)
				wprintf(L"%c\n", line[i]);
		}
	}
}

void count_enwords()
{
	int i, exist;
	char *word;

	while (word = getWord())
	{
		exist = 0;
		for (int i = 0; i < encnt; i++)
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


	for (int i = 0; i < encnt; i++)
	{
		if (maxcount < encount[i])
			maxcount = encount[i];
		//printf("%s\t%d\n", en[i], encount[i]);

	}
}

void count_chwords()
{
	int i, exist;
	char *word;

	wchar_t line[100];
	wchar_t c;
	while (fgetws(line, 100, fp) != NULL)
	{
		for (int i = 0; i < wcslen(line); i++)
		{
			int d = line[i];
			if (d >= 19968 && d <= 40869)
			{
				c = line[i];
				//wprintf(L"%c\n", c);
				exist = 0;
				for (int i = 0; i < chcnt; i++)
				{
					if (ch[i] == c)
					{
						chcount[i]++;
						exist = 1;
						break;
					}
				}
				if (!exist)
				{
					ch[chcnt] = c;
					chcount[chcnt] = 1;
					chcnt++;
				}
			}
		}
	}

	for (int i = 0; i < chcnt; i++)
	{
		if (maxcount < chcount[i])
			maxcount = chcount[i];
		//wprintf(L"%c\t%d\n", ch[i], chcount[i]);
	}
}

int main()
{
	int i, j, exist;
	char line[200];

	setlocale(LC_ALL, "chs");
	//wchar_t test[] = L"测试Test";
	//wprintf(L"%s", test);

	//fgetwsexample();
	//system("pause");

	fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!");
		getchar();
		exit(1);
	}
	count_enwords();
	fclose(fp);

	fpc = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!");
		getchar();
		exit(1);
	}
	//fgetwsexample();
	count_chwords();
	fclose(fpc);

	for (i = maxcount; i > 0; i--)
	{
		for (j = 0; j < encnt; j++)
		{
			if (encount[j] == i)
				printf("%s\t\t\t%d\n", en[j], encount[j]);
		}
		for (j = 0; j < chcnt; j++)
		{
			if (chcount[j] == i)
				wprintf(L"%c\t\t\t%d\n", ch[j], chcount[j]);
		}
	}

	system("pause");
	return 0;
}

