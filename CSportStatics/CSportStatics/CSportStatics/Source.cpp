#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STRLEN 20
#define MAX_SUBJECT_COUNT 6
#define TEAM_FILE "team.txt"
#define PLAYER_FILE "player.txt"
#define TEST 1
typedef struct team
{
	char name[50];
	char leader[50];
	int total;
}team;
team allteams[10];
int allteamscount = 0;
typedef struct result
{
	int playerid;
	int sportid;
	int score;
}result;
result allresults[50];
int allresultscount = 0;
typedef struct player
{
	char name[50];
	char teamname[50];
	int teamid;
}player;

int subjects_count = 3;//默认科目数

player allplayers[50];
int allplayerscount = 0;

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void promptinputsubjectcount()
{
	printf("请输入科目数量（1～6）:");
	scanf("%d", &subjects_count);
	fseek(stdin, 0, SEEK_END);
	if (subjects_count < 1 || subjects_count>6)
		subjects_count = 3;//默认科目数量
}

void displayplayer(player stu)
{
	//int i;
	//printf("\r\n");
	//printf("%s\t%s\t", stu.no, stu.name);
	//for (i = 0; i < subjects_count; i++)
	//{
	//	printf("%d\t", stu.scores[i]);
	//}
	//printf("%d\t%.1f\n", stu.total, stu.average);

}

void displayallplayers()
{
	int i;
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allplayerscount; i++)
	{
		displayplayer(allplayers[i]);
	}
	printf("--------------------------------------------\r\n");
}

team getteamfromline(char *line)
{
	char *part;
	int index = 0;
	team q;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.name, part);
			break;
		case 2:
			strcpy(q.leader, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	q.total = 0;
	return q;
}

void readallteams()
{
	char line[200];
	FILE *fp = fopen(TEAM_FILE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", TEAM_FILE);
		getchar();
		exit(1);
	}
	allteamscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allteams[allteamscount++] = getteamfromline(line);
	}
	printf("\n已读入文件!\n");

}


//////
int getteamidbyname(char *name)
{
	int i;
	for (i = 0; i < allteamscount; i++)
	{
		if (streq(allteams[i].name, name))
		{
			return i;
		}
	}
	printf("\n基础数据中未找到团队名称%s!\n", name);
	return -1;
}
player getplayerfromline(char *line)
{
	char *part;
	int index = 0;
	player q;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.name, part);
			break;
		case 2:
			strcpy(q.teamname, part);
			q.teamid = getteamidbyname(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	//q.total = 0;
	return q;
}

void readallplayers()
{
	char line[200];
	FILE *fp = fopen(PLAYER_FILE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", PLAYER_FILE);
		getchar();
		exit(1);
	}
	allplayerscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allplayers[allplayerscount++] = getplayerfromline(line);
	}
	printf("\n已读入文件!\n");

}

