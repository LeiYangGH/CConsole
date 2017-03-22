#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define TEAM_FILE "team.txt"
#define PLAYER_FILE "player.txt"
#define SPORT_FILE "sport.txt"
#define RESULT_FILE "result.txt"
#define TEST 1
typedef struct team
{
	char name[20];
	char leader[20];
	int points;
	int order;
}team;
team allteams[10];
int allteamscount = 0;

typedef struct sport
{
	char name[20];
}sport;
sport allsports[10];
int allsportscount = 0;

typedef struct result
{
	char playername[20];
	char sportname[20];
	int score;
	int order;
	int points;
}result;
result allresults[50];
int allresultscount = 0;

typedef struct player
{
	char name[50];
	char teamname[50];
	int points;
	int order;
}player;
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

void displayresult(result re)
{
	printf("%s\t%s\t%d\n", re.playername, re.sportname, re.score);
}

void displayallresults()
{
	int i;
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allresultscount; i++)
	{
		displayresult(allresults[i]);
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
	q.points = 0;
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


void readallsports()
{
	char line[200];
	FILE *fp = fopen(SPORT_FILE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", SPORT_FILE);
		getchar();
		exit(1);
	}
	allsportscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 2)
			continue;
		sport q;
		strcpy(q.name, strtok(line, "\t\n"));
		allsports[allsportscount++] = q;
	}
	printf("\n已读入文件!\n");

}

//////
//int getteamidbyname(char *name)
//{
//	int i;
//	for (i = 0; i < allteamscount; i++)
//	{
//		if (streq(allteams[i].name, name))
//		{
//			return i;
//		}
//	}
//	printf("\n基础数据中未找到团队名称%s!\n", name);
//	return -1;
//}
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
//**///
result getresultfromline(char *line)
{
	char *part;
	int index = 0;
	result q;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.playername, part);
			break;
		case 2:
			strcpy(q.sportname, part);
			break;
		case 3:
			q.score = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	return q;
}

void readallresults()
{
	char line[200];
	FILE *fp = fopen(RESULT_FILE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", RESULT_FILE);
		getchar();
		exit(1);
	}
	allresultscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allresults[allresultscount++] = getresultfromline(line);
	}
	printf("\n已读入文件!\n");

}

int checkplayerexists(char *name)
{
	int i;
	for (i = 0; i < allplayerscount; i++)
	{
		if (streq(allplayers[i].name, name))
		{
			return 1;
		}
	}
	printf("\n基础数据中未找到选手%s!\n", name);
	return 0;
}

int checksportexists(char *name)
{
	int i;
	for (i = 0; i < allsportscount; i++)
	{
		if (streq(allsports[i].name, name))
		{
			return 1;
		}
	}
	printf("\n基础数据中未找到比赛%s!\n", name);
	return 0;
}

int checkplayersportexists(char *playername, char *sportname)
{
	int i;
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].playername, playername)
			&& streq(allresults[i].sportname, sportname))
		{
			printf("\n同一选手不能多次参加同一比赛!\n");
			return 1;
		}
	}
	return 0;
}

int checksportscoreexists(char *sportname, int score)
{
	int i;
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].sportname, sportname)
			&& allresults[i].score == score)
		{
			printf("\n同一比赛分数必须唯一，否则无法计算排名!\n");
			return 1;
		}
	}
	return 0;
}

void appendresult(result re)
{
	FILE *fp = fopen(RESULT_FILE, "a");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", RESULT_FILE);
		getchar();
		exit(1);
	}
	fprintf(fp, "%s\t%s\t%d\n", re.playername, re.sportname, re.score);
	fclose(fp);
	printf("已保存成绩到文件。");
}

void addresult(char *playername, char *sportname, int score)
{
	int i;
	if (checkplayerexists(playername)
		&& checksportexists(sportname)
		&& !checkplayersportexists(playername, sportname)
		&& !checksportscoreexists(sportname, score))
	{
		result re;
		strcpy(re.playername, playername);
		strcpy(re.sportname, sportname);
		re.score = score;
		//
		allresults[allresultscount++] = re;
		appendresult(re);
		//printf("\n比赛成绩添加成功!\n");
	}
}


