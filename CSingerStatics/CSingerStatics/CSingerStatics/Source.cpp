#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 1 //调试时候1， 发布时候0
#define FILE_STU "sgr.txt"
//#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\n"
//#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define JUDGES_COUNT 2
//#define STU_MEMBERS_FULL sgr.no, sgr.name,  sgr.score,sgr.total
//#define STU_MEMBERS_NET sgr.no, sgr.name,  sgr.score
#define LINE  "\n------------------------\n"
typedef struct singer
{
	int no;
	char name[50];
	int score[JUDGES_COUNT];
	int total;
}singer;

singer allsingers[100];
singer sortsingers[100];
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
	printf("歌手编号：%d\t姓名%s\t分数如下：\n", sgr.no, sgr.name);
	for (i = 0; i < JUDGES_COUNT; i++)
		printf("%d\t", sgr.score[i]);
	printf("\n");
}

void displayallsingers()
{
	int i;
	printf("所有%d分数如下\n", allsingerscount);
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		displaysinger(allsingers[i]);
	}
	printf("--------------------------------------------\n");
}

int cmpfunc(const void * a, const void * b)
{
	return ((singer*)a)->total - ((singer*)b)->total;
}
void sorttotal()
{
	int i;
	for (i = 0; i < allsingerscount; i++)
	{
		sortsingers[i] = allsingers[i];
	}
	qsort(sortsingers, allsingerscount, sizeof(singer), cmpfunc);
}

void sortanddisplay()
{
	int i;
	sorttotal();
	printf("排序后如下\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		displaysinger(sortsingers[i]);
	}
	printf("--------------------------------------------\n");
}




float ave()
{
	int i;
	float sum = 0;
	for (i = 0; i < allsingerscount; i++)
		sum += allsingers[i].total;
	return sum / (float)allsingerscount;
}

void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("请输入姓名:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}

void searchtotalbyname(char *name)
{
	int i;
	for (i = 0; i < allsingerscount; i++)
		if (strcmp(name, allsingers[i].name) == 0)
		{
			displaysinger(allsingers[i]);
			return;
		}
	printf("没找到对应歌手的信息。\n");
}

int promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	searchtotalbyname(name);
	return strcmp(name, "q");
}



void searchtotalbyno(int no)
{
	int i;
	for (i = 0; i < allsingerscount; i++)
		if (allsingers[i].no == no)
		{
			displaysinger(allsingers[i]);
			return;
		}
	printf("没找到对应歌手的信息。\n");
}

void promptsearchtotalbyno()
{
	int no;
	printf("请输入要查询的学号:");
	scanf("%d", &no);
	searchtotalbyno(no);
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

void promptremovesinger()
{
	int no;
	printf("请输入要删除的学号:");
	scanf("%d", &no);
	removesinger(no);
}


int login()
{
	char name[50] = "";
	char pwd[50] = "";
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入密码\n");
	scanf("%s", pwd);
	return streq(name, "username")
		&& streq(pwd, "password");
}


int calctotal(int math, int english, int chinese, int c)
{
	return math + english + chinese + c;
}

float calcave(int total)
{
	return total / 4.0f;
}

void addsinger(int no, char name[], int scores[])
{
	int i;
	singer sgr;
	sgr.no = no;
	strcpy(sgr.name, name);
	for (i = 0; i < JUDGES_COUNT; i++)
		sgr.score[i] = scores[i];
	//sgr.score = math;
	//sgr.english = english;
	//sgr.chinese = chinese;
	//sgr.c = c;
	allsingers[allsingerscount++] = sgr;
}

void createsamplesingers()
{
	int scores1[JUDGES_COUNT] = { 11,12 };
	int scores2[JUDGES_COUNT] = { 21,22 };
	printf("创建示例歌手数据...");
	addsinger(1, "name1", scores1);
	addsinger(2, "name2", scores2);
	printf("2条示例歌手数据已创建\n");
}

void calcanddisplaytotalandaverage()
{
	//int i;
	//singer sgr;
	//printf("所有各科总分、平均分如下\n");
	//printf("--------------------------------------------\n");
	//for (i = 0; i < allsingerscount; i++)
	//{
	//	sgr = allsingers[i];
	//	allsingers[i].total = sgr.total = calctotal(sgr.score, sgr.english, sgr.chinese, sgr.c);
	//	allsingers[i].average = sgr.average = calcave(sgr.total);
	//	printf("%d\t%s\t%d\t%.1f\n", sgr.no, sgr.name, sgr.total, sgr.average);
	//}
	//printf("--------------------------------------------\n");
}

void calcanddisplaysubject(char *subuject, int scores[])
{
	int i, sum = 0, below60 = 0;
	for (i = 0; i < allsingerscount; i++)
	{
		sum += scores[i];
		if (scores[i] < 60)
			below60++;
	}
	printf("科目:%s 平均分%.1f、及格率百分之%.1f、不及格率百分之%.1f\n", subuject,
		(sum / (float)allsingerscount),
		(1 - below60 / (float)allsingerscount)*100.0f,
		(below60 / (float)allsingerscount)*100.0f
	);
}


void calcanddisplayallsubjects()
{
	//int i, sum = 0, below60 = 0;
	//int scores[100];
	//singer sgr;
	//printf("所有科目歌手统计如下\n");
	//printf("--------------------------------------------\n");
	//for (i = 0; i < allsingerscount; i++)
	//{
	//	scores[i] = allsingers[i].score;
	//}
	//calcanddisplaysubject("数学", scores);


	//calcanddisplaysubject("C语言", scores);
	//printf("--------------------------------------------\n");
}

void promptaddsinger()
{
	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	printf("\n请输入学号\n");
	scanf("%d", &no);
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入数学、英语、语文、c语言歌手（整数），空格隔开\n");
	scanf("%d%d%d%d", &math, &english, &chinese, &c);
	//addsinger(no, name,null);
	printf("完成第%d个入库录入!\n", allsingerscount);
}


int main()
{
	int choice = -1;

#if DEV

	createsamplesingers();


	////printf("\n%d\n", allsingerscount);
	///*promptaddsinger();
	//writeallsingers();*/
	///*promptremovesinger();
	//writeallsingers();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallsingers();
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
			"按3键：按照学号查询               按8键：保存歌手档案\n"
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
			promptsearchtotalbyname();
			break;
		case 3:
			promptsearchtotalbyno();
			break;
		case 4:
			promptaddsinger();
			break;
		case 5:
			promptremovesinger();
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

