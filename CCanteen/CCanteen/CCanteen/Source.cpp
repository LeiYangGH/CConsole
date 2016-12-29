#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //����ʱ��1�� ����ʱ��0
#define CANTEEN_COUNT 5 //5��ʳ��
#define MEAL_COUNT 3 //������3��
#define MAX_COUNT 20 //�ݶ����20�����ݣ�����
#define MAX_STRLEN 20 //�ַ��������
#define FORMAT_STU "%s\t%s\t%s\r\n" //\r is for write
#define MEMBERS_STU stu.no, stu.name, stu.sex
#define FORMAT_RCD "%s\t%s\t\%d\n"
#define MEMBERS_RCD rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_FD "%s\t%s\t%.1f\r\n"
#define MEMBERS_FD fd.name, fd.taste, fd.price
#define LINE  "\n------------------------\n"
#define FILE_STU "stu.txt"
#define FILE_FD "fd.txt"
#define FILE_SELL "sl.txt"
#define FILE_SELL_ID "slid.txt"
typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	char sex[MAX_STRLEN];
}student;
typedef struct rentcd
{
	int cdno;
	char cdname[MAX_STRLEN];
	int cuno;
	char cuname[MAX_STRLEN];
	int days;
	int isreturned;
}rentcd;
typedef struct food
{
	char name[MAX_STRLEN];
	char taste[MAX_STRLEN];
	float price;
}food;
//�������ݶ��洢��������3���ṹ����������
student allstudents[MAX_COUNT];
int allstudentscount = 0;

rentcd allrentcds[MAX_COUNT];
int allrentcdscount = 0;

food allfoods[MAX_COUNT];
int allfoodscount = 0;

//ÿ�����ʳ�õĲ���(�±�)
//3���±����δ���ʳ�á����������ȱ�ţ�����0��ʼ
int sellfoods[CANTEEN_COUNT][MEAL_COUNT][MAX_COUNT] = { 0 };
//����ʳ�ø��ٵĲ�����������
int sellfoodscount[CANTEEN_COUNT][MEAL_COUNT] = { 0 };

//char meals[] = { '��','��', '��' };
char *meals[] = { "��","��","��" };
//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

float tofloat(char *s)
{
	char *end;
	return (float)strtol(s, &end, 10);
}

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
}
//display all��ʾȫ��������displaystudent��ʾ���У���ͬ
void displayallstudents()
{
	int i;
	printf("����ѧ���������\n");
	printf("���\t����\n");
	printf(LINE);
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf(LINE);
}
void displayrentcd(rentcd rcd)
{
	printf(FORMAT_RCD, MEMBERS_RCD);
}

void displayallrentcds()
{
	int i;
	printf("����ѧ������������\n");
	printf("ѧ��\t����\t����\n");
	printf(LINE);
	for (i = 0; i < allrentcdscount; i++)
	{
		if (allrentcds[i].isreturned == 0)
			displayrentcd(allrentcds[i]);
	}
}


student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			strcpy(stu.sex, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}



void createsamplestudents()
{
	FILE *fp = fopen(FILE_STU, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		return;
	}
	fprintf(fp, FORMAT_STU, "01", "smile", "F");
	fprintf(fp, FORMAT_STU, "02", "lukas", "M");
	fprintf(fp, FORMAT_STU, "03", "shawn", "F");
	fprintf(fp, FORMAT_STU, "04", "tony", "M");
	fprintf(fp, FORMAT_STU, "05", "stu5", "F");
	fprintf(fp, FORMAT_STU, "06", "stu6", "F");
	fprintf(fp, FORMAT_STU, "07", "stu7", "M");
	fprintf(fp, FORMAT_STU, "08", "stu8", "F");
	fprintf(fp, FORMAT_STU, "09", "stu9", "M");
	fprintf(fp, FORMAT_STU, "10", "stu10", "F");
	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽student.txt��\n");
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!\n", FILE_STU);
		createsamplestudents();
		fp = fopen(FILE_STU, "r");
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allstudents[allstudentscount++] = getstudentfromline(line);
	}
	printf("\n�Ѷ����ļ�!", FILE_STU);

}

void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_STU, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_STU);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, FORMAT_STU, MEMBERS_STU);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

//��ӵ���
void addstudent(char * no, char *name, char *sex)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	strcpy(stu.sex, sex);
	allstudents[allstudentscount++] = stu;
	writeallstudents();
}

