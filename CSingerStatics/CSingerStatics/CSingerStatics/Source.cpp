#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //调试时候1， 发布时候0
#define MAX_STRLEN 20
#define SINGERS_COUNT 10
#define JUDGES_COUNT 10
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
int allsingerscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaysinger(singer sgr)
{
	int i;
	printf("\n");
	printf("歌手编号：%d\t姓名：%s\t分数如下：\n", sgr.no, sgr.name, sgr.total);
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

void addsinger(int no, char name[], int scores[])
{
	int i;
	singer sgr;
	sgr.no = no;
	strcpy(sgr.name, name);
	for (i = 0; i < JUDGES_COUNT; i++)
		sgr.score[i] = scores[i];
	sgr.total = 0;
	allsingers[allsingerscount++] = sgr;
}

void createsamplesingers()
{
	int scores1[JUDGES_COUNT] = { 11,12,13,14,15,16,17,18,19,91 };
	int scores2[JUDGES_COUNT] = { 21,22,23,24,25,26,27,28,29,92 };
	int scores3[JUDGES_COUNT] = { 31,32,33,34,35,36,37,38,39,93 };
	int scores4[JUDGES_COUNT] = { 41,42,44,44,45,46,47,48,49,94 };
	int scores5[JUDGES_COUNT] = { 51,52,55,55,55,56,57,58,59,95 };
	int scores6[JUDGES_COUNT] = { 61,62,66,66,66,66,67,68,69,96 };
	int scores7[JUDGES_COUNT] = { 71,72,77,77,77,77,77,78,79,97 };
	int scores8[JUDGES_COUNT] = { 81,82,88,88,88,88,88,88,89,98 };

	printf("创建示例歌手数据...");
	addsinger(1, "name1", scores1);
	addsinger(3, "name3", scores3);
	addsinger(2, "name2", scores2);
	addsinger(4, "name4", scores4);
	addsinger(5, "name5", scores5);
	addsinger(6, "name6", scores6);
	addsinger(7, "name7", scores7);
	addsinger(8, "name8", scores8);
	printf("8条示例歌手数据已创建\n");
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
	scanf("%d%d%d%d%d%d%d%d%d%d", &scores[0], &scores[1], &scores[2], &scores[3], &scores[4], &scores[5], &scores[6], &scores[7], &scores[8], &scores[9]);
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
	createsamplesingers();

#if DEV

	inputaddsinger();

	displayallsingers();

	calcsortanddisplayaverage();
	//findtotalbyno(3);
	//inputfindtotalbyno();
	inputfindtotalbyname();
	//calcanddisplaytotalandaverage();
	//sortanddisplay();
#else
	while (choice != 0)
	{
		printf("\n\t 歌唱比赛评分");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入新一个歌手的成绩");
		printf("\n\t 2. 查看所有歌手的成绩");
		printf("\n\t 3. 计算排序输出成绩");
		printf("\n\t 4. 根据歌手编号查找");
		printf("\n\t 5. 根据歌手名字查找");
		printf("\n\n  请选择: ");
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			inputaddsinger();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallsingers();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			calcsortanddisplayaverage();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			inputfindtotalbyno();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			inputfindtotalbyname();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
	}
#endif
	system("pause");
	return 0;
}

