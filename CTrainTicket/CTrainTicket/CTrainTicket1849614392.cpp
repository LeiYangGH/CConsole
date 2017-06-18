#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_TRAIN_COUNT 10
#define MAX_CARRIAGE_COUNT 20
#define MAX_SEAT_COUNT 130

int order[MAX_TRAIN_COUNT][MAX_CARRIAGE_COUNT][MAX_SEAT_COUNT];
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
	inputnum(&seatcount, MAX_SEAT_COUNT, "每车厢的座位数");
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


void cancel(int trainid, int carriageid, int seatid)
{
	if (order[trainid][carriageid][seatid] == 1)
	{
		order[trainid][carriageid][seatid] = 0;
		printf("退票成功！");
	}
	else
		printf("此票未卖出，不能退票！");
}

void promptcancel()
{
	int i, j, k;
	if (!initdone)
	{
		printf("请先初始化再执行其他操作\n");
		return;
	}
	inputnum(&i, traincount, "要退票的车次");
	inputnum(&j, carriagecount, "要退票的车厢");
	inputnum(&k, seatcount, "要退票的座位");
	cancel(i - 1, j - 1, k - 1);
}

int main()
{
	int choice = -1;
#if TEST
	init();
	//showavailable(0);
	//showavailable(1);
	buy(0, 0, 1);
	//buy(0, 0, 1);
	//showavailable(0);
	//buy(0, 1, 1);
	showavailable(0);
	cancel(0, 0, 1);
	showavailable(0);

	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t 火车订票系统");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 初始化");
		printf("\n\t 2. 查询");
		printf("\n\t 3. 售票");
		printf("\n\t 4. 退票");
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
			promptcancel();
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

