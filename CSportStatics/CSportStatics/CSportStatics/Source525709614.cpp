#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define TEAM_FILE "team.txt"
#define PLAYER_FILE "player.txt"
#define SPORT_FILE "sport.txt"
#define RESULT_FILE "result.txt"
//下面结构体定义，与各个文件基本对应
typedef struct team
{
	char name[20];
	char leader[20];
	int points;//积分
	int order;//排序
}team;
team allteams[10];//所有记录
int allteamscount = 0;//记录数

typedef struct sport
{
	char name[20];
}sport;
sport allsports[10];
int allsportscount = 0;

typedef struct result
{
	char playername[20];
	char teamname[20];//所属团队，实际上是冗余信息，但避免了一次关联查找
	char sportname[20];
	int score;//裁判打分，这分数只用来排序，不作为积分
	int order;
	int points;
}result;
result allresults[50];
int allresultscount = 0;

typedef struct player
{
	char name[50];
	char teamname[50];//所属团队
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

//显示单个比赛结果
void displayresult(result re)
{
	printf("%s\t%s\t%d\t%d\t%d\n", re.playername, re.sportname, re.score, re.order, re.points);
}

//显示所有比赛结果
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

//显示单个团队信息
void displayteam(team t)
{
	printf("%s\t%s\t%d\t%d\n", t.name, t.leader, t.points, t.order);
}

//显示所有团队信息
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

//从文本的一行拆分出团队
//思路：根据Tab和换行符拆分strtok函数实现拆分，根据累计的列序号来判断为结构体的哪个成员复制
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

//从文本读取所有团队
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

//从文本读取所有赛事
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

//从文本的一行拆分出选手
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
	return q;
}

//从文本读取所有选手
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

//根据选手姓名查找所属团队
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

//从文本的一行拆分出比赛结果
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
			getteamdbyplayer(part, teamname);//读入比赛结果的时候，关联所属团队
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

//从文本读取所有比赛结果
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

//检查选手是否在基础数据中
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

//检查比赛是否在基础数据中
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

//检查某选手是否参加过某比赛
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

//检查某比赛的多个选手评分是否重复
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

//把新的比赛结果追加到文件末尾
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

//按成绩倒序排序，快速排序函数qsort要求的格式
int cmpbyscoredesc(const void * a, const void * b)
{
	return *(int*)b - *(int*)a;
}
//把成绩倒序排序然后得出排名
//scores成绩列表，scorescnt成绩个数，orders每个成绩排序后对应的名次
void sortandgetorders(int scores[], int scorescnt, int orders[])
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
			if (scores[i] == sortscores[s])
			{
				orders[i] = s + 1;
				break;
			}
		}
}

//设置某个选手参加某项比赛的名次和积分
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

//计算某一项比赛所有参赛者的排名
void calcresultorderpointsbysport(char *sportname)
{
	int i;
	int orders[100] = { 0 };
	int playerinsportcnt = 0;
	int copyscores[100];//分数列表
	result copyresults[100];//复制出来排序的成绩列表（由于qsort函数是按地址排序因此要复制一份以免影响原有数据）
	for (i = 0; i < allresultscount; i++)
	{
		if (streq(allresults[i].sportname, sportname))
		{
			copyresults[playerinsportcnt] = allresults[i];
			playerinsportcnt++;
		}
	}
	//如果没人参加此项比赛就什么都不用做
	if (playerinsportcnt <= 0)
		return;
	for (i = 0; i < playerinsportcnt; i++)
	{
		copyscores[i] = copyresults[i].score;
	}
	//排序并获得名次
	sortandgetorders(copyscores, playerinsportcnt, orders);
	//把名次和积分设置给每个result
	for (i = 0; i < playerinsportcnt; i++)
	{
		setresultorderpointsvalue(copyresults[i].playername, copyresults[i].sportname, orders[i]);
	}
}

//计算所有比赛的排名和积分
void calcallresultorderpoints()
{
	int i;
	for (i = 0; i < allsportscount; i++)
	{
		calcresultorderpointsbysport(allsports[i].name);
	}
}

//裁判评分添加成绩
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
		allresults[allresultscount++] = re;
		appendresult(re);//存文件
		calcallresultorderpoints();//计算排名，由于菜单调用顺序不可预期，其他查询调用之前就应该先算好排名
	}
}

//提示裁判输入比赛结果
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

//计算一个团队的总分
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

//团队积分倒序比较
int cmpteambypointsdesc(const void * a, const void * b)
{
	return ((team*)b)->points - ((team*)a)->points;
}
//计算所有团队的总分并倒序排序
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
		allteams[i].order = i + 1;//为每个团队的名次赋值
	}
}

//显示某个选手的团队信息
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

//提示选手输入姓名并显示所属团队信息
void promptdisplayteambyplayer()
{
	char playername[20] = "";
	printf("请输入选手姓名:");
	scanf("%s", playername);
	fseek(stdin, 0, SEEK_END);
	displayteambyplayer(playername);
}

//显示选手的比赛信息
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

//提示选手输入姓名并显示比赛信息
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

	while (choice != 0)
	{
		printf("\n\t 比赛成绩录入统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入成绩");
		printf("\n\t 2. 查看所有成绩");
		printf("\n\t 3. 查看所有团队");
		printf("\n\t 4. 运动员姓名查看团队");
		printf("\n\t 5. 运动员姓名查看自己的比赛");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);//清除缓冲区避免多次输入之间影响
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
		default:
			printf("\n\n输入有误，请重选\n");
			break;
			fseek(stdin, 0, SEEK_END);
			system("pause");
		}
	}
	return 0;
}