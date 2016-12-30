#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //����ʱ��1�� ����ʱ��0
#define CANTEEN_COUNT 5 //5��ʳ��
#define MEAL_COUNT 3 //������3��
#define MAX_COUNT 50 //�ݶ����20�����ݣ�����
#define DK_COUNT 3 //�������࣬��������û˵�������࣬����3��ʾ��
#define MAX_STRLEN 20 //�ַ��������
#define FORMAT_STU "%s\t%s\t%s\r\n" //\r is for write
#define MEMBERS_STU stu.no, stu.name, stu.sex
//#define FORMAT_BUY "%s\t%s\t\%d\n"
//#define MEMBERS_BUY rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_FD "%s\t%s\t%.1f\r\n"
#define MEMBERS_FD fd.name, fd.taste, fd.price
#define FORMAT_DK "%s\t%d\t%d\t%d\r\n"
#define MEMBERS_DK dk.name, dk.fresh, dk.canreturn, dk.returned
#define LINE  "\n------------------------\n"
#define FILE_STU "stu.txt"
#define FILE_FD "fd.txt"
#define FILE_DK "dk.txt"
#define FILE_SELL "sl.txt"
#define FILE_SELL_ID "slid.txt"
#define FILE_BUY "buy.txt"
#define FILE_BUY_ID "buyid.txt"
typedef struct student
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN];
	char sex[MAX_STRLEN];
}student;
typedef struct food
{
	char name[MAX_STRLEN];
	char taste[MAX_STRLEN];
	float price;
}food;

typedef struct drink
{
	char name[MAX_STRLEN];
	//���ʵ�
	int fresh;
	//�����ˣ�Ҳ�����ϴ���������������˵�����Ϊ�ϴι��������
	int canreturn;
	//�˻���
	int returned;
}drink;

typedef struct buydetail
{
	int stuid;
	int fdid;
	// ���Լ�ʳ�á����ڡ��ͱ�ȣ�����������û�ᵽ��Ҫ����������ݣ�����û��
}buydetail;

//�������ܶƶ������ʱ����
typedef struct buytotal
{
	int stuid;
	float total;
}buytotal;
//�������ݶ��洢��������3���ṹ����������
student allstudents[MAX_COUNT];
int allstudentscount = 0;

buydetail allrentcds[MAX_COUNT];
int allrentcdscount = 0;

food allfoods[MAX_COUNT];
int allfoodscount = 0;

drink alldrinks[DK_COUNT];

//ÿ�����ʳ�õĲ���(�±�)
//3���±����δ���ʳ�á����������ȱ�ţ�����0��ʼ
int sellfoods[CANTEEN_COUNT][MEAL_COUNT][MAX_COUNT] = { 0 };
//����ʳ�ø��ٵĲ�����������
int sellfoodscount[CANTEEN_COUNT][MEAL_COUNT] = { 0 };

char *meals[] = { "��","��","��" };
char currentmeal[MAX_STRLEN] = "��";//��ǰĬ��Ϊ����

//��ǰ�û�
char currentuname[MAX_STRLEN] = "";
int currentstuid = -1;

buydetail allbuydetails[200];//���ڿ��Բ������ӵģ����Ʒſ�һЩ
int allbuydetailscount = 0;

buytotal allbuytotals[MAX_COUNT];
int allbuytotalscount = 0;

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
	fprintf(fp, FORMAT_STU, "10", "admin", "F");//����Ա�ʺţ�����ɾ
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
	fclose(fp);
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
	fclose(fp);
	printf("\n�Ѷ����ļ�!", FILE_FD);

}


//////////////////////food end///////////////


//////////////////////drink start///////////////
void displaydrink(drink dk)
{
	printf(FORMAT_DK, MEMBERS_DK);
	printf("\n");
}
void displayalldrinks()
{
	int i;
	printf("������������\n");
	printf("����\t����\t����\t�˻�\n");
	printf(LINE);
	for (i = 0; i < DK_COUNT; i++)
	{
		displaydrink(alldrinks[i]);
	}
	printf(LINE);
}

void writealldrinks()
{
	int i;
	drink dk;
	FILE *fp = fopen(FILE_DK, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_DK);
		getchar();
		exit(1);
	}
	for (i = 0; i < DK_COUNT; i++)
	{
		dk = alldrinks[i];
		fprintf(fp, FORMAT_DK, MEMBERS_DK);
	}
	fclose(fp);
	printf("�ѱ������ϵ��ļ���");
}

void adddrink(int dkid, int count)
{
	int i;
	alldrinks[dkid].fresh += count;
	writealldrinks();
}