//Ҫ���û����룬��������addstudent����ͬ���ֿ�����������Ϊ�˲��Է���
void inputstudents()
{
	//int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char sex[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������ѧ�����(������q����):");
		scanf("%s", no);
		if (streq(no, "q"))
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������ѧ�����ơ��Ա𣬶��ŷָ����س�����:");
		scanf("%s%s", name, sex);
		addstudent(no, name, sex);
		printf("\nCD%s��Ϣ��ӳɹ�!\n", name);
	}
}
/////////////food start//////////////
void displayfood(food fd)
{
	printf(FORMAT_FD, MEMBERS_FD);
	printf("\n");
}
void displayallfoods()
{
	int i;
	printf("���в�������\n");
	printf("����\t��ζ\t�۸�\n");
	printf(LINE);
	for (i = 0; i < allfoodscount; i++)
	{
		displayfood(allfoods[i]);
	}
	printf(LINE);
}

void writeallfoods()
{
	int i;
	food fd;
	FILE *fp = fopen(FILE_FD, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_FD);
		getchar();
		exit(1);
	}


	for (i = 0; i < allfoodscount; i++)
	{
		fd = allfoods[i];
		fprintf(fp, FORMAT_FD, MEMBERS_FD);
	}
	fclose(fp);
	printf("�ѱ�����ȵ��ļ���");
}

void addfood(char *name, char *taste, float price)
{
	int i;
	food fd;
	strcpy(fd.name, name);
	strcpy(fd.taste, taste);
	fd.price = price;
	allfoods[allfoodscount++] = fd;
	writeallfoods();
}

void inputfoods()
{
	int i;
	float price;
	char name[MAX_STRLEN] = "";
	char taste[MAX_STRLEN] = "";
	char pstr[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n�������������(q����):");
		scanf("%s", name);
		if (streq(name, "q"))
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n����������������۸��м�ո�ָ����س�����:");
		scanf("%s%s", taste, pstr);
		price = atof(pstr);
		addfood(name, taste, price);
		printf("\n����%s��Ϣ��ӳɹ�!\n", name);
	}
}

food getfoodfromline(char *line)
{
	char *part;
	int index = 0;
	food fd;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(fd.name, part);
			break;
		case 2:
			strcpy(fd.taste, part);
			break;
		case 3:
			fd.price = tofloat(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return fd;
}

void createsamplefoods()
{
	FILE *fp = fopen(FILE_FD, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		return;
	}
	fprintf(fp, FORMAT_FD, "fish", "fry", 9.0f);
	fprintf(fp, FORMAT_FD, "beaf", "bake", 30.0f);
	fprintf(fp, FORMAT_FD, "food3", "stew", 15.0f);
	fprintf(fp, FORMAT_FD, "food4", "stew", 15.0f);
	fprintf(fp, FORMAT_FD, "food5", "stew", 15.0f);
	fprintf(fp, FORMAT_FD, "food6", "stew", 15.0f);
	fprintf(fp, FORMAT_FD, "food7", "stew", 15.0f);
	fprintf(fp, FORMAT_FD, "food8", "stew", 15.0f);
	fprintf(fp, FORMAT_FD, "food9", "stew", 15.0f);
	fprintf(fp, FORMAT_FD, "food10", "stew", 15.0f);
	fclose(fp);
	printf("5��ʾ���ɼ������ѱ��浽food.txt��\n");
}

void readallfoods()
{
	char line[200];
	FILE *fp = fopen(FILE_FD, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!\n", FILE_FD);
		createsamplefoods();
		fp = fopen(FILE_FD, "r");
	}
	allfoodscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allfoods[allfoodscount++] = getfoodfromline(line);
	}
	printf("\n�Ѷ����ļ�!", FILE_FD);

}


//////////////////////food end///////////////
//ͨ�����Ʋ���stu������������student��ָ�룬��ͬ
void findstudentbyname(char *cdname, student **stu)
{
	int i;
	int found = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].name, cdname))
		{
			*stu = &allstudents[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("û�ҵ�����Ϊ%s��ѧ��\n", cdname);
		*stu = NULL;
	}
}