//////
//快速排序用
//int cmpbytotal(const void * a, const void * b)
//{
//	return ((player*)a)->total - ((player*)b)->total;
//}
//
//int cmpbyno(const void * a, const void * b)
//{
//	return ((player*)a)->no - ((player*)b)->no;
//}
//
//void sortanddisplaybytotal()
//{
//	qsort(allplayers, allplayerscount, sizeof(player), cmpbytotal);
//	printf("按总分排序后如下\r\n");
//	displayallplayers();
//}
//
//void sortanddisplaybyno()
//{
//	qsort(allplayers, allplayerscount, sizeof(player), cmpbyno);
//	printf("按学号排序后如下\r\n");
//	displayallplayers();
//}
//
//void countbygradesforonesubject(int subjectId)
//{
//	int i, t, cnt100_90 = 0, cnt89_80 = 0, cnt79_70 = 0, cnt69_60 = 0, cnt59_0 = 0;
//	printf("第%d科目成绩在各分值段的成绩比例统计如下：\r\n", subjectId + 1);
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < allplayerscount; i++)
//	{
//		t = allplayers[i].scores[subjectId];
//		if (t >= 90)
//			cnt100_90++;
//		else if (t >= 80 && t <= 89)
//			cnt89_80++;
//		else if (t >= 70 && t <= 79)
//			cnt79_70++;
//		else if (t >= 60 && t <= 69)
//			cnt69_60++;
//		else if (t < 149)
//			cnt59_0++;
//	}
//	printf("100-90\t89-80\t79-70\t69-60\t59-0\t\n");
//	printf("%d\t%d\t%d\t%d\t%d\n",
//		cnt100_90, cnt89_80, cnt79_70, cnt69_60, cnt59_0);
//	printf("%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\n",
//		cnt100_90 * 100 / (float)allplayerscount,
//		cnt89_80 * 100 / (float)allplayerscount,
//		cnt79_70 * 100 / (float)allplayerscount,
//		cnt69_60 * 100 / (float)allplayerscount,
//		cnt59_0 * 100 / (float)allplayerscount
//	);
//	printf("--------------------------------------------\r\n");
//}
//
//void countbygrades()
//{
//	int i;
//	int totalSubject = 0;
//	float aveSubject;
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < subjects_count; i++)
//	{
//		countbygradesforonesubject(i);
//	}
//	printf("--------------------------------------------\r\n");
//}
//
//void searchtotalbyname(char *name)
//{
//	int i;
//	//先按总分排序
//	qsort(allplayers, allplayerscount, sizeof(player), cmpbytotal);
//	for (i = 0; i < allplayerscount; i++)
//		if (strcmp(name, allplayers[i].name) == 0)
//		{
//			printf("%s,第%d名, 详细如下\n", name, allplayerscount - i);
//			displayplayer(allplayers[i]);
//			return;
//		}
//	printf("没找到对应学生的信息。\r\n");
//}
//
//void promptsearchtotalbyname()
//{
//	char name[MAX_STRLEN] = "";
//	printf("请输入要查询的学生姓名:");
//	scanf("%s", &name);
//	searchtotalbyname(name);
//}
//
//
//void addplayer(char no[], char name[], int scores[])
//{
//	int i;
//	player stu;
//	strcpy(stu.no, no);
//	strcpy(stu.name, name);
//	stu.total = 0;
//	for (i = 0; i < subjects_count; i++)
//	{
//		stu.scores[i] = scores[i];
//		stu.total += scores[i];
//	}
//	for (i = subjects_count; i < MAX_SUBJECT_COUNT; i++)
//	{
//		stu.scores[i] = 0;
//	}
//	stu.average = stu.total / (float)subjects_count;
//	allplayers[allplayerscount++] = stu;
//}
//
//void createsampleplayers()
//{
//	int scores[MAX_SUBJECT_COUNT];
//	printf("创建示例成绩数据...");
//	scores[0] = 93;
//	scores[1] = 96;
//	scores[2] = 91;
//	scores[3] = 0;
//	scores[4] = 0;
//	scores[5] = 0;
//	addplayer("16001123", "Smile", scores);
//	scores[0] = 95;
//	scores[1] = 85;
//	scores[2] = 65;
//	scores[3] = 0;
//	scores[4] = 0;
//	scores[5] = 0;
//	addplayer("20161465", "Shawn", scores);
//	scores[0] = 92;
//	scores[1] = 82;
//	scores[2] = 1;
//	scores[3] = 0;
//	scores[4] = 0;
//	scores[5] = 0;
//	addplayer("30161465", "Tony", scores);
//	//addplayer("16004", "Flex", 91, 81, 61);
//	//addplayer("16005", "Smile5", 63, 63, 66);
//	//addplayer("16006", "Smile6", 96, 83, 63);
//	//addplayer("16007", "Smile7", 93, 83, 56);
//	//addplayer("16008", "Smile8", 97, 83, 73);
//	//addplayer("16009", "Smile9", 55, 55, 58);
//	//addplayer("16010", "Smile10", 13, 13, 43);
//	//allplayerscount = 1;
//	printf("示例成绩数据已创建。\n");
//
//}
//
//void promptaddplayer()
//{
//	int i;
//	char no[MAX_STRLEN];
//	char name[MAX_STRLEN] = "";
//	int scores[MAX_SUBJECT_COUNT];
//	printf("\n请输入学号\n");
//	scanf("%s", &no);
//	printf("\n请输入姓名\n");
//	scanf("%s", name);
//	for (i = 0; i < subjects_count; i++)
//	{
//		printf("\n请输入第%d科成绩（整数）:", i + 1);
//		scanf("%d", &scores[i]);
//	}
//	addplayer(no, name, scores);
//	printf("完成第%d个入库录入!\r\n", allplayerscount);
//}
//
//void calcanddisplaytotalandaverageforonesubject(int subjectId)
//{
//	int i;
//	int totalSubject = 0;
//	float aveSubject;
//	player stu;
//	for (i = 0; i < allplayerscount; i++)
//	{
//		totalSubject += allplayers[i].scores[subjectId];
//	}
//	aveSubject = totalSubject / (float)allplayerscount;
//	printf("%d\t%d\t%.1f\n", subjectId + 1, totalSubject, aveSubject);
//
//}
//
//void calcanddisplaytotalandaverage()
//{
//	int i;
//	int totalSubject = 0;
//	float aveSubject;
//	player stu;
//	printf("科目\t总分\t平均分\n");
//	printf("--------------------------------------------\r\n");
//	for (i = 0; i < subjects_count; i++)
//	{
//		calcanddisplaytotalandaverageforonesubject(i);
//	}
//	printf("--------------------------------------------\r\n");
//}

int main()
{
#if TEST
	readallteams();
	readallplayers();
#else


	int choice = -1;
	promptinputsubjectcount();
	createsampleplayers();
	//system("pause");
	while (choice != 0)
	{
		printf("\n\t 学生成绩输入查询统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 手动录入");
		printf("\n\t 2. 计算每门课程的总分和平均分");
		printf("\n\t 3. 按学生总分由高到低排出名次表");
		printf("\n\t 4. 按学号由小到大排出成绩表");
		printf("\n\t 5. 按姓名查询学生排名及其考试成绩");
		printf("\n\t 6. 统计");
		printf("\n\t 7. 输出");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
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
			promptaddplayer();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			calcanddisplaytotalandaverage();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			sortanddisplaybytotal();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			sortanddisplaybyno();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptsearchtotalbyname();
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			countbygrades();
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			sortanddisplaybyno();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	fseek(stdin, 0, SEEK_END);
#endif // TEST
	system("pause");
	return 0;
}

