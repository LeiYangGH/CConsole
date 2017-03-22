#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define TEAM_FILE "team.txt"
#define PLAYER_FILE "player.txt"
#define SPORT_FILE "sport.txt"
#define RESULT_FILE "result.txt"
#define TEST 0
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
	char teamname[20];
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
	printf("%s\t%s\t%d\t%d\t%d\n", re.playername, re.sportname, re.score, re.order, re.points);
}

void displayallresults()
{
	int i;
	printf("姓名\t比赛\t成绩\t排名\t积分\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allresultscount; i++)
	{
		displayresult(allresults[i]);
	}
	printf("--------------------------------------------\r\n");
}


//-
void displayteam(team t)
{
	printf("%s\t%s\t%d\t%d\n", t.name, t.leader, t.points, t.order);
}

void displayallteams()
{
	int i;
	printf("团队\t领队\t积分\t排名\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allteamscount; i++)
	{
		displayteam(allteams[i]);
	}
	printf("--------------------------------------------\r\n");
}
//-///
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

void getteamdbyplayer(char *playername, char teamname[])
{
	int i;
	int found = 0;
	for (i = 0; i < allplayerscount; i++)
	{
		if (streq(allplayers[i].name, playername))
		{
			strcpy(teamname, allplayers[i].teamname);
			found = 1;
			break;
		}
	}
	if (found == 0)
		printf("\n基础数据中未找到姓名%s对应的团队!\n", playername);
}

//**///
result getresultfromline(char *line)
{
	char *part;
	char teamname[20] = "";
	int index = 0;
	result q;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.playername, part);
			getteamdbyplayer(part, teamname);
			strcpy(q.teamname, teamname);
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

void setresultorderpointsvalue(char *playername, char *sportname, int order)
{
	int i;
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].playername, playername)
			&& streq(allresults[i].sportname, sportname))
		{
			allresults[i].order = order;
			if (order == 1)
				allresults[i].points = 3;
			else if (order == 2)
				allresults[i].points = 2;
			else if (order == 3)
				allresults[i].points = 1;
			else
				allresults[i].points = 0;
			break;
		}
	}
}
void calcresultorderpointsbysport(char *sportname)
{
	int i;
	int orders[100] = { 0 };
	int playerinsportcnt = 0;
	int copyscores[100];
	result copyresults[100] = {};
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].sportname, sportname))
		{
			copyresults[playerinsportcnt] = allresults[i];
			playerinsportcnt++;
		}
	}
	if (playerinsportcnt <= 0)
		return;
	for (i = 0; i < playerinsportcnt; i++)
	{
		copyscores[i] = copyresults[i].score;
	}
	sortandgetorders(copyscores, playerinsportcnt, orders);
	for (i = 0; i < playerinsportcnt; i++)
	{
		setresultorderpointsvalue(copyresults[i].playername, copyresults[i].sportname, orders[i]);
	}
}

void calcallresultorderpoints()
{
	int i;
	for (i = 0; i < allsportscount; i++)
	{
		calcresultorderpointsbysport(allsports[i].name);
	}
}



void addresult(char *playername, char *sportname, int score)
{
	int i;
	char teamname[20] = "";
	if (checkplayerexists(playername)
		&& checksportexists(sportname)
		&& !checkplayersportexists(playername, sportname)
		&& !checksportscoreexists(sportname, score))
	{
		result re;
		strcpy(re.playername, playername);
		strcpy(re.sportname, sportname);
		re.score = score;
		getteamdbyplayer(playername, teamname);
		strcpy(re.teamname, teamname);
		//
		allresults[allresultscount++] = re;
		appendresult(re);
		//printf("\n比赛成绩添加成功!\n");
		calcallresultorderpoints();
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
void calconeteam(char *teamname)
{
	int i;
	int totalpoints = 0;
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].teamname, teamname))
		{
			totalpoints += allresults[i].points;
		}
	}
	for (i = 0; i < allteamscount; i++)
	{
		if (streq(allteams[i].name, teamname))
		{
			allteams[i].points = totalpoints;
			break;
		}
	}
}
//////
int cmpteambypointsdesc(const void * a, const void * b)
{
	return ((team*)b)->points - ((team*)a)->points;
}
void calcallteams()
{
	int i;
	for (i = 0; i < allteamscount; i++)
	{
		calconeteam(allteams[i].name);
	}
	qsort(allteams, allteamscount, sizeof(team), cmpteambypointsdesc);
	for (i = 0; i < allteamscount; i++)
	{
		allteams[i].order = i + 1;
	}
}

void displayteambyplayer(char *playername)
{
	int i;
	char teamname[20] = "";
	calcallteams();
	getteamdbyplayer(playername, teamname);
	for (i = 0; i < allteamscount; i++)
	{
		if (streq(allteams[i].name, teamname))
		{
			printf("团队\t领队\t积分\t排名\n");
			displayteam(allteams[i]);
			break;
		}
	}
}
void promptdisplayteambyplayer()
{
	char playername[20] = "";
	printf("请输入选手姓名:");
	scanf("%s", playername);
	fseek(stdin, 0, SEEK_END);
	displayteambyplayer(playername);
}

void displayplayer(char *playername)
{
	int i;
	printf("姓名\t比赛\t成绩\t排名\t积分\n");
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].playername, playername))
		{
			displayresult(allresults[i]);
		}
	}
}

void promptdisplayplayer()
{
	char playername[20] = "";
	printf("请输入选手姓名:");
	scanf("%s", playername);
	fseek(stdin, 0, SEEK_END);
	displayplayer(playername);
}

int main()
{
	int choice = -1;
	readallteams();
	readallsports();
	readallplayers();
	readallresults();
	calcallresultorderpoints();
	displayallresults();


#if TEST
	int i;
	displayplayer("p2");
	//displayteambyplayer("p3");
	//calcallteams();
	//displayallteams();
	//int n = 1;
	//int orders[100] = { 0 };
	//int nums[] = { 24 };
	//sortandgetorders(nums, n, orders);
	//for (i = 0; i < n; i++)
	//{
	//	printf("%d\t", orders[i]);
	//}


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
		printf("\n\t 3. 查看所有团队");
		printf("\n\t 4. 运动员姓名查看团队");
		printf("\n\t 5. 运动员姓名查看自己的比赛");
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
		case '3':
			printf("\n\n你选择了 3\n");
			calcallteams();
			displayallteams();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptdisplayteambyplayer();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptdisplayplayer();
			break;
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

