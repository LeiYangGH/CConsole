#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>

FILE *fin;
FILE *fout;

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
			if (c == '.')
				c = L'¡£';
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

