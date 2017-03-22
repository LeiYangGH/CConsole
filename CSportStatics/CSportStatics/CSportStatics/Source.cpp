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
	int total;
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
}result;
result allresults[50];
int allresultscount = 0;

typedef struct player
{
	char name[50];
	char teamname[50];
}player;
player allplayers[50];
int allplayerscount = 0;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}
//
//void promptinputsubjectcount()
//{
//	printf("�������Ŀ������1��6��:");
//	scanf("%d", &subjects_count);
//	fseek(stdin, 0, SEEK_END);
//	if (subjects_count < 1 || subjects_count>6)
//		subjects_count = 3;//Ĭ�Ͽ�Ŀ����
//}
//
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
	q.total = 0;
	return q;
}

void readallteams()
{
	char line[200];
	FILE *fp = fopen(TEAM_FILE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", TEAM_FILE);
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
	printf("\n�Ѷ����ļ�!\n");

}


void readallsports()
{
	char line[200];
	FILE *fp = fopen(SPORT_FILE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", SPORT_FILE);
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
	printf("\n�Ѷ����ļ�!\n");

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
//	printf("\n����������δ�ҵ��Ŷ�����%s!\n", name);
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
		printf("\n���ļ�%sʧ��!", PLAYER_FILE);
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
	printf("\n�Ѷ����ļ�!\n");

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
		printf("\n���ļ�%sʧ��!", RESULT_FILE);
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
	printf("\n�Ѷ����ļ�!\n");

}
//**//
//////
//����������
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
//	printf("���ܷ����������\r\n");
//	displayallplayers();
//}
//
//void sortanddisplaybyno()
//{
//	qsort(allplayers, allplayerscount, sizeof(player), cmpbyno);
//	printf("��ѧ�����������\r\n");
//	displayallplayers();
//}
//
//void countbygradesforonesubject(int subjectId)
//{
//	int i, t, cnt100_90 = 0, cnt89_80 = 0, cnt79_70 = 0, cnt69_60 = 0, cnt59_0 = 0;
//	printf("��%d��Ŀ�ɼ��ڸ���ֵ�εĳɼ�����ͳ�����£�\r\n", subjectId + 1);
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
//	//�Ȱ��ܷ�����
//	qsort(allplayers, allplayerscount, sizeof(player), cmpbytotal);
//	for (i = 0; i < allplayerscount; i++)
//		if (strcmp(name, allplayers[i].name) == 0)
//		{
//			printf("%s,��%d��, ��ϸ����\n", name, allplayerscount - i);
//			displayplayer(allplayers[i]);
//			return;
//		}
//	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
//}
//
//void promptsearchtotalbyname()
//{
//	char name[MAX_STRLEN] = "";
//	printf("������Ҫ��ѯ��ѧ������:");
//	scanf("%s", &name);
//	searchtotalbyname(name);
//}
//
//
void addresult(char *playername, char *sportname, int score)
{
	int i;
	result re;
	strcpy(re.playername, playername);
	strcpy(re.sportname, sportname);
	re.score = score;
	//
	allresults[allresultscount++] = re;
}

void writeallresults()
{
	FILE *fp = fopen(RESULT_FILE, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", RESULT_FILE);
		getchar();
		exit(1);
	}

	int i;
	result re;
	for (i = 0; i < allresultscount; i++)
	{
		re = allresults[i];
		fprintf(fp, "%s\t%s\t%d\n", re.playername, re.sportname, re.score);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

int main()
{
#if TEST
	readallteams();
	readallsports();
	readallplayers();
	//addresult("p1", "s1", 11);
	//addresult("p1", "s2", 12);
	//addresult("p2", "s1", 21);
	readallresults();
	displayallresults();
	//writeallresults();
#else


	int choice = -1;
	promptinputsubjectcount();
	createsampleplayers();
	//system("pause");
	while (choice != 0)
	{
		printf("\n\t ѧ���ɼ������ѯͳ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. �ֶ�¼��");
		printf("\n\t 2. ����ÿ�ſγ̵��ֺܷ�ƽ����");
		printf("\n\t 3. ��ѧ���ܷ��ɸߵ����ų����α�");
		printf("\n\t 4. ��ѧ����С�����ų��ɼ���");
		printf("\n\t 5. ��������ѯѧ���������俼�Գɼ�");
		printf("\n\t 6. ͳ��");
		printf("\n\t 7. ���");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			promptaddplayer();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			calcanddisplaytotalandaverage();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			sortanddisplaybytotal();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			sortanddisplaybyno();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptsearchtotalbyname();
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			countbygrades();
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			sortanddisplaybyno();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	fseek(stdin, 0, SEEK_END);
#endif // TEST
	system("pause");
	return 0;
}

