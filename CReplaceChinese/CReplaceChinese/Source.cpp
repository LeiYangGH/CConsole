#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>

FILE *fin;
FILE *fout;
int q1 = 0;
int q2 = 0;
wchar_t convertpunctuation(wchar_t input)
{
	switch (input)
	{
	case ',':
		return L'£¬';
	case '.':
		return L'¡£';
	case ':':
		return L'£º';
	case '\'':
		q1 = !q1;
		return q1 ? L'¡®' : L'¡¯';
	case '"':
		q2 = !q2;
		return q2 ? L'¡°' : L'¡±';
	default:
		return input;
	}
}

void count_chwords()
{
	int i, j, d, exist;
	char *word;

	wchar_t line[100];
	wchar_t c;
	while (fgetws(line, 100, fin) != NULL)
	{
		for (i = 0; i < wcslen(line); i++)
		{
			c = line[i];
			c = convertpunctuation(c);
			//wprintf(L"%c\n", c);
			fwprintf(fout, L"%lc", c);
		}
	}
}

int main(int argc, char *argv[])
{
	int i, j, exist;
	char inputfilename[255] = "input.txt";
	char outputfilename[255] = "output.txt";
	setlocale(LC_ALL, "chs");

	fin = fopen(inputfilename, "r");
	fout = fopen(outputfilename, "w");

	count_chwords();
	fclose(fin);
	fclose(fout);

	system("pause");
	return 0;
}

