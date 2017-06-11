#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "stuin.txt"//
#define FILE_ALLOUTPUT "stuout.txt"
#define MAX_STRLEN 20 //��ַ�������
#define GRADES_COUNT 5 //�ȼ�����

typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	int score;
}student;

student allstudents[1005];
int allstudentscount = 0;

float averagescore = 0;

FILE *outfile;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//��ʾһ��ѧ���ɼ�
void displaystudent(student stu)
{
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.score);
	fprintf(outfile, "%s\t%s\t%d\n", stu.no, stu.name, stu.score);
}

//��ʾ����ѧ���ɼ�
void displayallstudents()
{
	int i;
	printf("����%dλͬѧ��������\r\n", allstudentscount);
	printf("ѧ��\t����\t�ɼ�\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
		displaystudent(allstudents[i]);
	printf("--------------------------------------------\r\n");
}

//��һ���ı���ֲ���ϳ�һ��ѧ��
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, " \n");//��ֺ��������ո�ͻس�
	while (part != NULL)
	{
		switch (++index)//index���ı��������
		{
		case 1:
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			stu.score = toint(part);
		default:
			break;
		}
		part = strtok(NULL, " \n");
	}
	return stu;
}

//�����ֺܷ�ƽ����
void calctotalandave()
{
	int i, j;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum += allstudents[i].score;
	}
	averagescore = sum / (float)allstudentscount;
}

//���ļ�������ѧ��
void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_INPUT, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_INPUT);
		getchar();
		exit(1);
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)//�����Щ���ǿ��л��߲��淶
			continue;
		++allstudentscount;
	//ÿ��һ��ѧ��
		allstudents[allstudentscount - 1] = getstudentfromline(line);
	}
}

//�̶���ʽ���ȽϷ���
int cmpstuavefunc(const void * b, const void * a)
{
	return (((student*)a)->score - ((student*)b)->score);
}
//����ѧ������������
void sortstudetsbyscore()
{
	//qsort �������������Ǳ�׼c����ĺ���
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
}

//��ʾ��߷ֵ�ѧ��
void displayhigheststudents()
{
	int i = 0;
	printf("\n��߷�ͬѧ����\r\n");
	fprintf(outfile, "��߷�ͬѧ����\r\n");
	sortstudetsbyscore();
	printf("ѧ��\t����\t�ɼ�\n");
	fprintf(outfile, "ѧ��\t����\t�ɼ�\n");
	printf("--------------------------------------------\r\n");
	while (allstudents[i].score == allstudents[0].score)
		displaystudent(allstudents[i++]);
	printf("--------------------------------------------\r\n");
}

//���㲢��ʾƽ���ָ��ڡ����ڡ�����ƽ���ֵ�����
void countanddisplaycompareaveragecount()
{
	int i, t, low = 0, eq = 0, high = 0;
	calctotalandave();
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score;
		if (t < averagescore)
			low++;
		else if (t == averagescore)
			eq++;
		else if (t > averagescore)
			high++;
	}
	//printf("\nƽ���ɼ���%.2f\n", averagescore);
	printf("\nƽ���ɼ�����ƽ���ɼ���������%d\n", high);
	fprintf(outfile, "\nƽ���ɼ�����ƽ���ɼ���������%d\n", high);
	printf("ƽ���ɼ�����ƽ���ɼ���������%d\n", low);
	fprintf(outfile, "ƽ���ɼ�����ƽ���ɼ���������%d\n", low);
	printf("ƽ���ɼ�����ƽ���ɼ���������%d\n\n", eq);
	fprintf(outfile, "ƽ���ɼ�����ƽ���ɼ���������%d\n\n", eq);
}

//���㲢��ʾ���������εȼ��������Ͱٷֱ�
void countanddisplaygradescountandpercent()
{
	int i, t;
	int count[GRADES_COUNT] = { 0 };
	char *grades[GRADES_COUNT] = { "������(0��59)","����(60��69)", "�е�(70��79)", "����(80��89)", "����(90��100)", };
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score;
		if (t < 60)
			count[0]++;
		else if (t >= 60 && t <= 69)
			count[1]++;
		else if (t >= 70 && t <= 79)
			count[2]++;
		else if (t >= 80 && t <= 89)
			count[3]++;
		else if (t >= 90)
			count[4]++;
	}
	printf("������\t����\t�ٷֱ�\n");
	fprintf(outfile, "������\t����\t�ٷֱ�\n");
	for (i = 0; i < GRADES_COUNT; i++)
	{
		printf("%s\t%d\t%d%%\n", grades[i], count[i], (int)(count[i] * 100 / (float)allstudentscount));
		fprintf(outfile, "%s\t%d\t%d%%\n", grades[i], count[i], (int)(count[i] * 100 / (float)allstudentscount));
	}
}

//������
int main()
{
	outfile = fopen(FILE_ALLOUTPUT, "a+");
	if (outfile == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_ALLOUTPUT);
		getchar();
		exit(1);
	}
	readallstudents();
	//displayallstudents();
	displayhigheststudents();
	countanddisplaycompareaveragecount();
	countanddisplaygradescountandpercent();
	fclose(outfile);
	printf("������������ļ�%s\n", FILE_ALLOUTPUT);
	system("pause");
	return 0;
}
