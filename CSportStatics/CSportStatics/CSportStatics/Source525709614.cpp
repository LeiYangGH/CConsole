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
	printf("所有%d位球星分数如下\r\n", allplayerscount);
	printf("%16s\t场次1\t进球\t助攻\t效率4\n", "姓名");
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
		printf("\n打开文件%s失败(按回车键开始输入数据)!", FILE_INPUT);
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
		printf("\n打开文件%s失败!", FILE_INPUT);
		getchar();
		exit(1);
	}
	for (i = 0; i < allplayerscount; i++)
	{
		p = allplayers[i];
		fprintf(fp, "%s\t%d\t%d\t%d\t%.2f\n", p.name, p.a, p.b, p.c, p.f);
	}
	fclose(fp);
	printf("已保存记录到文件。");
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
	printf("\n请输入球员姓名 参与场次数 进球数 助攻数，空格隔开，回车结束\n");
	scanf("%s%d%d%d", name, &a, &b, &c);
	f = (float)(b + c) / (float)a;
	addplayer(name, a, b, c, f);
	printf("完成第%d个球星成绩录入!\r\n", allplayerscount);
}


void promptaddplayersfirsttime()
{
	int i, n;
	if (allplayerscount > 0)
		return;
	printf("\n请先指定要输入多少个球星的数据:");
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
			printf("%s,第%d名, 详细如下\n", name, allplayerscount - i);
			displayplayer(allplayers[i]);
			return;
		}
	printf("没找到对应球星的信息。\r\n");
}

void promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("请输入要查询的球星姓名:");
	scanf("%s", &name);
	searchtotalbyname(name);
}

int main()
{
	int choice = -1;
	printf("\n开始读文件...\n");
	readallplayers();
	promptaddplayersfirsttime();
	printf("\n读文件结束！\n");

	while (choice != 0)
	{
		printf("\n欢迎使用欧洲足球联赛进球数据榜操作系统\n");
		printf("****************************************\n");
		printf("\t 1.查看进球榜单\n");
		printf("\t 2.查找您喜爱的球员数据\n");
		printf("\t 3.添加球员赛季进球数据\n");
		printf("\t 4.退出系统\n");
		printf("请输入您的指令代号：\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '1':
			printf("\n\n你选择了 1\n");
			displayallplayers();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptsearchtotalbyname();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptaddplayer();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			printf("\n\n感谢您使用本系统，期待与您的下次再会。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	system("pause");
	return 0;
}