void findfoodbyname(char *cuname, food **fd)
{
	int i;
	int found = 0;
	for (i = 0; i < allfoodscount; i++)
	{
		if (streq(allfoods[i].name, cuname))
		{
			*fd = &allfoods[i];
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("û�ҵ�����Ϊ%s�Ĳ���\n", cuname);
		*fd = NULL;
	}
}

//����һ�����ҵ�
void findcunamebycdname(char *cdname, char *cuname)
{
	int i;
	for (i = 0; i < allrentcdscount; i++)
	{
		if (streq(allrentcds[i].cdname, cdname))
		{
			strcpy(cuname, allrentcds[i].cuname);
			break;
		}
	}
}

/////////////sell start//////////////
int random(int min, int max)
{
	return rand() % (max - min) + min;
}

void generaterandomfoodids(int ids[], int cnt)
{
	int i;
	int r, ri, ucnt = 0, top;
	int allids[MAX_COUNT];
	for (i = 0; i < allfoodscount; i++)
	{
		allids[i] = i;
	}
	while (ucnt < cnt)
	{
		ri = random(0, allfoodscount - ucnt);
		ids[ucnt++] = r = allids[ri];
		top = allfoodscount - ucnt - 1;
		if (r < top)
		{
			allids[r] = allids[top];
		}
	}
}

void generatesellfoodsforonecateenonemeal()
{
	int i, j, k, fdcnt;
	int ids[MAX_COUNT] = { 0 };
	for (i = 0; i < CANTEEN_COUNT; i++)
	{
		for (j = 0; j < MEAL_COUNT; j++)
		{
			//ÿ��ʳ��ÿ�ٵĲ������࣬����2�����Ϊȫ�����ȵ�һ��
			//�����������
			//Ŀǰ�۸���ͬһ�ģ������ϸ��õ��������ø���ʳ�ü۸��ڱ�׼�۸����¸���
			fdcnt = random(2, allfoodscount / 2);
			generaterandomfoodids(ids, fdcnt);
			for (k = 0; k < fdcnt; k++)
			{
				sellfoods[i][j][k] = ids[k];
			}
			sellfoodscount[i][j] = fdcnt;
		}
	}
	printf("������ÿ�ղ˵���");
}
//�����ֱ�Ϊʳ�á����������ȱ�ţ�0��ʼ��
void writeonesellfoodids(FILE *fp, int i, int j, int id)
{
	char cat[MAX_STRLEN] = "";
	food fd = allfoods[id];
	fprintf(fp, "%d\t%d\t%d\r\n%", i, j, id);
}

void writeonesellfoods(FILE *fp, int i, int j, int id)
{
	char cat[MAX_STRLEN] = "";
	food fd = allfoods[id];
	fprintf(fp, "ʳ��%d\t%s\t%s\t%s\t%.1f\r\n%", i + 1, meals[j],
		fd.name, fd.taste, fd.price);
}

void writeallsellfoods()
{
	int i, j, k, fdcnt;
	int ids[MAX_COUNT] = { 0 };
	FILE *fp = fopen(FILE_SELL, "w+");
	FILE *fpid = fopen(FILE_SELL_ID, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_SELL);
		return;
	}
	for (i = 0; i < CANTEEN_COUNT; i++)
	{
		for (j = 0; j < MEAL_COUNT; j++)
		{
			for (k = 0; k < sellfoodscount[i][j]; k++)
			{
				writeonesellfoods(fp, i, j, sellfoods[i][j][k]);
				writeonesellfoodids(fpid, i, j, sellfoods[i][j][k]);
			}
		}
	}
	fclose(fp);
	fclose(fpid);
	printf("�ѱ���ÿ�ղ˵����ļ���");
}
/////////////sell end//////////////


int main()
{
	int choice = -1;
	char *s = "2";
	int f = atoi(s);
	//������Щ�ǲ���ʱ������Եģ�����ɾ��
	//createsamplestudents();
	readallstudents();
	displayallstudents();

	readallfoods();
	displayallfoods();

	generatesellfoodsforonecateenonemeal();
	writeallsellfoods();
#if DEV
	//������Щ�ǲ���ʱ������Եģ�����ɾ��

#else
	while (choice != 0)
	{
		printf("\n\t ѧ��ѡ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ����ѧ����Ϣ");
		printf("\n\t 2. �鿴����ѧ��");
		printf("\n\t 3. ���Ӳ�����Ϣ");
		printf("\n\t 4. �鿴���в���");
		//printf("\n\t 5. ����ѧ��");
		//printf("\n\t 6. �鿴����ѧ���������");
		//printf("\n\t 7. �鿴ĳλ����ѧ���������");
		//printf("\n\t 8. �黹ѧ��");
		printf("\n\n  ��ѡ��: ");
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
			inputstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			displayallstudents();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			inputfoods();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			displayallfoods();
			break;
			//case '5':
			//	printf("\n\n��ѡ���� 5\n");
			//	inputrent();
			//	break;
			//case '6':
			//	printf("\n\n��ѡ���� 6\n");
			//	displayallrentcds();
			//break;
			//case '7':
			//	printf("\n\n��ѡ���� 7\n");
			//	inputanddisplayonefoodrentcds();
			//	break;
			//case '8':
			//	printf("\n\n��ѡ���� 8\n");
			//	inputreturn();
			//	break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}