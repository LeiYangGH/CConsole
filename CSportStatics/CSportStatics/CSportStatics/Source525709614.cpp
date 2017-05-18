#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define MAX_STRLEN 20

typedef struct player
{
	char name[MAX_STRLEN];
	int a;
	int b;
	int c;
	float f;
}player;
player allplayers[100];
int allplayerscount = 0;

int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

float tofloat(char *s)
{
	double temp = strtod(s, NULL);
	return atof(s);
}

void displayplayer(player p)
{
	printf("\r\n");
	printf("%16s\t%d\t%d\t%d\t%.2f\n", p.name, p.a, p.b, p.c, p.f);
}

void displayallplayers()
{
	int i;
	printf("����%dλ���Ƿ�������\r\n", allplayerscount);
	printf("%16s\t����1\t����\t����\tЧ��4\n", "����");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allplayerscount; i++)
	{
		displayplayer(allplayers[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}


player getplayerfromline(char *line)
{
	char *part;
	int index = 0;
	player p;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(p.name, part);
			break;
		case 2:
			p.a = toint(part);
			break;
		case 3:
			p.b = toint(part);
			break;
		case 4:
			p.c = toint(part);
			break;
		case 5:
			p.f = tofloat(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	return p;
}

int cmpstuavefunc(const void * b, const void * a)
{
	return (((player*)a)->b - ((player*)b)->b);
}
void sortbyb()
{
	qsort(allplayers, allplayerscount, sizeof(player), cmpstuavefunc);
}

void readallplayers()
{
	char line[200];
	FILE *fp = fopen(FILE_INPUT, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��(���س�����ʼ��������)!", FILE_INPUT);
		getchar();
	}
	else
	{
		allplayerscount = 0;
		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			++allplayerscount;
			allplayers[allplayerscount - 1] = getplayerfromline(line);
		}
		sortbyb();
	}
}

void writeallplayers()
{
	int i;
	player p;
	FILE *fp = fopen(FILE_INPUT, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_INPUT);
		getchar();
		exit(1);
	}
	for (i = 0; i < allplayerscount; i++)
	{
		p = allplayers[i];
		fprintf(fp, "%s\t%d\t%d\t%d\t%.2f\n", p.name, p.a, p.b, p.c, p.f);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void addplayer(char name[], int i1, int i2, int i3, float f)
{
	player p;
	strcpy(p.name, name);
	p.a = i1;
	p.b = i2;
	p.c = i3;
	p.f = f;
	allplayers[allplayerscount++] = p;
	sortbyb();
	writeallplayers();
}

void promptaddplayer()
{
	char name[MAX_STRLEN] = "";
	int   a, b, c;
	float f;
	printf("\n��������Ա���� ���볡���� ������ ���������ո�������س�����\n");
	scanf("%s%d%d%d", name, &a, &b, &c);
	f = (float)(b + c) / (float)a;
	addplayer(name, a, b, c, f);
	printf("��ɵ�%d�����ǳɼ�¼��!\r\n", allplayerscount);
}


void promptaddplayersfirsttime()
{
	int i, n;
	if (allplayerscount > 0)
		return;
	printf("\n����ָ��Ҫ������ٸ����ǵ�����:");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		promptaddplayer();
}
void searchtotalbyname(char *name)
{
	int i;
	for (i = 0; i < allplayerscount; i++)
		if (strcmp(name, allplayers[i].name) == 0)
		{
			printf("%s,��%d��, ��ϸ����\n", name, allplayerscount - i);
			displayplayer(allplayers[i]);
			return;
		}
	printf("û�ҵ���Ӧ���ǵ���Ϣ��\r\n");
}

void promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("������Ҫ��ѯ����������:");
	scanf("%s", &name);
	searchtotalbyname(name);
}

int main()
{
	int choice = -1;
	printf("\n��ʼ���ļ�...\n");
	readallplayers();
	promptaddplayersfirsttime();
	printf("\n���ļ�������\n");

	while (choice != 0)
	{
		printf("\n��ӭʹ��ŷ�����������������ݰ����ϵͳ\n");
		printf("****************************************\n");
		printf("\t 1.�鿴�����\n");
		printf("\t 2.������ϲ������Ա����\n");
		printf("\t 3.�����Ա������������\n");
		printf("\t 4.�˳�ϵͳ\n");
		printf("����������ָ����ţ�\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '1':
			printf("\n\n��ѡ���� 1\n");
			displayallplayers();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptsearchtotalbyname();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptaddplayer();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			printf("\n\n��л��ʹ�ñ�ϵͳ���ڴ��������´��ٻᡣ");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	system("pause");
	return 0;
}
