#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<iostream>
#include <stdio.h>
#include <string.h>
#define TEAM_COUNT 4
#define MAX_MEMBER 50
#define GOODS_TYPES 5
//int teammembers[4][MAX_MEMBER] = {
//	{1,2},
//	{10,13,11,12,14},
//	{0,1},
//	{99,2},
//};
//int teamlen[4] = { 2,5,2,2 };
int teammembers[4][MAX_MEMBER];
int teamlen[4];
int infectedmembers[TEAM_COUNT*MAX_MEMBER];
int infectedmemberslen;
int teamisinfectedandrecorded[TEAM_COUNT] = { 0 };
//int infectedteamslen;
//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

int getnumsfromline(char *line, int nums[])
{
	char *part;
	int index = 0;
	part = strtok(line, " ");
	while (part != NULL)// && part[0] != 'y')
	{
		nums[index++] = toint(part);
		//printf("%d\n", nums[index - 1]);
		part = strtok(NULL, " ");
	}
	return index;
}

void inputteammembers(int team)
{
	int cnt;
	char line[200];
	int nums[MAX_MEMBER];
	printf("NO.%d:������y������\n", team + 1);
	fgets(line, 1024, stdin);
	teamlen[team] = getnumsfromline(line, teammembers[team]);
}

void printallteammembers()
{
	int t, m;
	for (t = 0; t < TEAM_COUNT; t++)
	{
		printf("����%d��ѧ�����£�\n", t + 1);
		for (m = 0; m < teamlen[t]; m++)
		{
			printf("%d\t", teammembers[t][m]);
		}
		printf("\n", t);
	}
}

int isteaminfected(int team)
{
	int i, m, teaminfected = 0;
	for (m = 0; m < teamlen[team]; m++)
	{
		int member = teammembers[team][m];
		for (i = 0; i < infectedmemberslen; i++)
		{
			if (infectedmembers[i] == member)
			{
				teaminfected = 1;
				break;
			}
		}
	}
	return teaminfected;
}

int addinfectedteam(int team)
{
	int i, m, exist, newmemberfound = 0;
	teamisinfectedandrecorded[team] = 1;
	for (m = 0; m < teamlen[team]; m++)
	{
		int member = teammembers[team][m];
		exist = 0;
		for (i = 0; i < infectedmemberslen; i++)
		{
			if (infectedmembers[i] == member)
			{
				exist = 1;
				break;
			}
		}
		if (!exist)
		{
			infectedmembers[infectedmemberslen++] = member;
			newmemberfound = 1;
		}
	}
	return newmemberfound;
}

void findmoreinfectedmembers()
{
	int foundnew = 1;
	int t, m;
	while (foundnew > 0)
	{
		foundnew = 0;
		for (t = 0; t < TEAM_COUNT; t++)
		{
			if (!teamisinfectedandrecorded[t] && isteaminfected(t))
			{
				foundnew += addinfectedteam(t);
			}
		}
	}
}

void getallinfectedmembers(int firstmember)
{
	infectedmembers[0] = firstmember;
	infectedmemberslen = 1;
	findmoreinfectedmembers();
}

void printallinfectedmembers()
{
	int i;
	printf("���Ƹ�Ⱦ��ѧ�����£�\n");

	for (i = 0; i < infectedmemberslen; i++)
	{
		printf("%d\t", infectedmembers[i]);
	}
	printf("\n");
}

int main()
{
	int t, m, first;
	for (t = 0; t < TEAM_COUNT; t++)
	{
		inputteammembers(t);
	}
	printf("---------\n");
	printallteammembers();
	printf("---------\n");
	printf("������һ�����Ʋ���ѧ����");
	scanf("%d", &first);
	printf("---------\n");
	getallinfectedmembers(first);
	printallinfectedmembers();
	system("pause");
	return 0;
}