void buydrink(int dkid, int fcnt, int rcnt)
{
	drink dk = alldrinks[dkid];
	//���Ҫ����������ڵ�ǰʣ������������ʵ��ʣ����������
	if (dk.fresh == 0 && fcnt > 0
		|| dk.returned == 0 && rcnt > 0)
	{
		printf("����û�ˣ�");
		return;
	}
	fcnt = fcnt > dk.fresh ? dk.fresh : fcnt;
	rcnt = rcnt > dk.returned ? dk.returned : rcnt;
	alldrinks[dkid].fresh -= fcnt;
	alldrinks[dkid].canreturn -= rcnt;
	printf("�������ϳɹ���%s����%d ���%d\n", dk.name, fcnt, rcnt);
	writealldrinks();
}

void warndrinklack(int dkid)
{
	drink dk = alldrinks[dkid];
	if (dk.fresh + dk.returned <= 3)
		printf("����%s�ý����ˣ�\n", dk.name);
}

void inputbuydrinks()
{
	int id1, fcnt, rcnt;
	float price;
	char name[MAX_STRLEN] = "";
	char taste[MAX_STRLEN] = "";
	char pstr[MAX_STRLEN] = "";
	displayalldrinks();

	printf("\n������Ҫ�������ţ����ϵ�������1��3��:");
	scanf("%d", &id1);
	if (id1 < 1 || id1 > 3)
	{
		printf("\n���������Ų��Ϸ���");
		return;
	}
	printf("��ѡ���˹���%s.\n", alldrinks[id1 - 1].name);
	printf("\n������������Ҫ�������ʵ���������ǰ�˹��������������ܳ������п�棩���м�ո�ָ����س�����:");
	scanf("%d%d", &fcnt, &rcnt);
	buydrink(id1 - 1, fcnt, rcnt);
	printf("\n����%s��Ϣ��ӳɹ�!\n", name);
	warndrinklack(id1 - 1);
	fseek(stdin, 0, SEEK_END);
}

drink getdrinkfromline(char *line)
{
	char *part;
	int index = 0;
	drink dk;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(dk.name, part);
			break;
		case 2:
			dk.fresh = toint(part);
			break;
		case 3:
			dk.canreturn = toint(part);
			break;
		case 4:
			dk.returned = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return dk;
}

void createsampledrinks()
{
	FILE *fp = fopen(FILE_DK, "wb");
	printf("����ʾ���ɼ�����...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		return;
	}
	fprintf(fp, FORMAT_DK, "cola", 5, 0, 0);
	fprintf(fp, FORMAT_DK, "walter", 5, 0, 0);
	fprintf(fp, FORMAT_DK, "mill", 5, 0, 0);
	fclose(fp);
	printf("3��ʾ���ɼ������ѱ��浽drink.txt��\n");
}

void readalldrinks()
{
	char line[200];
	int alldrinkscount = 0;
	FILE *fp = fopen(FILE_DK, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!\n", FILE_DK);
		createsampledrinks();
		fp = fopen(FILE_DK, "r");
	}
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 3)
			continue;
		alldrinks[alldrinkscount++] = getdrinkfromline(line);
	}
	fclose(fp);
	printf("\n�Ѷ����ļ�!", FILE_DK);

}
//////////////////////drink end///////////////


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
			currentstuid = i;
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

void addsellfood(int i, int j, int id)
{
	sellfoods[i][j][sellfoodscount[i][j]++] = id;
}

void getsellidsfromline(char *line)
{
	int i, j, id;
	char *part;
	int index = 0;
	food fd;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			i = toint(part);
			break;
		case 2:
			j = toint(part);
			break;
		case 3:
			id = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	addsellfood(i, j, id);
}

void initsellfoodscount()
{
	int i, j, k;
	for (i = 0; i < CANTEEN_COUNT; i++)
	{
		for (j = 0; j < MEAL_COUNT; j++)
		{
			sellfoodscount[i][j] = 0;
		}
	}
}

void readsellfoods()
{
	char line[200];
	FILE *fp = fopen(FILE_SELL_ID, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!\n", FILE_SELL_ID);
		generatesellfoodsforonecateenonemeal();
		writeallsellfoods();
		fp = fopen(FILE_SELL_ID, "r");
	}

	initsellfoodscount();

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 3)
			continue;
		getsellidsfromline(line);
	}
	fclose(fp);
	printf("\n�Ѷ�����������ļ�!");
}
/////////////sell end//////////////

/////////////select start//////////////

