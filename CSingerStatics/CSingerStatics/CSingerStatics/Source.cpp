#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_STU "sgr.txt"
#define FORMATFULL "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.1f\r\n"
#define FORMATNET "%d\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STU_MEMBERS_FULL sgr.no, sgr.name,  sgr.score,sgr.total
#define STU_MEMBERS_NET sgr.no, sgr.name,  sgr.score
typedef struct singer
{
	int no;
	char name[50];
	int score;
	int total;
}singer;

singer allsingers[100];
singer sortsingers[100];
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
	printf("\r\n");
	printf(FORMATNET, STU_MEMBERS_NET);
}

void displayallsingers()
{
	int i;
	printf("����%d��������\r\n", allsingerscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allsingerscount; i++)
	{
		displaysinger(allsingers[i]);
	}
	printf("--------------------------------------------\r\n");
}

int cmpfunc(const void * a, const void * b)
{
	return ((singer*)a)->total - ((singer*)b)->total;
}
void sorttotal()
{
	int i;
	for (i = 0; i < allsingerscount; i++)
	{
		sortsingers[i] = allsingers[i];
	}
	qsort(sortsingers, allsingerscount, sizeof(singer), cmpfunc);
}

void sortanddisplay()
{
	int i;
	sorttotal();
	printf("���������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allsingerscount; i++)
	{
		displaysinger(sortsingers[i]);
	}
	printf("--------------------------------------------\r\n");
}




float ave()
{
	int i;
	float sum = 0;
	for (i = 0; i < allsingerscount; i++)
		sum += allsingers[i].total;
	return sum / (float)allsingerscount;
}

void inputstring(char str[])
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("����������:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
}

void searchtotalbyname(char *name)
{
	int i;
	for (i = 0; i < allsingerscount; i++)
		if (strcmp(name, allsingers[i].name) == 0)
		{
			displaysinger(allsingers[i]);
			return;
		}
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}

int promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	inputstring(name);
	searchtotalbyname(name);
	return strcmp(name, "q");
}



void searchtotalbyno(int no)
{
	int i;
	for (i = 0; i < allsingerscount; i++)
		if (allsingers[i].no == no)
		{
			displaysinger(allsingers[i]);
			return;
		}
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}

void promptsearchtotalbyno()
{
	int no;
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%d", &no);
	searchtotalbyno(no);
}

