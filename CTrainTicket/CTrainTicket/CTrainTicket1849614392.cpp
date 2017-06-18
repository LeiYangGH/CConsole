#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_TRAIN_COUNT 10
#define MAX_CARRIAGE_COUNT 20
#define SEAT_COUNT 45

typedef struct shift
{
	char id[20];
	int hour;
	int minute;
	char start[20];
	char end[20];
	int leftseats;
}shift;

shift allshifts[20];
int allshiftscount = 0;

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}


//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}


void displayshift(shift s)
{
	printf("%s\t%02d:%02d\t%s\t%s\t%d\t%d\n",
		s.id, s.hour, s.minute, s.start, s.end, 45, s.leftseats);
}

void displayallshifts()
{
	int i;
	printf("所有%d位班次信息如下\r\n", allshiftscount);
	printf("班次\t时间\t起点\t终点\t座位\t余票\n"),
		printf("--------------------------------------------\r\n");
	for (i = 0; i < allshiftscount; i++)
	{
		displayshift(allshifts[i]);
	}
	printf("--------------------------------------------\r\n");
}



//qsort是快速排序，要求如下写法，根据age排序
int cmpfunc(const void * a, const void * b)
{
	int ha = ((shift*)a)->hour;
	int ma = ((shift*)a)->minute;
	int hb = ((shift*)b)->hour;
	int mb = ((shift*)b)->minute;
	return (ha - hb) * 60 + ma - mb;
}

void sortshiftsbyageanddisplay()
{
	int i;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("按每个班次年龄排序后如下\r\n");
	displayallshifts();
}

//根据编号查数组里的序号
int getshiftidexbyno(char id[50])
{
	int i;
	for (i = 0; i < allshiftscount; i++)
	{
		if (streq(allshifts[i].id, id))
			return i;
	}
	return -1;//没找到
}


void editshift(char id[50])
{
	int i;
	i = getshiftidexbyno(id);
	if (i >= 0)
	{
		printf("\n请输入新发车时间（24小时制时 分，空格隔开）：");
		scanf("%d%d", &allshifts[i].hour, &allshifts[i].minute);
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应班次的班次。\r\n");
	}
}

void prompteditshift()
{
	char id[50];
	printf("请输入要修改的班次:");
	scanf("%s", &id);
	editshift(id);
}

void addshift(char id[], int hour, int minute)
{
	shift s;
	strcpy(s.id, id);
	s.hour = hour;
	s.minute = minute;
	strcpy(s.start, "保定");
	strcpy(s.end, "北京");
	s.leftseats = SEAT_COUNT;
	allshifts[allshiftscount++] = s;
}


void promptaddshift()
{
	char id[20];
	int hour;
	int minute;
	printf("\n请输入班次（不重复）:\n");
	scanf("%s", id);
	if (getshiftidexbyno(id) >= 0)
	{
		printf("班次与已有班次重复！\n");
		return;
	}
	printf("\n请输入新发车时间（24小时制时 分，空格隔开）：");
	scanf("%d%d", &hour, &minute);
	addshift(id, hour, minute);
	printf("完成第%d位班次录入!\r\n", allshiftscount);
}


void removeshift(char no[20])
{
	int i;
	int index;
	index = getshiftidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allshiftscount - 1; i++)
			allshifts[i] = allshifts[i + 1];
		allshiftscount--;
		printf("删除完毕，剩下%d个。\r\n", allshiftscount);
	}
	else
	{
		printf("没找到对应班次的班次。\r\n");
	}

}

void promptremoveshift()
{
	char id[20];
	printf("请输入要删除的班次:");
	scanf("%s", id);
	removeshift(id);
}


void searcbetweenage(int from, int to)
{
	//int i, found = 0;
	//for (i = 0; i < allshiftscount; i++)
	//	if (allshifts[i].age >= from && allshifts[i].age <= to)
	//	{
	//		displayshift(allshifts[i]);
	//		found = 1;
	//	}
	//if (!found)
	//	printf("没找到对应班次的信息。\r\n");
}

void promptsearchbetweenage()
{
	int from, to;
	printf("请输入要查找的最低和最高年龄(正整数，空格分隔):");
	scanf("%d%d", &from, &to);
	searcbetweenage(from, to);
}

int order[MAX_TRAIN_COUNT][MAX_CARRIAGE_COUNT][SEAT_COUNT];
int traincount = 0;
int carriagecount = 0;
int seatcount = 0;
int initdone = 0;
#define TEST 0

void inputnum(int *num, int max, char *description)
{
	int input = 0;
	do
	{
		printf("\n请输入%s,(范围1~%d):", description, max);
		scanf("%d", &input);
		fseek(stdin, 0, SEEK_END);
	} while (input<1 || input>max);
	*num = input;
}

void init()
{
	int i, j, k;
#if TEST
	traincount = 2;
	carriagecount = 2;
	seatcount = 2;
#else
	if (initdone)
	{
		printf("已经初始化过，不能再初始化\n");
		return;
	}
	inputnum(&traincount, MAX_TRAIN_COUNT, "车次数");
	inputnum(&carriagecount, MAX_CARRIAGE_COUNT, "每车次的车厢数");
	inputnum(&seatcount, SEAT_COUNT, "每车厢的座位数");
	for (i = 0; i < traincount; i++)
		for (j = 0; j < carriagecount; j++)
			for (k = 0; k < seatcount; k++)
				order[i][j][k] = 0;
	initdone = 1;

#endif
}

void showavailableseats(int trainid, int carriageid)
{
	int train, i, j, k;
	printf("第%d车次 第%d车厢剩余座位号如下:\n", trainid + 1, carriageid + 1);
	printf("--------------------------------------------\n");
	for (k = 0; k < seatcount; k++)
	{
		if (order[trainid][carriageid][k] == 0)
		{
			printf("%d\t", k + 1);
		}
	}
	printf("\n--------------------------------------------\n");
}



void showavailable(int trainid)
{
	int j;
	for (j = 0; j < carriagecount; j++)
		showavailableseats(trainid, j);
}

void promptshowavailable()
{
	int i;
	if (!initdone)
	{
		printf("请先初始化再执行其他操作\n");
		return;
	}
	inputnum(&i, carriagecount, "要查询余票的车次");
	showavailable(i - 1);
}

void buy(int trainid, int carriageid, int seatid)
{
	if (order[trainid][carriageid][seatid] == 0)
	{
		order[trainid][carriageid][seatid] = 1;
		printf("售票成功！第%d车次 第%d车厢 第%d号座位。\n", trainid + 1, carriageid + 1, seatid + 1);
	}
	else
		printf("此票已经卖出！");
}

void promptbuy()
{
	int i, j, k;
	if (!initdone)
	{
		printf("请先初始化再执行其他操作\n");
		return;
	}
	inputnum(&i, traincount, "要购买的车次");
	inputnum(&j, carriagecount, "要购买的车厢");
	inputnum(&k, seatcount, "要购买的座位");
	buy(i - 1, j - 1, k - 1);
}



int main()
{
	int choice = -1;
#if 1
	promptaddshift();
	displayallshifts();

	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t 火车订票系统");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 初始化");
		printf("\n\t 2. 查询");
		printf("\n\t 3. 售票");
		//printf("\n\t 4. 退票");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
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
			init();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptshowavailable();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptbuy();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			//promptcancel();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

