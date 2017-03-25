#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define MAX_QUESTIONS_COUNT 98
#define PARK_FILE "park.txt"

#define TEST 1

typedef struct park
{
	char no[20];
	int intime;
	int outtime;
}park;
park allparks[20];
int allparkscount = 0;

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

void displaypark(park stu)
{
	printf("%s\t%d\t%d\r\n", stu.no, stu.intime, stu.outtime);
}

void displayallparks()
{
	int i;
	printf("����%d������Ϣ����\r\n", allparkscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allparkscount; i++)
	{
		displaypark(allparks[i]);
	}
	printf("--------------------------------------------\r\n");
}

park getparkfromline(char *line)
{
	char *part;
	int index = 0;
	park q;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.no, part);
			break;
		case 2:
			q.intime = toint(part);
			break;
		case 3:
			q.outtime = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	return q;
}


void readallparks()
{
	char line[200];
	FILE *fp = fopen(PARK_FILE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", PARK_FILE);
		getchar();
		exit(1);
	}
	allparkscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allparks[allparkscount++] = getparkfromline(line);
	}
	printf("\n�Ѷ����ļ�!\n");

}

void writeallparks(park re)
{
	int i;
	FILE *fp = fopen(PARK_FILE, "w");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", PARK_FILE);
		getchar();
		exit(1);
	}
	for (i = 0; i < allparkscount; i++)
	{
		park p = allparks[i];
		fprintf(fp, "%s\t%d\t%d\r\n", p.no, p.intime, p.outtime);
	}
	fclose(fp);
	printf("�ѱ��浽�ļ���");
}

int checkparkexists(char *no)
{
	int i;
	for (i = 0; i < allparkscount; i++)
	{
		if (streq(allparks[i].no, no))
		{
			return 1;
		}
	}
	return 0;
}

void addpark(char *no, int intime, int outtime)
{
	park re;
	char teamname[20] = "";
	//if (checkparkexists(name))
	//{
	//	printf("ѧ��%s�Ѵ��ڲ����ظ���ӡ�\n", name);
	//	return;
	//}
	strcpy(re.no, no);
	re.intime = intime;
	re.outtime = outtime;
	allparks[allparkscount++] = re;
	writeallparks(re);
}


//void promptaddpark()
//{
//	char no[20] = "";
//	char name[20] = "";
//	char idcard[20] = "";
//
//	printf("����������Ҫ��ӵ�ѧ�����š����������֤�ţ��������ո񣩣��ո�������س�����:\n");
//	scanf("%s%s%s", no, name, idcard);
//	fseek(stdin, 0, SEEK_END);
//	addpark(no, name, idcard);
//}

void createsampleparks()
{
	FILE *fp = fopen(PARK_FILE, "w");
	char *format = "%s\t%d\t%d\r\n";
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, format, "111", 1, 2);
	fprintf(fp, format, "222", 2, 4);
	fprintf(fp, format, "333", 3, 6);
	fprintf(fp, format, "444", 4, 8);
	fprintf(fp, format, "555", 5, 10);

	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽park.txt��\n");
}
int main()
{
	createsampleparks();
	readallparks();
	displayallparks();
#if TEST
	;
#else


	char choice = ' ';
	readallparks();

	while (choice != 0)
	{
		printf("\n\n\t---����ϵͳ---\n");
		printf("\t 1. ��¼\n");
		printf("\t 2. ѧ������\n");
		printf("\t 3. �鿴���гɼ�\n");
		printf("\t 4. ��ӿ�����Ϣ\n");
		printf("\t 5. ��ӿ���\n");
		printf("\t 0. �˳�");
		printf("\n\n ��ѡ��: ");
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
			login();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			inputcountandexam();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			displayallresults();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			promptaddpark();
			break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			promptaddquestion();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
			fseek(stdin, 0, SEEK_END);
			system("pause");
		}
	}
#endif // TEST

	system("pause");
	return 0;
}