int iscurrentuserstudent()
{
	return (streq(currentuname, "") || streq(currentuname, "admin")) ? 0 : 1;
}

//���к���Ҳ��Ϊ�������û�ע��ѡ��˵��޸Ĳͱ�
int getcurrentmeal()
{
	int j;
	char msg[MAX_STRLEN] = "";
	if (streq(currentmeal, "��"))
	{
		j = 0;
		strcpy(msg, "���Ϻã�");
	}
	else if (streq(currentmeal, "��"))
	{
		j = 1;
		strcpy(msg, "����ã�");
	}
	else
	{
		j = 2;
		strcpy(msg, "���Ϻã�");
	}
	printf("%s\n", msg);
	return j;
}

int isidinlist(int i, int j, int id)
{
	int k, found = 0;
	for (k = 0; k < sellfoodscount[i][j]; k++)
	{
		if (sellfoods[i][j][k] == id)
		{
			return 1;
		}
	}
	return 0;
}

int selectfoodfromlist(int i, int j)
{
	int k, fdid, choice = -1;
	food fd;
	printf("�˵����£�\n");
	printf(LINE);
	printf("���\t����\t��ζ\t�۸�\n");
	for (k = 0; k < sellfoodscount[i][j]; k++)
	{
		fdid = sellfoods[i][j][k];
		fd = allfoods[fdid];
		printf("%d\t%s\t%s\t%.1f\n", fdid, fd.name, fd.taste, fd.price);
	}
	printf(LINE);
	while (!isidinlist(i, j, choice))
	{
		printf("��ѡ����Ҫ��Ĳ�ǰ�����ţ��س�������");
		scanf("%d", &choice);
	}
	return choice;
}

void appendonebuyfood(FILE *fp, FILE *fpid, int stuid, int i, int j, int fdid)
{
	char cat[MAX_STRLEN] = "";
	food fd = allfoods[fdid];
	fprintf(fp, "%s\tʳ��%d\t%s\t%s\t%s\t%.1f\r\n%", allstudents[stuid].name, i + 1, meals[j],
		fd.name, fd.taste, fd.price);
	//�ֱ�Ϊѧ��id��fdid
	fprintf(fpid, "%d\t%d\r\n%", currentstuid, fdid);
}

//�ٶ�������Ч��Χ��
//Ӧ�û������ڲ�������Ŀǰû��
void buyfood(int stuid, int i, int j, int fdid)
{
	food fd;
	FILE *fp, *fpid;
	fp = fopen(FILE_BUY, "a");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_BUY);
		return;
	}
	fpid = fopen(FILE_BUY_ID, "a");
	if (fpid == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_BUY_ID);
		return;
	}
	appendonebuyfood(fp, fpid, stuid, i, j, fdid);
	fclose(fp);
	fclose(fpid);
	printf("\n�����Ѿ�׷���ļ���");
}


void inputbuyfood()
{
	int i, j, id;
	food fd;
	if (iscurrentuserstudent())
	{
		j = getcurrentmeal();
		printf("�������������ĸ�ʳ�þͲͣ�����1��5�����س�����:");
		scanf("%d", &i);
		printf("��ѡ����ʳ��%d\n", i);
		id = selectfoodfromlist(i - 1, j);
		fd = allfoods[id];
		printf("����Ĳ���%d\t%s\t%s\t%.1f\n", id, fd.name, fd.taste, fd.price);
		buyfood(currentstuid, i, j, id);
	}
	else
	{
		printf("\nֻ����ѧ��������¼�����ò����ѣ�");
	}
}


/////////////select end//////////////

/////////////statics   start//////////////

buydetail getbuydetailfromline(char *line)
{
	char *part;
	int index = 0;
	buydetail buy;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			buy.stuid = toint(part);
			break;
		case 2:
			buy.fdid = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return buy;
}

void readallbuydetails()
{
	char line[200];
	FILE *fp = fopen(FILE_BUY_ID, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!\n", FILE_BUY_ID);
		return;
	}
	allbuydetailscount = 0;
	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 2)
			continue;
		allbuydetails[allbuydetailscount++] = getbuydetailfromline(line);
	}
	fclose(fp);
	printf("\n�Ѷ����ļ�!", FILE_STU);
}

