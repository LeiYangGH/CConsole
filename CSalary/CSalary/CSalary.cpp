#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_per "salary.txt"
#define MAX_STRLEN 20
//��ţ��������������ʡ����𡢱��ա�ʵ������
typedef struct salary
{
	char no[20];
	char name[20];
	int basic;
	int bonus;
	int insurance;
	int real;
}salary;

salary allsalarys[100];
int allsalaryscount = 0;

//�ַ������
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


void displaysalary(salary s)
{
	printf("%s\t%s\t%d\t%d\t%d\t%d\n", s.no, s.name, s.basic, s.bonus, s.insurance, s.real);
}
void displayallsalarys()
{
	int i;
	printf("����%dλԱ��������Ϣ����\r\n", allsalaryscount);
	printf("���\t����\t����\t����\t����\tʵ��\r\n", allsalaryscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allsalaryscount; i++)
	{
		displaysalary(allsalarys[i]);
	}
	printf("--------------------------------------------\r\n");
}

void setreal(salary *s)
{
	s->real = s->basic + s->bonus - s->insurance;
}

//��һ���ı����벢����\t���Ų�֣���ϳ�һ��salary
salary getsalaryfromline(char *line)
{
	char *part;
	int index = 0;
	salary s;
	s.real = 0;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(s.no, part);
			break;
		case 2:
			strcpy(s.name, part);
			break;
		case 3:
			s.basic = toint(part);
			break;
		case 4:
			s.bonus = toint(part);

			break;
		case 5:
			s.insurance = toint(part);
			break;
		case 6:
			s.real = toint(part);
			break;
		case 7:
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	if (s.real == 0)
		setreal(&s);
	return s;
}

void readallsalarys()
{
	char line[200];
	FILE *fp = fopen(FILE_per, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_per);
		printf("\n\n��������˳�\n");
		system("pause");
		exit(0);
	}
	else
	{
		allsalaryscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allsalarys[allsalaryscount++] = getsalaryfromline(line);
		}
		printf("\n�Ѷ����ļ�!", FILE_per);
	}
}

//qsort�ǿ�������Ҫ������д��������age����
int cmpfunc(const void * b, const void * a)
{
	return ((salary*)a)->basic - ((salary*)b)->basic;
}

void sortsalarysanddisplay()
{
	int i;
	qsort(allsalarys, allsalaryscount, sizeof(salary), cmpfunc);
	printf("��ÿ��Ա�������������������\r\n");
	displayallsalarys();
}

//���ݱ�Ų�����������
int getsalaryidexbyname(char name[50])
{
	int i;
	for (i = 0; i < allsalaryscount; i++)
	{
		if (streq(allsalarys[i].name, name))
			return i;
	}
	return -1;//û�ҵ�
}

void writeallsalarys()
{
	int i;
	salary s;
	FILE *fp = fopen(FILE_per, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_per);
		getchar();
		exit(1);
	}
	for (i = 0; i < allsalaryscount; i++)
	{
		s = allsalarys[i];
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\n", s.no, s.name, s.basic, s.bonus, s.insurance, s.real);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void editsalary(char id[50])
{
	int i;
	i = getsalaryidexbyname(id);
	if (i >= 0)
	{
		printf("\n�������µĻ������ʡ����𡢱��գ����������������ո����\n");
		scanf("%d%d%d", &allsalarys[i].basic, &allsalarys[i].bonus, &allsalarys[i].insurance);
		setreal(&allsalarys[i]);
		writeallsalarys();
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧ������Ա����\r\n");
	}
}

void prompteditsalary()
{
	char name[50];
	printf("������Ҫ�޸Ĺ��ʵ�Ա������:");
	scanf("%s", &name);
	editsalary(name);
}



int main()
{
	char choice = -1;
#if 0//�����ã�if���ɾ��
	readallsalarys();
	//addsalary("05", "n5", "20170605", 41, 92, 93);
	//addsalary("06", "n6", "20170606", 46, 96, 96);

	//editsalary("01");
	////printf("\n%d\n", allsalaryscount);
	displayallsalarys();
	promptaddsalary();
	displayallsalarys();
	//promptsearchbetweenage();
	//prompteditsalary();
	//writeallsalarys();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	//promptremovesalary();
	//sortsalarysbytotalanddisplay();
	//displayallsalarys();
	//sortsalarysbytotal();
	//prompteditsalary();
	//displayallsalarys();


	system("pause");

#endif
	readallsalarys();
	while (choice != 0)
	{
		printf("\n\t Ա��������Ϣ����ϵͳ");
		printf("\n\t 2---��ʾ���ʼ�¼");
		printf("\n\t 5---���������޸Ĺ�������");
		printf("\n\t 6---���ݻ������ʽ�������");
		printf("\n\t 7---�˳�");
		printf("\n��ѡ��:");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '7':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0); break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallsalarys();
			break;
		case '5':
			printf("\n\n��ѡ���� c\n");
			prompteditsalary();
			break;
		case '6':
			printf("\n\n��ѡ���� f\n");
			sortsalarysanddisplay();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}