//����ɼ���Ϣ
void inputname(char str[])
{
	printf("����������(2-45���ַ�)�����ܴ��ո�Tab��س���:");
	scanf("%s", str);
	printf("�����������ΪΪ %s \r\n", str);
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

void createsamplesingers()
{
	FILE *fp = fopen(FILE_STU, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, FORMATNET, 33, "Smile", 13, 83, 63, 93);
	fprintf(fp, FORMATNET, 44, "Lukas", 14, 84, 64, 94);
	fprintf(fp, FORMATNET, 55, "Shawn", 15, 85, 65, 95);
	fprintf(fp, FORMATNET, 22, "Tony", 12, 82, 62, 92);
	fprintf(fp, FORMATNET, 11, "Flex", 11, 81, 61, 91);
	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽singer.txt��\n");
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
	printf("ɾ����ϣ�ʣ��%d����\r\n", allsingerscount);

}

void promptremovesinger()
{
	int no;
	printf("������Ҫɾ����ѧ��:");
	scanf("%d", &no);
	removesinger(no);
}


int login()
{
	char name[50] = "";
	char pwd[50] = "";
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n����������\n");
	scanf("%s", pwd);
	return streq(name, "username")
		&& streq(pwd, "password");
}


int calctotal(int math, int english, int chinese, int c)
{
	return math + english + chinese + c;
}

float calcave(int total)
{
	return total / 4.0f;
}

void addsinger(int no, char name[], int math, int english, int chinese, int c)
{
	singer sgr;
	sgr.no = no;
	strcpy(sgr.name, name);
	sgr.score = math;
	//sgr.english = english;
	//sgr.chinese = chinese;
	//sgr.c = c;
	allsingers[allsingerscount++] = sgr;
}

void calcanddisplaytotalandaverage()
{
	//int i;
	//singer sgr;
	//printf("���и����ܷ֡�ƽ��������\r\n");
	//printf("--------------------------------------------\r\n");
	//for (i = 0; i < allsingerscount; i++)
	//{
	//	sgr = allsingers[i];
	//	allsingers[i].total = sgr.total = calctotal(sgr.score, sgr.english, sgr.chinese, sgr.c);
	//	allsingers[i].average = sgr.average = calcave(sgr.total);
	//	printf("%d\t%s\t%d\t%.1f\r\n", sgr.no, sgr.name, sgr.total, sgr.average);
	//}
	//printf("--------------------------------------------\r\n");
}

void calcanddisplaysubject(char *subuject, int scores[])
{
	int i, sum = 0, below60 = 0;
	for (i = 0; i < allsingerscount; i++)
	{
		sum += scores[i];
		if (scores[i] < 60)
			below60++;
	}
	printf("��Ŀ:%s ƽ����%.1f�������ʰٷ�֮%.1f���������ʰٷ�֮%.1f\r\n", subuject,
		(sum / (float)allsingerscount),
		(1 - below60 / (float)allsingerscount)*100.0f,
		(below60 / (float)allsingerscount)*100.0f
	);
}


void calcanddisplayallsubjects()
{
	int i, sum = 0, below60 = 0;
	int scores[100];
	singer sgr;
	printf("���п�Ŀ�ɼ�ͳ������\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allsingerscount; i++)
	{
		scores[i] = allsingers[i].score;
	}
	calcanddisplaysubject("��ѧ", scores);


	calcanddisplaysubject("C����", scores);
	printf("--------------------------------------------\r\n");
}

void promptaddsinger()
{
	int no; char name[MAX_STRLEN] = ""; int math; int english; int chinese; int c;
	printf("\n������ѧ��\n");
	scanf("%d", &no);
	printf("\n�������û���\n");
	scanf("%s", name);
	printf("\n��������ѧ��Ӣ����ġ�c���Գɼ������������ո����\n");
	scanf("%d%d%d%d", &math, &english, &chinese, &c);
	addsinger(no, name, math, english, chinese, c);
	printf("��ɵ�%d�����¼��!\r\n", allsingerscount);
}


int main()
{
	int choice = -1;

	/*if (login())
	{
		printf("login ok\n");
	}
	else
		printf("login fail\n");*/

	createsamplesingers();


	////printf("\n%d\n", allsingerscount);
	///*promptaddsinger();
	//writeallsingers();*/
	///*promptremovesinger();
	//writeallsingers();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	////displayallsingers();
	//calcanddisplaytotalandaverage();
	//sortanddisplay();
	//calcanddisplayallsubjects();

	//countbygrades();

	while (choice != 0)
	{
		char *menu = "**********************�˵�****************************\n"
			"��1��������ѧ������               ��6����ѧ�Ƽ������\n"
			"��2��������������ѯ               ��7����ѧ����������\n"
			"��3��������ѧ�Ų�ѯ               ��8��������ѧ������\n"
			"��4�������ѧ������               ��9�� : �鿴ѧ������\n"
			"��5����ɾ��ѧ������               ��10���������ƽ����\n"
			"��0�����˳�����ϵͳ";
		printf("������ѡ�����֣����س�\n", menu);
		printf("%s\n", menu);
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			system("pause");
			exit(0);
			break;
		case 1:

			break;
		case 2:
			promptsearchtotalbyname();
			break;
		case 3:
			promptsearchtotalbyno();
			break;
		case 4:
			promptaddsinger();
			break;
		case 5:
			promptremovesinger();
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
		getch();
	}
	fseek(stdin, 0, SEEK_END);
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}

