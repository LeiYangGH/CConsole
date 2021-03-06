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
		return L'��';
	case '.':
		return L'��';
	case ':':
		return L'��';
	case '\'':
		q1 = !q1;
		return (q1 ? L'��' : L'��');
	case '"':
		q2 = !q2;
		return q2 ? L'��' : L'��';
	default:
		return input;
	}
}

void trimparagraphendspaces(wchar_t line[])
{
	int i;
	for (i = wcslen(line) - 2; i >= 0; i--)
	{
		if (line[i] != L' ')
		{
			line[i + 1] = L'\r';
			line[i + 2] = L'\n';
			line[i + 3] = L'\0';
			break;
		}
	}
}

void keepparagraphstart2spaces(wchar_t line[])
{
	int i, j;
	while (isspace(line[0]))
	{
		for (i = 0; i < wcslen(line); i++)
		{
			line[i] = line[i + 1];
		}
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
		if (wcslen(line) <= 1)
			continue;
		trimparagraphendspaces(line);
		if (wcslen(line) <= 1)
			continue;
		keepparagraphstart2spaces(line);
		if (wcslen(line) <= 1)
			continue;
		fwprintf(fout, L"%lc", L' ');
		fwprintf(fout, L"%lc", L' ');
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
	char inputfilename[255] = "C:\\input.txt";
	char outputfilename[255] = "C:\\output.txt";
	setlocale(LC_ALL, "chs");

	fin = fopen(inputfilename, "r");
	fout = fopen(outputfilename, "w");

	count_chwords();
	fclose(fin);
	fclose(fout);

	system("pause");
	return 0;
}

