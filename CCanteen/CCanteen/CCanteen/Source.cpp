#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEV 1 //调试时候1， 发布时候0
#define CANTEEN_COUNT 5 //5个食堂
#define MEAL_COUNT 3 //早中晚3顿
#define MAX_COUNT 50 //暂定最多20条数据，随便改
#define MAX_STRLEN 20 //字符串最长长度
#define FORMAT_STU "%s\t%s\t%s\r\n" //\r is for write
#define MEMBERS_STU stu.no, stu.name, stu.sex
//#define FORMAT_BUY "%s\t%s\t\%d\n"
//#define MEMBERS_BUY rcd.cdname,rcd.cuname,rcd.days
#define FORMAT_FD "%s\t%s\t%.1f\r\n"
#define MEMBERS_FD fd.name, fd.taste, fd.price
#define LINE  "\n------------------------\n"
#define FILE_STU "stu.txt"
#define FILE_FD "fd.txt"
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
typedef struct buydetail
{
	int stuid;
	int fdid;
	// 可以加食堂、日期、餐别等，但由于需求没提到需要处理相关数据，所以没加
}buydetail;
//所有数据都存储在下面这3个结构体数组里面
student allstudents[MAX_COUNT];
int allstudentscount = 0;

buydetail allrentcds[MAX_COUNT];
int allrentcdscount = 0;

food allfoods[MAX_COUNT];
int allfoodscount = 0;

//每天各个食堂的菜肴(下标)
//3个下标依次代表食堂、早中晚、菜肴编号，都从0开始
int sellfoods[CANTEEN_COUNT][MEAL_COUNT][MAX_COUNT] = { 0 };
//各个食堂各顿的菜肴种类数量
int sellfoodscount[CANTEEN_COUNT][MEAL_COUNT] = { 0 };

char *meals[] = { "早","中","晚" };
char currentmeal[MAX_STRLEN] = "中";//当前默认为中午

//当前用户
char currentuname[MAX_STRLEN] = "";
int currentstuid = -1;

buydetail allbuydetails[200];//由于可以不断增加的，限制放开一些
int allbuydetailscount = 0;

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
//void displayrentcd(buydetail rcd)
//{
//	printf(FORMAT_RCD, MEMBERS_RCD);
//}
//
//void displayallrentcds()
//{
//	int i;
//	printf("所有学生租借情况如下\n");
//	printf("学生\t菜肴\t天数\n");
//	printf(LINE);
//	for (i = 0; i < allrentcdscount; i++)
//	{
//		if (allrentcds[i].isreturned == 0)
//			displayrentcd(allrentcds[i]);
//	}
//}


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
	fprintf(fp, FORMAT_STU, "10", "admin", "F");//管理员帐号，不能删
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
	fclose(fp);
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
	fclose(fp);
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
			currentstuid = i;
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
		printf("\n打开文件%s失败!\n", FILE_SELL_ID);
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
	printf("\n已读入菜肴销售文件!");
}
/////////////sell end//////////////

/////////////select start//////////////

int iscurrentuserstudent()
{
	return (streq(currentuname, "") || streq(currentuname, "admin")) ? 0 : 1;
}

