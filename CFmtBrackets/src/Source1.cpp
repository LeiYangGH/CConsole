#include <stdlib.h>  
#include <stdio.h>  
#define STACK_SIZE  100  

typedef struct {
	char *bs;
	char *tp;
	int sz;
}ST;

int  InitStack(ST &s)
{
	s.bs = (char *)malloc(STACK_SIZE * sizeof(char));
	if (s.bs == NULL)
		return 0;
	s.tp = s.bs;
	s.sz = STACK_SIZE;
	return 0;
}

int Push(ST &s, char c)
{
	if (s.tp - s.bs >= s.sz) {
		s.bs = (char *)realloc(s.bs, (s.sz + 100) * sizeof(char));
	}
	if (s.bs == NULL)
		return 1;
	*s.tp++ = c;
	return 0;
}

int Pop(ST &s, char &c)
{
	if (s.tp == s.bs)
		return 1;
	c = *--s.tp;
	return 0;
}

char opp(char b)
{
	switch (b)
	{
	case '{':
		return '}';
	case '[':
		return ']';
	case '(':
		return ')';
	default:
		break;
	}
}

void identbracket(char b, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf(" ");
	printf("%c", b);
	printf("\n");
}

int main(void)
{
	ST s;

	InitStack(s);
	int i;
	char *pc = "{(([[](){}()[]]))}";//改这个字符串，相当于从文本里读，但目前不支持中间夹其他字符
	char *pcx = pc;
	char c;
	int match = 1;
	int space = 0;
	for (i = 0; pcx[i] != 0; i++)
	{
		if (pcx[i] == '(' || pcx[i] == '[' || pcx[i] == '{')
		{
			Push(s, pcx[i]);
			space += 2;
			identbracket(pcx[i], space);
			if (pcx[i + 1] == NULL)
			{
				printf("括号不匹配");
				match = 0;
				break;
			}
		}
		else
		{
			Pop(s, c);
			c = opp(c);

			identbracket(c, space);
			space -= 2;

			if (c != pcx[i])
			{
				printf("括号不匹配");
				match = 0;
				break;
			}
		}
	}
	if (match == 1)
		printf("括号匹配");
	system("pause");
	return 0;
}