#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define MAX_STRLEN 20

typedef struct flight
{
	char no[MAX_STRLEN];
	char from[MAX_STRLEN];
	char to[MAX_STRLEN];
	int seats;
	int left;
}flight;

flight allflights[100];
int allflightscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void addstudent(char no[], char from[], char to[], int seats)
{
	flight stu;
	strcpy(stu.no, no);
	strcpy(stu.from, from);
	strcpy(stu.to, to);
	stu.seats = seats;
	allflights[allflightscount++] = stu;
}

void promptaddstudent()
{
	char no[MAX_STRLEN] = "";
	char from[MAX_STRLEN] = "";
	char to[MAX_STRLEN] = "";
	int seats = 0;
	printf("\n�����뺽���\n");
	scanf("%s", &no);
	printf("\n������ʼ����\n");
	scanf("%s", from);
	printf("\n������Ŀ�ĵ�\n");
	scanf("%s", to);
	printf("\n��������λ��\n");
	scanf("%d", &seats);
	addstudent(no, from, to, seats);
	printf("��ɵ�%d������¼��!\r\n", allflightscount);
}

void displayflight(flight stu)
{
	printf("\r\n");
	printf("%s\t%s\t%s\t%d\n", stu.no, stu.from, stu.to, stu.left);
}

void searchflight(char *from, char *to)
{
	int i;
	for (i = 0; i < allflightscount; i++)
		if (streq(allflights[i].from, from)
			&& streq(allflights[i].to, to))
			displayflight(allflights[i]);
	printf("û�ҵ���Ӧ�������Ϣ��\r\n");
}

void promptsearflight()
{
	char no[MAX_STRLEN] = "";
	char from[MAX_STRLEN] = "";
	char to[MAX_STRLEN] = "";
	printf("\n�������ѯʼ����\n");
	scanf("%s", from);
	printf("\n�������ѯĿ�ĵ�\n");
	scanf("%s", to);
	searchflight(from, to);
}

void bookflight(char *no)
{
	int i, found = 0;
	for (i = 0; i < allflightscount; i++)
		if (streq(allflights[i].no, no))
		{
			found = 1;
			if (allflights[i].left > 0)
			{
				allflights[i].left--;
				printf("��Ʊ�ɹ���\r\n");
			}
			else
			{
				printf("û����Ʊ�ˣ�\r\n");
			}
			break;

		}
	if (found == 0)
		printf("û�ҵ���Ӧ�������Ϣ��\r\n");
}

void promptbookflight()
{
	char no[MAX_STRLEN] = "";
	printf("\n�����뺽���\n");
	scanf("%s", &no);
	bookflight(no);
}


int main()
{
	int choice = -1;
	while (choice != 0)
	{
		system("CLS");
		printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |        ����ϵͳ          |");
		printf("\n\t          +---------------------------------+");
		printf("\n\t 1. ���뺽����Ϣ\n");
		printf("\n\t 2. ��ѯ����\n");
		printf("\n\t 3. ��Ʊ\n");
		printf("\n\t 4. ͳ�ƺ���\n");
		printf("\n\t 0. �˳�");
		printf("\n\n ��ѡ��: ");
		scanf("%1[01234]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			promptaddstudent();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptsearflight();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptbookflight();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			printf("\n\n������������2\n");
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	system("pause");
	return 0;
}
