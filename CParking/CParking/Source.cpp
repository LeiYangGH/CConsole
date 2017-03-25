#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define MAX_QUESTIONS_COUNT 98
#define PARK_FILE "park.txt"

#define TEST 0

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

int checktimevalid(int t)
{
	if (t > 0 && t < 24)
		return 1;
	else
	{
		printf("ʱ��ֻ��������1��23֮���������\n");
		return 0;
	}
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

void writeallparks()
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

int checknoexists(char *no)
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

int checkparkinexists(char *no)
{
	int i;
	for (i = 0; i < allparkscount; i++)
	{
		if (streq(allparks[i].no, no) && allparks[i].intime > 0)
		{
			return 1;
		}
	}
	return 0;
}

int checkparkoutexists(char *no)
{
	int i;
	for (i = 0; i < allparkscount; i++)
	{
		if (streq(allparks[i].no, no) && allparks[i].outtime > 0)
		{
			return 1;
		}
	}
	return 0;
}

void addparkin(char *no, int intime)
{
	int i;
	park p;
	if (!checktimevalid(intime))
		return;
	if (checknoexists(no))
	{
		if (checkparkinexists(no))
		{
			printf("����%s�Ѿ����룬�����ٴεǼǣ�\n", no);
		}
		else
		{
			for (i = 0; i < allparkscount; i++)
			{
				if (streq(allparks[i].no, no))
				{
					allparks[i].intime = intime;
					break;
				}
			}
		}
	}
	else
	{
		strcpy(p.no, no);
		p.intime = intime;
		p.outtime = 0;
		allparks[allparkscount++] = p;
		writeallparks();
	}
}


void promptaddparkin()
{
	char no[20] = "";
	int intime = 0;
	printf("����������Ҫ����ĳ��ƺź�ʱ��(1-23)���ո�������س�����:\n");
	scanf("%s%d", no, &intime);
	fseek(stdin, 0, SEEK_END);
	addparkin(no, intime);
}

//--
void addparkout(char *no, int outtime)
{
	int i;
	if (!checktimevalid(outtime))
		return;
	if (checkparkinexists(no))
	{
		if (checkparkoutexists(no))
			printf("����%s�Ѿ��Ǽǹ��뿪�������ٴεǼǣ�\n", no);
		else
			for (i = 0; i < allparkscount; i++)
			{
				if (streq(allparks[i].no, no))
				{
					if (allparks[i].intime < outtime)
					{
						if (checktimevalid(outtime))
						{
							allparks[i].outtime = outtime;
							writeallparks();
						}
					}
					else
						printf("����%s��%d����룬�뿪ʱ��������ڽ���ʱ�䣡\n", no, allparks[i].intime);
					break;
				}
			}
	}
	else
		printf("����%s��δ�Ǽǽ��룬���ܵǼ��뿪��\n", no);
}


void promptaddparkout()
{
	char no[20] = "";
	int outtime = 0;
	printf("����������Ҫ�뿪�ĳ��ƺź�ʱ��(1-23)���ո�������س�����:\n");
	scanf("%s%d", no, &outtime);
	fseek(stdin, 0, SEEK_END);
	addparkout(no, outtime);
}
//

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

#if TEST
	//displayallparks();
	//promptaddparkin();
	addparkin("6", 1);
	addparkout("7", 24);
	readallparks();
	displayallparks();
#else
	char choice = ' ';
	while (choice != 0)
	{
		printf("\n\n\t---ͣ���շѹ���ϵͳ---\n");
		printf("\t 1. ���ͣ������\n");
		printf("\t 2. ���ͣ���뿪\n");
		//printf("\t 3. ɾ��ͣ����Ϣ\n");
		//printf("\t 4. �޸ĳ��ƺ�\n");
		printf("\t 5. �鿴����ͣ����Ϣ\n");
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
			promptaddparkin();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptaddparkout();
			break;
			//case '3':
			//	printf("\n\n��ѡ���� 3\n");
			//	displayallresults();
			//	break;
			//case '4':
			//	printf("\n\n��ѡ���� 4\n");
			//	promptaddpark();
			//	break;
		case '5':
			printf("\n\n��ѡ���� 5\n");
			displayallparks();
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