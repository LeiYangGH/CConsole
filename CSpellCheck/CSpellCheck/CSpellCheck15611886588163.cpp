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
	int indexes[20];
	int count;
}user;


int maxcount = 0;
FILE *fp;

char *dic[] = { "will","at","is","be" };
int diclen = 4;

//int place = 0;

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
	printf("%s\t%ld\n", word, tell);
	//puts(word);
	return strdup(word);
}


void spell_check()
{
	int i, exist;
	char *word;

	while (word = getword())
	{
		//puts(word);
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

	spell_check();
	fclose(fp);





	system("pause");
	return 0;
}

