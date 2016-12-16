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

//�ַ���ת����
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
	printf("����%d��Ӱ����\r\n", allmoviescount);
	printf("--------------------------------------------\r\n");
	printf(STRING_FORMAT_3, "Ƭ��", "����", "ʱ��");
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
		printf("������%s��%d���ַ����ڣ����ܴ�Tab��س���:", purpose, MAX_STRLEN);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("���� %s Ϊ %s \r\n", purpose, str);
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
	inputstring(goal.name, "Ƭ��");
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
		printf("���������ڼ�������1��9:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	weekday = toint(input);
	setdatestringbyweekday(weekday);
	printf("����ѡ��Ϊ����%d ����%s\r\n", weekday, goal.date);
	return findmovie();
}

int promptfindbytime()
{
	inputstring(goal.time, "ʱ��");
	return findmovie();
}

void createsamplemovies()
{
	printf("����ʾ����¼��Ϣ...\n");

	strcpy(allmovies[0].name, "̩̹��˺�");
	strcpy(allmovies[0].date, "2016-12-12");
	strcpy(allmovies[0].time, "19:00");

	strcpy(allmovies[1].name, "ǧ��ǧѰ");
	strcpy(allmovies[1].date, "2016-12-13");
	strcpy(allmovies[1].time, "23:00");

	strcpy(allmovies[2].name, "��������");
	strcpy(allmovies[2].date, "2016-12-16");
	strcpy(allmovies[2].time, "20:45");

	strcpy(allmovies[3].name, "��������");
	strcpy(allmovies[3].date, "2016-12-16");
	strcpy(allmovies[3].time, "22:40");

	strcpy(allmovies[4].name, "��������");
	strcpy(allmovies[4].date, "2016-12-18");
	strcpy(allmovies[4].time, "19:00");

	//Ƭ��xΪ�˲���ʱ���뷽��
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
	printf("ʾ����¼��Ϣ������ϣ�\n");
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
	printf("ϵͳΪ�����ŵ���λ���ǣ�%d\n", rand() % 49 + 1);
}

void requestnexttry(char* purpose)
{
	printf("û���ҵ���Ӧ%s�ĵ�Ӱ����������²�ѯ��\n", purpose);
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
					printf("���ѳɹ�Ԥ����Ӱ:");
					displaymovie(allmovies[index]);
					generaterandseat();
					break;
				}
				else
					requestnexttry("ʱ��");
			}
			else
				requestnexttry("����");
		}
		else
			requestnexttry("Ƭ��");
	}
	system("pause");
	return 0;
}