//打招呼，也是为了提醒用户注意选择菜单修改餐别
int getcurrentmeal()
{
	int j;
	char msg[MAX_STRLEN] = "";
	if (streq(currentmeal, "早"))
	{
		j = 0;
		strcpy(msg, "早上好！");
	}
	else if (streq(currentmeal, "中"))
	{
		j = 1;
		strcpy(msg, "中午好！");
	}
	else
	{
		j = 2;
		strcpy(msg, "晚上好！");
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
	printf("菜单如下：\n");
	printf(LINE);
	printf("序号\t菜名\t风味\t价格\n");
	for (k = 0; k < sellfoodscount[i][j]; k++)
	{
		fdid = sellfoods[i][j][k];
		fd = allfoods[fdid];
		printf("%d\t%s\t%s\t%.1f\n", fdid, fd.name, fd.taste, fd.price);
	}
	printf(LINE);
	while (!isidinlist(i, j, choice))
	{
		printf("请选择您要点的菜前面的序号，回车结束：");
		scanf("%d", &choice);
	}
	return choice;
}

void appendonebuyfood(FILE *fp, FILE *fpid, int stuid, int i, int j, int fdid)
{
	char cat[MAX_STRLEN] = "";
	food fd = allfoods[fdid];
	fprintf(fp, "%s\t食堂%d\t%s\t%s\t%s\t%.1f\r\n%", allstudents[stuid].name, i + 1, meals[j],
		fd.name, fd.taste, fd.price);
	//分别为学生id和fdid
	fprintf(fpid, "%d\t%d\r\n%", currentstuid, fdid);
}

//假定都在有效范围内
//应该还有日期参数？但目前没做
void buyfood(int stuid, int i, int j, int fdid)
{
	food fd;
	FILE *fp, *fpid;
	fp = fopen(FILE_BUY, "a");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_BUY);
		return;
	}
	fpid = fopen(FILE_BUY_ID, "a");
	if (fpid == NULL)
	{
		printf("\n打开文件%s失败!", FILE_BUY_ID);
		return;
	}
	appendonebuyfood(fp, fpid, stuid, i, j, fdid);
	fclose(fp);
	fclose(fpid);
	printf("\n消费已经追加文件。");
}


void inputbuyfood()
{
	int i, j, id;
	food fd;
	if (iscurrentuserstudent())
	{
		j = getcurrentmeal();
		printf("请输入您想在哪个食堂就餐（数字1～5），回车结束:");
		scanf("%d", &i);
		printf("您选择了食堂%d\n", i);
		id = selectfoodfromlist(i - 1, j);
		fd = allfoods[id];
		printf("您点的菜是%d\t%s\t%s\t%.1f\n", id, fd.name, fd.taste, fd.price);
		buyfood(currentstuid, i, j, id);
	}
	else
	{
		printf("\n只有以学生姓名登录才能用餐消费！");
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
		printf("\n打开文件%s失败!\n", FILE_BUY_ID);
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
	printf("\n已读入文件!", FILE_STU);
}

void calcanddisplaypopularfood()
{
	int i, fdid, max = 0, maxid = -1;
	float sum = 0;
	int buyfreq[MAX_COUNT] = { 0 };//每种菜肴被消费的次数
	readallbuydetails();
	for (i = 0; i < allbuydetailscount; i++)
	{
		fdid = allbuydetails[i].fdid;
		sum += allfoods[fdid].price;//没做份数的功能，直接加价钱
		if (max < ++buyfreq[fdid])
		{
			max = buyfreq[fdid];
			maxid = fdid;
		}
	}
	printf("\n最受欢迎的菜品是%s，销量是%d!\n", allfoods[fdid].name, max);
	printf("\n所有销量总量是%.1f元!\n", sum);
}

/////////////statics end//////////////

int main()
{
	int choice = -1;
	student *curstu = NULL;
	//下面这些是测试时方便测试的，可以删除
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


	calcanddisplaypopularfood();
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
		printf("\n\t 5. admin或学生登录");
		printf("\n\t 6. 设置当前餐别（早中晚）");
		printf("\n\t 7. 当前学生就餐选择菜肴消费");
		printf("\n\t 8. 抽取最受欢迎的菜品");
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
		case '5':
			do
			{
				printf("请输入您的姓名，回车结束:");
				scanf("%s", currentuname);
				findstudentbyname(currentuname, &curstu);
			} while (curstu == NULL);
			printf("当前学生姓名：%s\n", currentuname);
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			do
			{
				printf("请输入当前餐别(早/中/晚，一个中文字符)，回车结束:");
				scanf("%s", currentmeal);
				findstudentbyname(currentuname, &curstu);
			} while (!streq(currentmeal, "早")
				&& !streq(currentmeal, "中")
				&& !streq(currentmeal, "晚"));
			printf("当前餐别：%s\n", currentmeal);
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			inputbuyfood();
			break;
		case '8':
			printf("\n\n你选择了 8\n");
			calcanddisplaypopularfood();
			break;
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