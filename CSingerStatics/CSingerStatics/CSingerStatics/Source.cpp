#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 1 //调试时候1， 发布时候0
#define FILE_STU "sgr.txt"
//#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\n"
//#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\n"
#define MAX_STRLEN 20
#define SINGERS_COUNT 3
#define JUDGES_COUNT 3
//#define STU_MEMBERS_FULL sgr.no, sgr.name,  sgr.score,sgr.total
//#define STU_MEMBERS_NET sgr.no, sgr.name,  sgr.score
#define LINE  "\n------------------------\n"
typedef struct singer
{
	int no;
	char name[50];
	int score[JUDGES_COUNT];
	int total;
	float ave;
}singer;

singer allsingers[SINGERS_COUNT];
//singer sortsingers[SINGERS_COUNT];
int allsingerscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//char *FILE_STU = "sgr.txt";
singer *head;

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

int tofloat(char *s)
{
	char *end;
	return (float)strtol(s, &end, 10);
}

void displaysinger(singer sgr)
{
	int i;
	printf("\n");
	printf("歌手编号：%d\t姓名%s\t分数如下：\n", sgr.no, sgr.name, sgr.total);
	for (i = 0; i < JUDGES_COUNT; i++)
		printf("%d\t", sgr.score[i]);
	printf("\n");
}

void displayallsingers()
{
	int i;
	printf("所有原始成绩如下\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		displaysinger(allsingers[i]);
	}
	printf("--------------------------------------------\n");
}


///////////


void displayallave()
{
	int i;
	singer sgr;
	printf("所有最终成绩如下\n", allsingerscount);
	printf("编号\t姓名\t成绩\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		sgr = allsingers[i];
		printf("%d\t%s\t%.1f\n", sgr.no, sgr.name, sgr.ave);
	}
	printf("--------------------------------------------\n");
}
////////////
int cmpfunc(const void * a, const void * b)
{
	return ((singer*)b)->ave - ((singer*)a)->ave;
}

void displayscoreandrank(singer sgr, int rank)
{
	printf("编号\t姓名\t成绩\t排名\n");
	printf("%d\t%s\t%.1f\t%d\n",
		sgr.no, sgr.name, sgr.ave, rank);
}



//输入歌手信息
void inputname(char str[])
{
	printf("请输入姓名(2-45个字符)，不能带空格、Tab或回车符:");
	scanf("%s", str);
	printf("您输入的姓名为为 %s \n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("请输入分数1～100:");
		scanf("%d", &n);
	}
	return n;
}



int getsingeridexbyid(int no)
{
	int i;
	for (i = 0; i < allsingerscount; i++)
	{
		singer b = allsingers[i];
		if (b.no == no)
			return i;
	}
}

void removesinger(int no)
{
	int i;
	int index;
	index = getsingeridexbyid(no);
	for (i = index; i < allsingerscount - 1; i++)
		allsingers[i] = allsingers[i + 1];
	allsingerscount--;
	printf("删除完毕，剩下%d个。\n", allsingerscount);

}

void inputremovesinger()
{
	int no;
	printf("请输入要删除的编号:");
	scanf("%d", &no);
	removesinger(no);
}


int login()
{
	char name[50] = "";
	char pwd[50] = "";
	printf("\n请输入姓名\n");
	scanf("%s", name);
	printf("\n请输入密码\n");
	scanf("%s", pwd);
	return streq(name, "username")
		&& streq(pwd, "password");
}



void addsinger(int no, char name[], int scores[])
{
	int i;
	singer sgr;
	sgr.no = no;
	strcpy(sgr.name, name);
	for (i = 0; i < JUDGES_COUNT; i++)
		sgr.score[i] = scores[i];
	sgr.total = 0;
	//sgr.score = math;
	//sgr.english = english;
	//sgr.chinese = chinese;
	//sgr.c = c;
	allsingers[allsingerscount++] = sgr;
}

void createsamplesingers()
{
	int scores1[JUDGES_COUNT] = { 11,12,13 };
	int scores2[JUDGES_COUNT] = { 21,22,23 };
	int scores3[JUDGES_COUNT] = { 31,32,33 };
	printf("创建示例歌手数据...");
	addsinger(1, "name1", scores1);
	addsinger(3, "name3", scores3);
	addsinger(2, "name2", scores2);
	printf("2条示例歌手数据已创建\n");
}

