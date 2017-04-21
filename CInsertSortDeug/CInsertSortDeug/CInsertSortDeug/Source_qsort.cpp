#include<stdio.h>
#include <stdlib.h>

#pragma once

//#define N 100
#define N 5

typedef struct student {
	int id;
	char name[16];
	int cid;
	int sid;
	int score[10];
	double ave;
}STU;

typedef struct sexy {
	int id;
	char name[16];
}S;

typedef struct college {
	int id;
	char name[16];
}C;

int readSinfo(S s[], int num, char filename[]) {
	int i;
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		return 1;
	}
	for (i = 0; i < num; i++)
	{
		fscanf(fp, "%d%s", &(s[i].id), (s[i].name));
	}
	fclose(fp);
	return 0;
}


int readCinfo(C s[], int num, char filename[]) {
	FILE *fp;
	int i;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		return 1;
	}
	for (i = 0; i < num; i++)
	{
		fscanf(fp, "%d%s", &(s[i].id), (s[i].name));
	}
	fclose(fp);
	return 0;
}




int readstu(STU s[], int num, char filename[]) {
	FILE *fp;
	int i, j;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		return 1;
	}
	for (i = 0; i < num; i++)
	{
		fscanf(fp, "%d%s%d%d", &(s[i].id), s[i].name, &(s[i].sid), &(s[i].cid));
		for (j = 0; j < 10; j++)
			fscanf(fp, "%d", &(s[i].score[j]));
	}
	fclose(fp);
	return 0;
}
/**********qsort********************/
int sortindex;
int cmpfunc(const void * a, const void * b)
{
	return ((STU*)a)->score[sortindex] - ((STU*)b)->score[sortindex];
}

void sorttotal(STU s[], int num, int index)
{
	sortindex = index;
	qsort(s, N, sizeof(student), cmpfunc);
}
/**********qsort********************/
void sortscore(STU s[], int num, int index)
{             //插入法排序                                                
	int i, n, k, j, t;
	STU stmp;
	if (index >= 0 && index <= 9)
	{
		for (i = 1; i < num; i++)
		{
			stmp = s[i];
			for (j = i; j > 0 && s[j - 1].score[index] > stmp.score[index]; j--)
			{
				s[j] = s[j - 1];
			}
			s[j] = stmp;
		}
	}

	else if (index = 10)                                  //比较法排序 
	{
		for (i = 0; i < num - 1; i++)
			for (n = i + 1; n < num; n++)
				if (s[i].ave < s[n].ave)
				{
					stmp = s[i];
					s[i] = s[n];
					s[n] = stmp;
				}
	}
}


int main()//测试成功后把你的整个main函数都注释掉
{
	int i, re, j, n, k;
	STU a[100];
	re = readstu(a, N, "Student_Info.txt");
	if (re = NULL)
	{
		printf("error,Student_Info.txt");
		return 1;
	}
	for (i = 0; i < N; i++)
	{
		a[i].ave = 0;
	}
	//for (i = 0; i < N; i++)
	//	printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", a[i].id, a[i].name, a[i].sid, a[i].cid, a[i].score[0], a[i].score[1], a[i].score[2], a[i].score[3], a[i].score[4], a[i].score[5], a[i].score[6], a[i].score[7], a[i].score[8], a[i].score[9]);
	while (1)
	{
		//printf("0按成绩科目0由高到低排序\n1按成绩科目1由高到低排序\n2按成绩科目2由高到低排序\n3按成绩科目3由高到低排序\n4按成绩科目4由高到低排序\n5按成绩科目5由高到低排序\n6按成绩科目6由高到低排序\n7按成绩科目7由高到低排序\n8按成绩科目8由高到低排序\n9按成绩科目9由高到低排序\n10按平均成绩由高到低排序\n11返回上一级菜单\n");
		printf("0~9,10按平均成绩由高到低排序\n11返回上一级菜单\n");
		scanf("%d", &j);
		for (n = 0; n < N; n++)
		{
			for (i = 0; i < 10; i++)
				a[n].ave += a[n].score[i];
			a[n].ave /= 10;
		}
		if (j >= 0 && j <= 10)
		{
			//sortscore(a, N, j);
			sorttotal(a, N, j);
			for (i = 0; i < N; i++)
				printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%.2lf\n", a[i].id, a[i].name, a[i].sid, a[i].cid, a[i].score[0], a[i].score[1], a[i].score[2], a[i].score[3], a[i].score[4], a[i].score[5], a[i].score[6], a[i].score[7], a[i].score[8], a[i].score[9], a[i].ave);
		}
		else
			printf("输入错误，请重新输入正确的序号。");
	}
	return 0;
}

