#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 1 //����ʱ��1�� ����ʱ��0
#define FILE_STU "sgr.txt"
//#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\n"
//#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\n"
#define MAX_STRLEN 20
#define SINGERS_COUNT 3
#define JUDGES_COUNT 3
//#define STU_MEMBERS_FULL sgr.no, sgr.name,  sgr.score,sgr.total
//#define STU_MEMBERS_NET sgr.no, sgr.name,  sgr.score
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
//singer sortsingers[SINGERS_COUNT];
int allsingerscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//char *FILE_STU = "sgr.txt";
singer *head;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

int tofloat(char *s)
{
	char *end;
	return (float)strtol(s, &end, 10);
}

void displaysinger(singer sgr)
{
	int i;
	printf("\n");
	printf("���ֱ�ţ�%d\t����%s\t�������£�\n", sgr.no, sgr.name, sgr.total);
	for (i = 0; i < JUDGES_COUNT; i++)
		printf("%d\t", sgr.score[i]);
	printf("\n");
}

void displayallsingers()
{
	int i;
	printf("����ԭʼ�ɼ�����\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		displaysinger(allsingers[i]);
	}
	printf("--------------------------------------------\n");
}


///////////


void displayallave()
{
	int i;
	singer sgr;
	printf("�������ճɼ�����\n", allsingerscount);
	printf("���\t����\t�ɼ�\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < allsingerscount; i++)
	{
		sgr = allsingers[i];
		printf("%d\t%s\t%.1f\n", sgr.no, sgr.name, sgr.ave);
	}
	printf("--------------------------------------------\n");
}
////////////
int cmpfunc(const void * a, const void * b)
{
	return ((singer*)b)->ave - ((singer*)a)->ave;
}

void displayscoreandrank(singer sgr, int rank)
{
	printf("���\t����\t�ɼ�\t����\n");
	printf("%d\t%s\t%.1f\t%d\n",
		sgr.no, sgr.name, sgr.ave, rank);
}



//���������Ϣ
void inputname(char str[])
{
	printf("����������(2-45���ַ�)�����ܴ��ո�Tab��س���:");
	scanf("%s", str);
	printf("�����������ΪΪ %s \n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("���������1��100:");
		scanf("%d", &n);
	}
	return n;
}



int getsingeridexbyid(int no)
{
	int i;
	for (i = 0; i < allsingerscount; i++)
	{
		singer b = allsingers[i];
		if (b.no == no)
			return i;
	}
}

void removesinger(int no)
{
	int i;
	int index;
	index = getsingeridexbyid(no);
	for (i = index; i < allsingerscount - 1; i++)
		allsingers[i] = allsingers[i + 1];
	allsingerscount--;
	printf("ɾ����ϣ�ʣ��%d����\n", allsingerscount);

}

void inputremovesinger()
{
	int no;
	printf("������Ҫɾ���ı��:");
	scanf("%d", &no);
	removesinger(no);
}


int login()
{
	char name[50] = "";
	char pwd[50] = "";
	printf("\n����������\n");
	scanf("%s", name);
	printf("\n����������\n");
	scanf("%s", pwd);
	return streq(name, "username")
		&& streq(pwd, "password");
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
	//sgr.score = math;
	//sgr.english = english;
	//sgr.chinese = chinese;
	//sgr.c = c;
	allsingers[allsingerscount++] = sgr;
}

void createsamplesingers()
{
	int scores1[JUDGES_COUNT] = { 11,12,13 };
	int scores2[JUDGES_COUNT] = { 21,22,23 };
	int scores3[JUDGES_COUNT] = { 31,32,33 };
	printf("����ʾ����������...");
	addsinger(1, "name1", scores1);
	addsinger(3, "name3", scores3);
	addsinger(2, "name2", scores2);
	printf("2��ʾ�����������Ѵ���\n");
}

void calcandsortaverage()
{
	int i, j, min, max, score;
	for (i = 0; i < allsingerscount; i++)
	{
		min = max = allsingers[i].score[0];//��ʼֵ
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

	printf("\n��������\n");
	scanf("%d", &no);
	printf("\n����������\n");
	scanf("%s", name);
	printf("\n������%d�����еĳɼ�(������)���ո����\n", JUDGES_COUNT);
	////
	scanf("%d%d", &scores[0], &scores[1]);
	addsinger(no, name, scores);
	printf("��ɵ�%d������¼��!\n", allsingerscount);
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
	printf("û�ҵ���Ӧ���ֵ���Ϣ��\n");
}

int inputfindtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("������Ҫ��ѯ�ĸ��ֵ������������ո񣬻س�����:");
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
	printf("û�ҵ���Ӧ���ֵ���Ϣ��\n");
}

void inputfindtotalbyno()
{
	int no;
	printf("������Ҫ��ѯ�ĸ��ֵı��:");
	scanf("%d", &no);
	findtotalbyno(no);
}

int main()
{
	int choice = -1;

#if DEV

	createsamplesingers();


	////printf("\n%d\n", allsingerscount);
	///*inputaddsinger();
	//writeallsingers();*/
	///*inputremovesinger();
	//writeallsingers();*/
	////inputfindtotalbyname();
	////inputfindtotalbyno();

	displayallsingers();

	calcsortanddisplayaverage();
	//findtotalbyno(3);
	//inputfindtotalbyno();
	inputfindtotalbyname();
	//calcanddisplaytotalandaverage();
	//sortanddisplay();
	//calcanddisplayallsubjects();

	//countbygrades();
#else
	while (choice != 0)
	{
		char *menu = "**********************�˵�****************************\n"
			"��1����������ֵ���               ��6����ѧ�Ƽ������\n"
			"��2��������������ѯ               ��7�������ֵ�������\n"
			"��3�������ձ�Ų�ѯ               ��8����������ֵ���\n"
			"��4������Ӹ��ֵ���               ��9�� : �鿴���ֵ���\n"
			"��5����ɾ�����ֵ���               ��10���������ƽ����\n"
			"��0�����˳�����ϵͳ";
		printf("������ѡ�����֣����س�\n", menu);
		printf("%s\n", menu);
		choice = getchar();
		switch (choice)
		{
		case 0:
			system("pause");
			exit(0);
			break;
		case 1:

			break;
		case 2:
			inputfindtotalbyname();
			break;
		case 3:
			inputfindtotalbyno();
			break;
		case 4:
			inputaddsinger();
			break;
		case 5:
			inputremovesinger();
			break;
		case 6:

			break;
		case 7:
			sortanddisplay();
			break;
		case 8:

			break;
		case 9:
			sortanddisplay();
			break;
		case 10:
			calcanddisplaytotalandaverage();
			calcanddisplayallsubjects();

			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
}
#endif
	//fseek(stdin, 0, SEEK_END);
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}

