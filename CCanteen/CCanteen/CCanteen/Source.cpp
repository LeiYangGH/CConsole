#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 0 //调试时候1， 发布时候0
#define CANTEEN_COUNT 5 //5个食堂
#define MEAL_COUNT 3 //早中晚3顿
#define MAX_COUNT 20 //暂定最多20条数据，随便改
#define MAX_STRLEN 20 //字符串最长长度
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
//所有数据都存储在下面这3个结构体数组里面
student allstudents[MAX_COUNT];
int allstudentscount = 0;

rentcd allrentcds[MAX_COUNT];
int allrentcdscount = 0;

food allfoods[MAX_COUNT];
int allfoodscount = 0;

//每天各个食堂的菜肴(下标)
//3个下标依次代表食堂、早中晚、菜肴编号，都从0开始
int sellfoods[CANTEEN_COUNT][MEAL_COUNT][MAX_COUNT] = { 0 };
//各个食堂各顿的菜肴种类数量
int sellfoodscount[CANTEEN_COUNT][MEAL_COUNT] = { 0 };

//char meals[] = { '早','中', '晚' };
char *meals[] = { "早","中","晚" };
//字符串转整数
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

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displaystudent(student stu)
{
	printf(FORMAT_STU, MEMBERS_STU);
}
//display all显示全部，调用displaystudent显示单行，下同
void displayallstudents()
{
	int i;
	printf("所有学生情况如下\n");
	printf("编号\t名称\n");
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
	printf("所有学生租借情况如下\n");
	printf("学生\t菜肴\t天数\n");
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
	printf("创建示例成绩数据...");
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
	printf("5条示例成绩数据已保存到student.txt。\n");
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!\n", FILE_STU);
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
	printf("\n已读入文件!", FILE_STU);

}

void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_STU, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_STU);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, FORMAT_STU, MEMBERS_STU);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

//添加单个
void addstudent(char * no, char *name, char *sex)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	strcpy(stu.sex, sex);
	allstudents[allstudentscount++] = stu;
	writeallstudents();
}

//要求用户输入，输入后调用addstudent，下同，分开两个函数是为了测试方便
void inputstudents()
{
	//int i, score;
	char no[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char sex[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n请输入学生编号(整数，q结束):");
		scanf("%s", no);
		if (streq(no, "q"))
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入学生名称、性别，逗号分隔，回车结束:");
		scanf("%s%s", name, sex);
		addstudent(no, name, sex);
		printf("\nCD%s信息添加成功!\n", name);
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
	printf("所有菜肴如下\n");
	printf("菜名\t风味\t价格\n");
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
		printf("\n打开文件%s失败!", FILE_FD);
		getchar();
		exit(1);
	}


	for (i = 0; i < allfoodscount; i++)
	{
		fd = allfoods[i];
		fprintf(fp, FORMAT_FD, MEMBERS_FD);
	}
	fclose(fp);
	printf("已保存菜肴到文件。");
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
		printf("\n\n请输入菜肴名称(q结束):");
		scanf("%s", name);
		if (streq(name, "q"))
		{
			printf("\n您已结束输入！");
			break;
		}
		printf("\n请输入菜肴姓名、价格，中间空格分隔，回车结束:");
		scanf("%s%s", taste, pstr);
		price = atof(pstr);
		addfood(name, taste, price);
		printf("\n菜肴%s信息添加成功!\n", name);
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
	printf("创建示例成绩数据...");
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
	printf("5条示例成绩数据已保存到food.txt。\n");
}

void readallfoods()
{
	char line[200];
	FILE *fp = fopen(FILE_FD, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!\n", FILE_FD);
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
	printf("\n已读入文件!", FILE_FD);

}


//////////////////////food end///////////////
//通过名称查找stu，传进来的是student的指针，下同
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
		printf("没找到名称为%s的学生\n", cdname);
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
		printf("没找到姓名为%s的菜肴\n", cuname);
		*fd = NULL;
	}
}

//假设一定能找到
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
			//每个食堂每顿的菜肴种类，最少2，最多为全部菜肴的一半
			//具体数量随机
			//目前价格是同一的，理论上更好的做法是让各个食堂价格在标准价格上下浮动
			fdcnt = random(2, allfoodscount / 2);
			generaterandomfoodids(ids, fdcnt);
			for (k = 0; k < fdcnt; k++)
			{
				sellfoods[i][j][k] = ids[k];
			}
			sellfoodscount[i][j] = fdcnt;
		}
	}
	printf("已生成每日菜单。");
}
//参数分别为食堂、早中晚、菜肴编号（0开始）
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
	fprintf(fp, "食堂%d\t%s\t%s\t%s\t%.1f\r\n%", i + 1, meals[j],
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
		printf("\n打开文件%s失败!", FILE_SELL);
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
	printf("已保存每日菜单到文件。");
}
/////////////sell end//////////////


int main()
{
	int choice = -1;
	char *s = "2";
	int f = atoi(s);
	//下面这些是测试时方便测试的，可以删除
	//createsamplestudents();
	readallstudents();
	displayallstudents();

	readallfoods();
	displayallfoods();

	generatesellfoodsforonecateenonemeal();
	writeallsellfoods();
#if DEV
	//下面这些是测试时方便测试的，可以删除

#else
	while (choice != 0)
	{
		printf("\n\t 学生选课");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 增加学生信息");
		printf("\n\t 2. 查看所有学生");
		printf("\n\t 3. 增加菜肴信息");
		printf("\n\t 4. 查看所有菜肴");
		//printf("\n\t 5. 出租学生");
		//printf("\n\t 6. 查看所有学生出租情况");
		//printf("\n\t 7. 查看某位菜肴学生出租情况");
		//printf("\n\t 8. 归还学生");
		printf("\n\n  请选择: ");
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			inputstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallstudents();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			inputfoods();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			displayallfoods();
			break;
			//case '5':
			//	printf("\n\n你选择了 5\n");
			//	inputrent();
			//	break;
			//case '6':
			//	printf("\n\n你选择了 6\n");
			//	displayallrentcds();
			//break;
			//case '7':
			//	printf("\n\n你选择了 7\n");
			//	inputanddisplayonefoodrentcds();
			//	break;
			//case '8':
			//	printf("\n\n你选择了 8\n");
			//	inputreturn();
			//	break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		fseek(stdin, 0, SEEK_END);
	}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}