void calcanddisplaypopularfood()
{
	int i, fdid, max = 0, maxid = -1;
	float sum = 0;
	int buyfreq[MAX_COUNT] = { 0 };//ÿ�ֲ��ȱ����ѵĴ���
	readallbuydetails();
	for (i = 0; i < allbuydetailscount; i++)
	{
		fdid = allbuydetails[i].fdid;
		sum += allfoods[fdid].price;//û�������Ĺ��ܣ�ֱ�ӼӼ�Ǯ
		if (max < ++buyfreq[fdid])
		{
			max = buyfreq[fdid];
			maxid = fdid;
		}
	}
	printf("\n���ܻ�ӭ�Ĳ�Ʒ��%s��������%d!\n", allfoods[fdid].name, max);
	printf("\n��������������%.1fԪ!\n", sum);
}

int cmpfunc(const void * a, const void * b)
{
	return ((buytotal*)a)->total - ((buytotal*)b)->total;
}
void calcanddisplaypoorstudents()
{
	int i, j, found;
	float sum = 0;
	int buyfreq[MAX_COUNT] = { 0 };//ÿ�ֲ��ȱ����ѵĴ���
	buydetail buy;
	readallbuydetails();
	allbuytotalscount = 0;
	for (i = 0; i < allbuydetailscount; i++)
	{
		buy = allbuydetails[i];
		found = 0;
		for (j = 0; j < allbuytotalscount; j++)
		{
			if (allbuytotals[j].stuid == buy.stuid)
			{
				allbuytotals[j].total += allfoods[buy.fdid].price;
				found = 1;
				break;
			}
		}
		if (found == 0)
		{
			allbuytotals[allbuytotalscount].stuid = buy.stuid;
			allbuytotals[allbuytotalscount].total += allfoods[buy.fdid].price;
			allbuytotalscount++;
		}
	}
	qsort(allbuytotals, allbuytotalscount, sizeof(buytotal), cmpfunc);
	printf("\n����ѧ�������������£����ⲻ�壬�������Щ��ƶ���������԰�ȫ�������������:\n", sum);
	for (i = 0; i < allbuytotalscount; i++)
	{
		buytotal buyto = allbuytotals[i];
		printf("%s\t%.1fԪ\n", allstudents[buyto.stuid].name, allbuytotals[i].total);
	}
}

/////////////statics end//////////////

int main()
{
	int choice = -1;
	student *curstu = NULL;
	//������Щ�ǲ���ʱ������Եģ�����ɾ��
	readallstudents();
	displayallstudents();

	readallfoods();
	displayallfoods();

	generatesellfoodsforonecateenonemeal();
	writeallsellfoods();

	readsellfoods();

	//strcpy(currentuname, "smile"); tony
	strcpy(currentuname, "tony");
	findstudentbyname(currentuname, &curstu);


	//buyfood(2, 3, 1, 2);
	//buyfood(2, 3, 1, 3);
	//buyfood(1, 2, 1, 5);
	//buyfood(2, 2, 1, 5);


	//calcanddisplaypopularfood();
	//calcanddisplaypoorstudents();
	readalldrinks();
	//inputbuydrinks();
	//displayalldrinks();
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
		printf("\n\t 5. admin��ѧ����¼");
		printf("\n\t 6. ���õ�ǰ�ͱ�������");
		printf("\n\t 7. ��ǰѧ���Ͳ�ѡ���������");
		printf("\n\t 8. ��ȡ���ܻ�ӭ�Ĳ�Ʒ�����������۶�");
		printf("\n\t 9. ͨ������������鿴ƶ����");
		printf("\n\t a. �鿴��������");
		printf("\n\t b. ��������");
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
		case '5':
			do
			{
				printf("�����������������س�����:");
				scanf("%s", currentuname);
				findstudentbyname(currentuname, &curstu);
			} while (curstu == NULL);
			printf("��ǰѧ��������%s\n", currentuname);
			break;
		case '6':
			printf("\n\n��ѡ���� 6\n");
			do
			{
				printf("�����뵱ǰ�ͱ�(��/��/��һ�������ַ�)���س�����:");
				scanf("%s", currentmeal);
				findstudentbyname(currentuname, &curstu);
			} while (!streq(currentmeal, "��")
				&& !streq(currentmeal, "��")
				&& !streq(currentmeal, "��"));
			printf("��ǰ�ͱ�%s\n", currentmeal);
			break;
		case '7':
			printf("\n\n��ѡ���� 7\n");
			inputbuyfood();
			break;
		case '8':
			printf("\n\n��ѡ���� 8\n");
			calcanddisplaypopularfood();
			break;
		case '9':
			printf("\n\n��ѡ���� 9\n");
			calcanddisplaypoorstudents();
			break;
		case 'a':
			printf("\n\n��ѡ���� a\n");
			displayalldrinks();
			break;
		case 'b':
			printf("\n\n��ѡ���� a\n");
			inputbuydrinks();
			break;
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