void promptaddresult()
{
	char playername[20] = "";
	char sportname[20] = "";
	int score = 0;
	printf("请依次输入选手姓名、比赛项目、得分（整数），空格隔开，回车结束:");
	scanf("%s%s%d", playername, sportname, &score);
	fseek(stdin, 0, SEEK_END);
	addresult(playername, sportname, score);
}

//**//
//////
//快速排序用
//int cmpbytotal(const void * a, const void * b)
//{
//	return ((player*)a)->total - ((player*)b)->total;
//}
//

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
int cmpbyscoredesc(const void * a, const void * b)
{
	return *(int*)b - *(int*)a;
}
void sortandgetorders(int scores[], int scorescnt, int orders[])//init -1
{
	int i, s;
	int sortscores[100] = { -1 };//
	for (i = 0; i < scorescnt; i++)
	{
		sortscores[i] = scores[i];
	}
	qsort(sortscores, scorescnt, sizeof(int), cmpbyscoredesc);
	for (i = 0; i < scorescnt; i++)
		for (s = 0; s < scorescnt; s++)
		{
			//printf("scores[%d]=%d\tsortscores[%d]=%d\n", i, scores[i], s, sortscores[s]);

			if (scores[i] == sortscores[s])
			{
				orders[i] = s + 1;
				break;
			}
		}
	//printf("%d\t", nums[i]);

}

void setresultorderpointsvalue(char *playername, char *sportname, int order, int points)
{

}
void calcresultorderpointsbysport(char *sportname)
{
	int i;
	int t1, t2, t3;
	int playerinsportcnt = 0;
	int copyscores[100];
	result copyresults[100];
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].sportname, sportname))
		{
			copyresults[i] = allresults[i];
			playerinsportcnt++;
		}
	}
	if (playerinsportcnt <= 0)
		return;
	for (i = 0; i < playerinsportcnt; i++)
	{
		copyscores[i] = copyresults[i].score;
	}
	//sortandgettop3(copyscores, playerinsportcnt, &t1, &t2, &t3);
	//if (playerinsportcnt >= 3)
	//{

	//}
	//else
}

int main()
{
	int choice = -1;
	//readallteams();
	//readallsports();
	//readallplayers();
	//readallresults();
	//displayallresults();


#if TEST
	int i;
	int n = 1;
	int orders[100] = { 0 };
	int nums[] = { 24 };
	sortandgetorders(nums, n, orders);
	//for (i = 0; i < n; i++)
	//{
	//	printf("%d\n", nums[i]);
	//}
	for (i = 0; i < n; i++)
	{
		printf("%d\t", orders[i]);
	}


	//addresult("p1", "s1", 11);
	//addresult("p1", "s2", 12);
	//addresult("p2", "s1", 21);

	//promptaddresult();
	//addresult("p2", "s3", 22);
	//writeallresults();
#else



	while (choice != 0)
	{
		printf("\n\t 比赛成绩录入统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入成绩");
		printf("\n\t 2. 查看所有成绩");
		//printf("\n\t 3. 按学生总分由高到低排出名次表");
		//printf("\n\t 4. 按学号由小到大排出成绩表");
		//printf("\n\t 5. 按姓名查询学生排名及其考试成绩");
		//printf("\n\t 6. 统计");
		//printf("\n\t 7. ");
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
			promptaddresult();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallresults();
			break;
			//case '3':
			//	printf("\n\n你选择了 3\n");
			//	sortanddisplaybytotal();
			//	break;
			//case '4':
			//	printf("\n\n你选择了 4\n");
			//	sortanddisplaybyno();
			//	break;
			//case '5':
			//	printf("\n\n你选择了 5\n");
			//	promptsearchtotalbyname();
			//	break;
			//case '6':
			//	printf("\n\n你选择了 6\n");
			//	countbygrades();
			//	break;
			//case '7':
			//	printf("\n\n你选择了 7\n");
			//	sortanddisplaybyno();
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

