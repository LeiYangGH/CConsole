#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRLEN 20
#define STRING_FORMAT_3 "%-20s\t%-20s\t%-20s\r\n"
#define SAMPLE_COUNT 5

typedef struct movie
{
	char name[MAX_STRLEN];
	char date[MAX_STRLEN];
	char time[MAX_STRLEN];
}movie;

movie allmovies[50];
movie goal;
int allmoviescount = 0;

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

void displaymovie(movie rec)
{
	printf("\r\n");
	printf(STRING_FORMAT_3, rec.name, rec.date, rec.time);
}

void displayallmovies()
{
	int i;
	printf("所有%d电影如下\r\n", allmoviescount);
	printf("--------------------------------------------\r\n");
	printf(STRING_FORMAT_3, "片名", "日期", "时间");
	for (i = 0; i < allmoviescount; i++)
	{
		displaymovie(allmovies[i]);
	}
	printf("--------------------------------------------\r\n");
}

void inputstring(char str[], char* purpose)
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("请输入%s，%d个字符以内，不能带Tab或回车符:", purpose, MAX_STRLEN);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("您的 %s 为 %s \r\n", purpose, str);
}

int findmovie()
{
	int i;
	int foundindex = -1;
	for (i = 0; i < allmoviescount; i++)
	{
		movie m = allmovies[i];
		if (
			(strlen(goal.name) > 0 && strcmp(m.name, goal.name) == 0)
			&& (strlen(goal.date) == 0 || strlen(goal.date) > 0 && strcmp(m.date, goal.date) == 0)
			&& (strlen(goal.time) == 0 || strlen(goal.time) > 0 && strcmp(m.time, goal.time) == 0)
			)
		{
			foundindex = i;
			break;
		}
	}
	return foundindex;
}

int promptfindbyname()
{
	inputstring(goal.name, "片名");
	return findmovie();
}

void setdatestringbyweekday(int weekday)
{
	strcpy(goal.date, "2016-12-12");
	goal.date[9] = '1' + weekday;
}

int promptfindbyweekday()
{
	int weekday;
	int len = -1;
	char input[50] = "";
	while (len != 1)
	{
		printf("请输入星期几，数字1～9:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	weekday = toint(input);
	setdatestringbyweekday(weekday);
	printf("您的选择为星期%d 日期%s\r\n", weekday, goal.date);
	return findmovie();
}

int promptfindbytime()
{
	inputstring(goal.time, "时间");
	return findmovie();
}

void createsamplemovies()
{
	printf("创建示例记录信息...\n");

	strcpy(allmovies[0].name, "泰坦尼克号");
	strcpy(allmovies[0].date, "2016-12-12");
	strcpy(allmovies[0].time, "19:00");

	strcpy(allmovies[1].name, "千与千寻");
	strcpy(allmovies[1].date, "2016-12-13");
	strcpy(allmovies[1].time, "23:00");

	strcpy(allmovies[2].name, "憨豆先生");
	strcpy(allmovies[2].date, "2016-12-16");
	strcpy(allmovies[2].time, "20:45");

	strcpy(allmovies[3].name, "憨豆先生");
	strcpy(allmovies[3].date, "2016-12-16");
	strcpy(allmovies[3].time, "22:40");

	strcpy(allmovies[4].name, "憨豆先生");
	strcpy(allmovies[4].date, "2016-12-18");
	strcpy(allmovies[4].time, "19:00");

	//片名x为了测试时输入方便
	//strcpy(allmovies[2].name, "x");
	//strcpy(allmovies[2].date, "2016-12-16");
	//strcpy(allmovies[2].time, "20:45");

	//strcpy(allmovies[3].name, "x");
	//strcpy(allmovies[3].date, "2016-12-16");
	//strcpy(allmovies[3].time, "22:40");

	//strcpy(allmovies[4].name, "x");
	//strcpy(allmovies[4].date, "2016-12-18");
	//strcpy(allmovies[4].time, "19:00");
	allmoviescount = SAMPLE_COUNT;
	printf("示例记录信息创建完毕！\n");
}

void initbookinginfo()
{
	strcpy(goal.name, "");
	strcpy(goal.date, "");
	strcpy(goal.time, "");
}

void generaterandseat()
{
	srand((unsigned)time(NULL));
	printf("系统为您安排的座位号是：%d\n", rand() % 49 + 1);
}

void requestnexttry(char* purpose)
{
	printf("没有找到对应%s的电影，任意键重新查询。\n", purpose);
	fseek(stdin, 0, SEEK_END);
	getchar();
}

int main0()
{
	createsamplemovies();
	while (1)
	{
		system("cls");
		displayallmovies();
		initbookinginfo();
		if (promptfindbyname() >= 0)
		{
			if (promptfindbyweekday() >= 0)
			{
				int index = promptfindbytime();
				if (index >= 0)
				{
					printf("您已成功预订电影:");
					displaymovie(allmovies[index]);
					generaterandseat();
					break;
				}
				else
					requestnexttry("时间");
			}
			else
				requestnexttry("日期");
		}
		else
			requestnexttry("片名");
	}
	system("pause");
	return 0;
}