void calcandsortaverage()
{
	int i, j, min, max, score;
	for (i = 0; i < allsingerscount; i++)
	{
		min = max = allsingers[i].score[0];//初始值
		allsingers[i].total = 0;
		for (j = 0; j < JUDGES_COUNT; j++)
		{
			score = allsingers[i].score[j];
			allsingers[i].total += score;
			if (min > score)
				min = score;
			if (max < score)
				max = score;
		}
		allsingers[i].total -= (min + max);
		allsingers[i].ave = allsingers[i].total / (float)(JUDGES_COUNT - 2);
	}
	qsort(allsingers, allsingerscount, sizeof(singer), cmpfunc);

}

void calcsortanddisplayaverage()
{
	calcandsortaverage();
	displayallave();
}


void inputaddsinger()
{
	int no; char name[MAX_STRLEN] = "";
	int scores[JUDGES_COUNT] = { 0 };

	printf("\n请输入编号\n");
	scanf("%d", &no);
	printf("\n请输入姓名\n");
	scanf("%s", name);
	printf("\n请输入%d个裁判的成绩(正整数)，空格隔开\n", JUDGES_COUNT);
	////
	scanf("%d%d", &scores[0], &scores[1]);
	addsinger(no, name, scores);
	printf("完成第%d个歌手录入!\n", allsingerscount);
}

void findtotalbyname(char *name)
{
	int i;
	singer sgr;
	calcandsortaverage();
	for (i = 0; i < allsingerscount; i++)
	{
		sgr = allsingers[i];
		if (strcmp(name, allsingers[i].name) == 0)
		{
			displayscoreandrank(sgr, i + 1);
			return;
		}
	}
	printf("没找到对应歌手的信息。\n");
}

int inputfindtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("请输入要查询的歌手的姓名，不带空格，回车结束:");
	scanf("%s", name);
	findtotalbyname(name);
	return strcmp(name, "q");
}



void findtotalbyno(int no)
{
	int i;
	singer sgr;
	calcandsortaverage();
	for (i = 0; i < allsingerscount; i++)
	{
		sgr = allsingers[i];
		if (allsingers[i].no == no)
		{
			displayscoreandrank(sgr, i + 1);
			return;
		}
	}
	printf("没找到对应歌手的信息。\n");
}

void inputfindtotalbyno()
{
	int no;
	printf("请输入要查询的歌手的编号:");
	scanf("%d", &no);
	findtotalbyno(no);
}

int main()
{
	int choice = -1;

#if DEV

	createsamplesingers();


	////printf("\n%d\n", allsingerscount);
	///*inputaddsinger();
	//writeallsingers();*/
	///*inputremovesinger();
	//writeallsingers();*/
	////inputfindtotalbyname();
	////inputfindtotalbyno();

	displayallsingers();

	calcsortanddisplayaverage();
	//findtotalbyno(3);
	//inputfindtotalbyno();
	inputfindtotalbyname();
	//calcanddisplaytotalandaverage();
	//sortanddisplay();
	//calcanddisplayallsubjects();

	//countbygrades();
#else
	while (choice != 0)
	{
		char *menu = "**********************菜单****************************\n"
			"按1键：读入歌手档案               按6键：学科及格概率\n"
			"按2键：按照姓名查询               按7键：歌手档案排序\n"
			"按3键：按照编号查询               按8键：保存歌手档案\n"
			"按4键：添加歌手档案               按9键 : 查看歌手档案\n"
			"按5键：删除歌手档案               按10键：求各科平均分\n"
			"按0键：退出管理系统";
		printf("请输入选择数字，并回车\n", menu);
		printf("%s\n", menu);
		choice = getchar();
		switch (choice)
		{
		case 0:
			system("pause");
			exit(0);
			break;
		case 1:

			break;
		case 2:
			inputfindtotalbyname();
			break;
		case 3:
			inputfindtotalbyno();
			break;
		case 4:
			inputaddsinger();
			break;
		case 5:
			inputremovesinger();
			break;
		case 6:

			break;
		case 7:
			sortanddisplay();
			break;
		case 8:

			break;
		case 9:
			sortanddisplay();
			break;
		case 10:
			calcanddisplaytotalandaverage();
			calcanddisplayallsubjects();

			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
}
#endif
	//fseek(stdin, 0, SEEK_END);
	printf("\n\n按任意键退出\n");
	system("pause");
	return 0;
}

