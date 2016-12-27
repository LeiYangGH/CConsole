#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define DEV 1
typedef struct flightnode
{
	char flight_num[10];//航班号
	char start_time[15];//起飞时间
	char end_time[15];//抵达时间
	char start_place[20];//起飞城市
	char end_place[20];//降落城市
	int left;//空座数
	float price;//票价
	int ifull;//航班是否满仓
	struct flightnode *next;//指向下一节点
}flightnode;

typedef struct passengernode
{
	char name[20];//姓名
	char ID_num[20];//证件号
	char flight_num[10];//航班号
	int order_num;//订单号
	int ticket_num;//订票数量
	struct passengernode *next;//指向下一节点
}passengernode;

typedef struct passengerList
{
	passengernode *head;
	passengernode *rear;
}passengerList;

typedef struct waitnode
{
	char name[20];//姓名
	char phone[20];//手机号
	char flight_num[10];//航班号
	int ticket_num;//订票数量
	int order_num;//预约排队号
	struct waitnode *next;//指向下一节点

}waitnode;

typedef struct waitList
{
	waitnode *head;
	waitnode *rear;
}waitList;



//建立以h为头结点的空链表，录入航班信息和增加航班后将航班结点插入该链表
void init_flight(flightnode *&h)
{
	h = (flightnode *)malloc(sizeof(flightnode));//申请头结点空间
	if (h == NULL)
		exit(0);
	h->next = NULL;//将头结点h的指针域置为空
}
//建立一个带有头尾指针的空链表，存储带有客户信息的节点
void init_passengerList(passengerList *&pList)
{
	pList = (passengerList *)malloc(sizeof(passengerList));
	pList->head = (passengernode *)malloc(sizeof(passengernode));//创建头结点
	pList->rear = pList->head;
	pList->rear->order_num = 0;//订单号从0开始计数
	pList->head->next = NULL;
}
//建立一个带有头尾指针的空队，存储带有预约客户信息的节点
void init_waitList(waitList *&wList)
{
	wList = (waitList *)malloc(sizeof(waitList));
	wList->head = (waitnode *)malloc(sizeof(waitnode));//创建头结点
	wList->rear = wList->head;
	wList->rear->order_num = 0;//预约排队号从0开始计数
	wList->head->next = NULL;
}

//保存航班信息到指定的数据文件中
void save_flight(flightnode *h)
{
	FILE *fp = fopen("flightList.dat", "wb");//以只写('wb')的方式打开名为'flightList.dat'的文件
	if (fp == NULL)
		return;
	flightnode *temp = h->next;
	while (temp != NULL)
	{
		fwrite(temp, sizeof(flightnode), 1, fp);//向其中写入temp（temp是指针）地址的l个flightnode类型的数据
		temp = temp->next;
	}
	fclose(fp);//关闭fp指向的文件
}
//从存储航班信息的文件导入航班信息到航班链表中
void load_flight(flightnode *&h)
{
	flightnode *pt = h;
	FILE *fp = fopen("flight.dat", "rb");
	if (fp == NULL)
		return;
	flightnode *q;
	int n;
	while (!feof(fp))//文件指针没有到达文件末尾（最后一个字符的下一个位置，即读失败时的位置）
	{
		q = (flightnode *)malloc(sizeof(flightnode));
		n = fread(q, sizeof(flightnode), 1, fp);//将写入的数据读取出来
		if (n != 1)
			break;
		pt->next = q;
		pt = q;
	}
	pt->next = NULL;
	fclose(fp);
}

//保存已订票客户信息到指定数据文件中
void save_passenger(passengerList *PList)
{
	FILE *fp = fopen("passenger.dat", "wb");
	if (fp == NULL)
		return;
	passengernode *temp = PList->head->next;
	while (temp != NULL)
	{
		fwrite(temp, sizeof(passengernode), 1, fp);//向其中写入temp（temp是指针）地址的l个passengernode类型的数据
		temp = temp->next;
	}
	fclose(fp);//关闭fp指向的文件
}
//从存储客户信息的文件导入客户信息到客户链表中
void load_passenger(passengerList *&PList)
{
	FILE *fp = fopen("passenger.dat", "rb");
	if (fp == NULL)
		return;
	passengernode *q;
	int n;
	while (!feof(fp))//文件指针没有到达文件末尾（最后一个字符的下一个位置，即读失败时的位置）
	{
		q = (passengernode *)malloc(sizeof(passengernode));
		n = fread(q, sizeof(passengernode), 1, fp);//将写入的数据读取出来
		if (n != 1)
			break;
		PList->rear->next = q;
		PList->rear = q;
	}
	PList->rear->next = NULL;
	fclose(fp);
}

//保存预约客户信息到指定数据文件中
void save_wait(waitList *WList)
{
	FILE *fp = fopen("waitpassenger.dat", "wb");
	if (fp == NULL)
		return;
	waitnode *temp = WList->head->next;
	while (temp != NULL)
	{
		fwrite(temp, sizeof(waitnode), 1, fp);//向其中写入temp（temp是指针）地址的l个waitnode类型的数据
		temp = temp->next;
	}
	fclose(fp);//关闭fp指向的文件
}
//从存储预约客户信息的文件导入预约客户信息到预约客户链表中
void load_wait(waitList *&WList)
{
	FILE *fp = fopen("waitpassenger.dat", "rb");
	if (fp == NULL)
		return;
	waitnode *w;
	int n;
	while (!feof(fp))//文件指针没有到达文件末尾（最后一个字符的下一个位置，即读失败时的位置）
	{
		w = (waitnode *)malloc(sizeof(waitnode));
		n = fread(w, sizeof(waitnode), 1, fp);//将写入的数据读取出来
		if (n != 1)
			break;
		WList->rear->next = w;
		WList->rear = w;
	}
	WList->rear->next = NULL;
	fclose(fp);
}

//录入航班情况或增加新的航班后，将新的航班结点插入到航线链表中
void insert_flight(flightnode *&h, char *flight_num, char *start_place, char *end_place, char *start_time, char *end_time, int left, float price, int ifull)
{
	flightnode *q;//定义q为新增加的航班节点的指针的形参
	flightnode *p = h;
	q = (flightnode *)malloc(sizeof(flightnode));//为节点q申请空间
	strcpy(q->flight_num, flight_num);
	strcpy(q->start_place, start_place);
	strcpy(q->end_place, end_place);
	strcpy(q->start_time, start_time);
	strcpy(q->end_time, end_time);
	q->left = left;
	q->price = price;
	q->ifull = ifull;
	//用strcpy函数将新增加航班的各种信息复制到q节点中
	q->next = p->next;//将q节点的指针域置为空
	p->next = q;
	p = p->next;//将指针后移
}

//录入航班信息后调用insert_flight函数增加航班
void add_flight(flightnode *&h)
{
	flightnode *p = h;
	char flight_num[10], start_time[10], end_time[10], start_place[10], end_place[10];
	int left, ifull, mark = 1;
	float price;
	for (; p->next != NULL; p = p->next)
	{
	}//移动指针，找到最后一个节点
	while (mark == 1)
	{
#if DEV
		strcpy(flight_num, "a");
		insert_flight(h, flight_num, "f", "t", "y", "t", 0, 1, 1);
#else
		printf("\t\t请输入你要增加的航班号：");
		scanf("%s", flight_num);
		printf("\t\t请输入出发地：");
		scanf("%s", start_place);
		printf("\t\t请输入目的地：");
		scanf("%s", end_place);
		printf("\t\t请输入起飞时间：");
		scanf("%s", start_time);
		printf("\t\t请输入抵达时间：");
		scanf("%s", end_time);
		printf("\t\t请输入票价：");
		scanf("%f", &price);
		printf("\t\t请输入剩余座位数：");
		scanf("%d", &left);
		printf("\t\t请输入是否满仓（0表示没有满仓，1表示已满仓）：");
		scanf("%d", &ifull);
		insert_flight(h, flight_num, start_place, end_place, start_time, end_time, left, price, ifull);
#endif
		printf("\t\t增加航班号%s成功！\n", flight_num);
		printf("\t\t是否继续录入航班信息（1表示继续录入，0表示停止录入）\n");
		printf("\t\t请输入：");
		scanf("%d", &mark);
	}
}

//按照起飞抵达城市查询航班信息
int place_check(flightnode *h, char *start_place, char *end_place)
{
	flightnode *p = h;
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "航班号", "起飞城市", "抵达城市", "起飞时间", "抵达时间", "价格", "是否满仓", "空座数");
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->start_place, start_place) == 0 && strcmp(p->end_place, end_place) == 0)
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
			mark = 1;
		}
	}
	if (mark == 0)
	{
		printf("\t\t抱歉，没有从%s到%s的航班信息！\n", start_place, end_place);
		return 0;
	}
	return 1;
}

//在顾客订票后，将该顾客结点插入到顾客链表，并修改相应航班信息
void insert_passengerList(flightnode *&h, passengerList *&PList, char *name, char *ID_num, char *flight_num, int ticket_num)
{
	flightnode *p = h->next;
	for (; p != NULL; p = p->next)
		if (strcmp(p->flight_num, flight_num) == 0)
		{
			p->left = p->left - ticket_num;
			if (p->left == 0)
				p->ifull = 1;
		}
	passengernode *q = (passengernode *)malloc(sizeof(passengernode));//新建结点，存放新的客户订单信息
	strcpy(q->name, name);
	strcpy(q->ID_num, ID_num);
	strcpy(q->flight_num, flight_num);
	q->ticket_num = ticket_num;
	q->next = NULL;
	//将新订单连接到链表中
	PList->rear->next = q;
	q->order_num = PList->rear->order_num + 1;//生成订单号
	PList->rear = q;
}

//在客户预约票后，将该预约客户结点插入到预约客户队列
void insert_waitList(waitList *&WList, char *name, char *phone, char *flight_num, int ticket_num, int order_num)
{
	waitnode *p = (waitnode *)malloc(sizeof(waitnode));
	strcpy(p->name, name);
	strcpy(p->phone, phone);
	strcpy(p->flight_num, flight_num);
	p->ticket_num = ticket_num;
	p->next = NULL;
	if (WList->rear == NULL)
	{
		WList->head = WList->rear = p;
	}
	else
	{
		WList->rear->next = p;
		p->order_num = WList->rear->order_num + 1;//生成预约排队号
		WList->rear = p;
	}
}
//完成客户订票，将客户结点插入客户链表，并修改相应的航班信息
int book(flightnode *&h, passengerList *&PList, waitList *WList)
{
	char name[20];
	char ID_num[20];
	char flight_num[10];
	char start_place[20];
	char end_place[20];
	char phone[20];
	int ticket_num;
	int order_num;
	int k;
	flightnode *p = h->next;
#if DEV
	strcpy(start_place, "f");
	strcpy(end_place, "t");
#else
	printf("\t\t请输入信息：\n");
	printf("\t\t请输入起飞城市：");
	scanf("%s", start_place);
	printf("\t\t请输入抵达城市：");
	scanf("%s", end_place);
#endif


	if (place_check(h, start_place, end_place) == 1)
	{
		printf("\t\t航班号：");
		scanf("%s", flight_num);
		while (flight_num == NULL)
		{
#if DEV
			strcpy(flight_num, "a");
#else
			printf("航班号不能为空！\n");
			printf("\t\t航班号：");
			scanf("%s", flight_num);
#endif

		}
		while (p != NULL)
		{
			if (strcmp(p->flight_num, flight_num) == 0)
			{

#if DEV
				strcpy(name, "ly");
				strcpy(ID_num, "510");
				ticket_num = 1;
#else
				printf("\t\t姓名：");
				scanf("%s", name);
				printf("\t\t证件号码：");
				scanf("%s", ID_num);
				printf("\t\t订票数量：");
				scanf("%d", &ticket_num);
#endif

				while (name == NULL)
				{
					printf("客户姓名不能为空！\n");
					printf("\t\t姓名：");
					scanf("%s", name);
				}
				while (ID_num == NULL)
				{
					printf("客户证件号码不能为空！\n");
					printf("\t\t证件号码：");
					scanf("%s", ID_num);
				}
				while (ticket_num == 0)
				{
					printf("客户订票数量不能为空！\n");
					printf("\t\t订票数量：");
					scanf("%d", &ticket_num);
				}
				if (p->left > 0 && p->left >= ticket_num)
				{
					insert_passengerList(h, PList, name, ID_num, flight_num, ticket_num);
					printf("\t\t你应付金额￥%8.2f。\n", p->price*ticket_num);
					getch();
					printf("\t\t恭喜您，订票成功！\n");
					return 1;
				}
				else
				{
					printf("\t\t***很遗憾，该航班已满！***\n");
					printf("\t\t***如选择其他航班请输入——1\n\t\t***预约请输入——2\n\t\t***不选则输入——0***\n");
					printf("\t\t输入数字进行选择：");
					scanf("%d", &k);
					if (k == 1)
					{
						printf("\t\t请输入您选的航班：");
						scanf("%s", flight_num);
						insert_passengerList(h, PList, name, ID_num, flight_num, ticket_num);
						printf("\t\t恭喜您，订票成功！\n");
						return 1;
					}
					else if (k == 2)
					{
#if DEV
						insert_waitList(WList, "ly", "151", "a", 1, 0);

#else
						printf("\t\t请输入您的姓名：");
						scanf("%s", name);
						printf("\t\t请输入您的手机号：");
						scanf("%s", phone);
						printf("\t\t请输入您需要预约的航班号：");
						scanf("%s", &flight_num);
						printf("\t\t请输入您需要的机票数量：");
						scanf("%d", &ticket_num);

						//insert_waitList(WList, name, phone, flight_num, ticket_num, order_num);
						insert_waitList(WList, name, phone, flight_num, ticket_num, 0);
#endif

						printf("\t\t如有退票，会尽快联系您！\n");
						return 2;
					}
				}
			}
			else
				p = p->next;
		}
		if (p == NULL)
			printf("\t\t对不起，您输入的航班不存在！\n");
	}
	return 0;
}




//客户订票时输入的航班号对应航班已满，提供其他可选航班并输出显示
int find_same_flight(flightnode *h, char *flight_num)
{
	flightnode *t = h->next, *p = h->next;
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "航班号", "起飞城市", "抵达城市", "起飞时间", "抵达时间", "价格", "是否满仓", "空座数");
	while (p != NULL)
	{
		if ((strcmp(t->start_place, p->start_place) == 0) && (strcmp(t->end_place, p->end_place) == 0) && (strcmp(t->flight_num, p->flight_num) != 0))
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
			mark = 1;
		}
		p = p->next;
	}
	if (mark = 0)
	{
		printf("\t\t抱歉，无可选航班！\n");
		return 0;
	}
	return 1;
}




//按照要退票的客户姓名和证件号查找该客户结点，进行删除操作
int delete_passenger(passengerList *&PList, flightnode *&h, char *name, char *ID_num)
{
	passengernode *p, *pr = PList->head;//pr指向客户链表的头结点
	p = pr->next;
	while (p != NULL)
	{
		if (strcmp(name, p->name) == 0 && strcmp(ID_num, p->ID_num) == 0)
		{
			for (flightnode *f = h->next; f != NULL; f = f->next)
			{
				if (strcmp(p->flight_num, f->flight_num) == 0)
				{
					f->left = f->left + p->ticket_num;
					f->ifull = 0;
					break;
				}
			}
			pr->next = p->next;
			free(p);
			printf("\t\t客户%s,%s退票成功！\n", name, ID_num);
			return 1;
		}
		pr = pr->next;
		p = pr->next;
	}
	printf("\t\t无此客户，无法退票！\n");
	return 0;
}
//完成退票，将订单从客户链表删除并修改相应航班信息
void cancel(passengerList *&PList, flightnode *&h)
{
	char name[20], ID_num[20];
	printf("\t\t请输入你的姓名：");
	scanf("%s", name);
	printf("\t\t请输入你的证件号：");
	scanf("%s", ID_num);
	delete_passenger(PList, h, name, ID_num);
}

//按照航班号查询航班信息
int flight_num_check(flightnode *h, char *flight_num)
{
	flightnode *p = h;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "航班号", "起飞城市", "抵达城市", "起飞时间", "抵达时间", "价格", "是否满仓", "空座数");
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->flight_num, flight_num) == 0)
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
			return 1;
		}
	}
	printf("\t\t抱歉，没有航班号为%s的航班信息！\n", flight_num);
	return 0;
}

//浏览所有航班信息
void check_all_flight(flightnode *h)
{
	flightnode *p = h;
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "航班号", "起飞城市", "抵达城市", "起飞时间", "抵达时间", "价格", "是否满仓", "空座数");
	for (; p != NULL; p = p->next)
	{
		printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
		mark = 1;
	}
	if (mark == 0)
		printf("\t\t航班信息为空！\n");
}

//选择使用何种方式对航班信息进行查询
void flight_check(flightnode *h)
{
	flightnode *p = h->next;
	char flight_num[10], start_place[20], end_place[20];
	char a;
	printf("\t\t请选择航班查询方式：\n");
	printf("\t\t1、按航班号进行查询：\n");
	printf("\t\t2、按起飞抵达城市进行查询：\n");
	printf("\t\t3、浏览全部航班信息.\n\t\t请输入：\n");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
	{
		printf("\t\t请输入航班号：");
		scanf("%s", flight_num);
		flight_num_check(p, flight_num);
	}
	else if (a == '2')
	{
		printf("\t\t请输入起飞城市：");
		scanf("%s", start_place);
		printf("\t\t请输入抵达城市：");
		scanf("%s", end_place);
		place_check(p, start_place, end_place);
	}
	else if (a == '3')
		check_all_flight(p);
	else
		return;
}




//按客户姓名和证件号查询订单信息
int ID_name_check(passengerList *PList, char *name, char *ID_num)
{
	passengernode *p = PList->head->next;
	int mark = 0;
	printf("%-8s%-20s%-20s%-10s%-8s%\n", "订单号", "姓名", "证件号", "航班号", "订票数量");
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->ID_num, ID_num) == 0 && strcmp(p->name, name) == 0)
		{
			printf("%-8d%-20s%-20s%-10s%-8d%\n", p->order_num, p->name, p->ID_num, p->flight_num, p->ticket_num);
			mark = 1;
		}
	}
	if (mark == 0)
	{
		printf("\t\t抱歉，没有%s，%s的订单信息！\n", name, ID_num);
		return 0;
	}
	return 1;
}
//按订单号查询订单信息
int order_num_check(passengerList *PList, int order_num)
{
	passengernode *p = PList->head->next;
	printf("%-8s%-20s%-20s%-10s%-8s%\n", "订单号", "姓名", "证件号", "航班号", "订票数量");
	for (; p != NULL; p = p->next)
	{
		if (p->order_num == order_num)
		{
			printf("%-8d%-20s%-20s%-10s%-8d%\n", p->order_num, p->name, p->ID_num, p->flight_num, p->ticket_num);
			return 1;
		}
	}
	printf("\t\t抱歉，没有订单号为%d的订单信息！\n", order_num);
	return 0;
}


//浏览所有订单信息
void check_all_passenger(passengerList *PList)
{
	passengernode *p = PList->head->next;
	int m = 0;
	printf("%-8s%-20s%-20s%-10s%-8s%\n", "订单号", "姓名", "证件号", "航班号", "订票数量");
	for (; p != NULL; p = p->next)
	{
		printf("%-8d%-20s%-20s%-10s%-8d%\n", p->order_num, p->name, p->ID_num, p->flight_num, p->ticket_num);
		m = 1;
	}
	if (m == 0)
		printf("\t\t订单信息为空！\n");
}

//选择使用何种方式查询订单信息
void passenger_check(passengerList *PList)
{
	char name[20], ID_num[15];
	int order_num = 0;
	char a;
	printf("\t\t请选择订单查询方式：\n");
	printf("\t\t1、按客户姓名和证件号进行查询\n");
	printf("\t\t2、按订单号进行查询\n");
	printf("\t\t3、查看全部订单信息\n\t\t请选择输入：");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
	{
		printf("\t\t请输入客户姓名：");
		scanf("%s", name);
		printf("\t\t请输入证件号：");
		scanf("%s", ID_num);
		ID_name_check(PList, name, ID_num);
	}
	else if (a == '2')
	{
		printf("\t\t请输入订单号：");
		scanf("%d", order_num);
		order_num_check(PList, order_num);
	}
	else
		check_all_passenger(PList);
}


//按预约航班号查询预约客户信息
int wait_flightnum_check(waitList *WList, char *flight_num)
{
	waitnode *p = WList->head->next;
	printf("%-20s%-20s%-10s%-8s%\n", "姓名", "手机号", "航班号", "订票数量");
	for (; p != NULL; p = p->next)
	{
		if (p->flight_num == flight_num)
		{
			printf("%-20s%-20s%-10s%-8d%\n", p->name, p->phone, p->flight_num, p->ticket_num);
			return 1;
		}
	}
	printf("\t\t抱歉，没有预约此航班号的信息！\n");
	return 0;
}

//浏览所有预约客户信息
void check_all_wait(waitList *WList)
{
	waitnode *a = WList->head->next;
	int m = 0;
	printf("%-20s%-20s%-10s%-8s%\n", "姓名", "手机号", "航班号", "订票数量", "预约排队号");
	for (; a != NULL; a = a->next)
	{
		printf("%-20s%-20s%-10s%-8d%\n", a->name, a->phone, a->flight_num, a->ticket_num, a->order_num);
		m = 1;
	}
	if (m == 0)
		printf("\t\t预约客户信息为空！\n");
}

//选择使用何种方式查询预约客户信息
void wait_check(waitList *WList)
{
	char flight_num[10];
	char a;
	printf("\t\t请选择预约客户信息查询方式：\n");
	printf("\t\t1、按预约航班号进行查询\n");
	printf("\t\t2、查看全部预约客户信息\n\t\t请选择输入：");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
	{
		printf("\t\t请输入预约航班号：");
		scanf("%c", &flight_num);
		wait_flightnum_check(WList, flight_num);
	}
	else if (a == '2')
	{
		check_all_wait(WList);
	}
}



//修改航班时间
void modify_flight_time(flightnode *&h, passengerList *&PList)
{
	flightnode *p = h->next;
	char flight_num[10], start_time[10], end_time[10];
	printf("\t\t请输入要修改航班的航班号：");
	scanf("%s", flight_num);
	if (flight_num_check(p, flight_num) == 1)
	{
		printf("\t\t请输入修改后的起飞时间：");
		scanf("%s", start_time);
		printf("\t\t请输入修改后的抵达时间：");
		scanf("%s", end_time);
		for (; p != NULL; p = p->next)
		{
			if (strcmp(flight_num, p->flight_num) == 0)
			{
				strcpy(p->start_time, start_time);
				strcpy(p->end_time, end_time);
				printf("\t\t航班%s时间修改成功！\n", flight_num);
			}
		}
	}
}

//按照某个航班号删除航班结点
void delete_flight(flightnode *&h, passengerList *&PList)
{
	flightnode *p, *pr;
	passengernode *q, *qr;
	char flight_num[10];
	int mark = 1;
	qr = PList->head;//pr为客户链表的头结点
	q = qr->next;//用p作为中间指针对客户链表中要删除的客户节点进行查找
	pr = h;//pr为航线链表的头结点
	p = pr->next;//用p作为指针对航班链表中要删除的航班节点进行查找
	printf("\t\t请输入您要删除的航班号：");
	scanf("%s", flight_num);
	while (p != NULL)//要删除的航班不存在，下面进行删除操作
	{
		if (strcmp(flight_num, p->flight_num) == 0)
		{
			pr->next = p->next;//移动指针找要删除的航班节点
			free(p);
			printf("\t\t删除%s航班成功！\n", flight_num);
			mark = 0;
			p = NULL;
		}
		if (pr->next != NULL)
		{
			pr = pr->next;
			p = pr->next;
		}
	}
	if (mark == 1)
		printf("\t\t无此航班，无法删除！\n");
	else
	{
		while (q != NULL)//要删除的客户不存在，下面进行删除操作
		{
			if (strcmp(flight_num, q->flight_num) == 0)
			{
				qr->next = q->next;//移动指针找要删除的客户节点
				free(q);
				q = NULL;
			}
			if (qr->next != NULL)
			{
				qr = qr->next;
				q = qr->next;
			}
		}
	}
}


//修改航班信息（包括添加删除航班信息，修改航班起飞抵达时间）
void modify_flight(flightnode *&h, passengerList *&PList)
{
	flightnode *p = h->next;
	char a;
	printf("\t\t****************************\n");
	printf("\t\t********航线信息修改********\n");
	printf("\t\t****************************\n");
	printf("\t\t*       增加航班——1      *\n");
	printf("\t\t*       删除航班——2      *\n");
	printf("\t\t*       修改航班时间——3  *\n");
	printf("\t\t****************************\n");
	printf("\t\t请选择：");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
		add_flight(h);
	else if (a == '2')
		delete_flight(h, PList);
	else if (a == '3')
	{
		modify_flight_time(h, PList);
	}
	else
		return;
}


int main()
{
	char choice;
	int t = 1;
	flightnode *flight;
	passengerList *PList;
	waitList *WList;
	init_flight(flight);
	init_passengerList(PList);
	init_waitList(WList);
	load_flight(flight);
	load_passenger(PList);
	load_wait(WList);
#if DEV
	insert_flight(flight, "a", "f", "t", "y", "t", 0, 1, 1);
	printf("已添加测试航班\n");
#else
#endif

	while (t == 1)
	{
		printf("\t\t****************************\n");
		printf("\t\t******飞机订票系统菜单******\n");
		printf("\t\t****************************\n");
		printf("\t\t*       录入信息——1      *\n");
		printf("\t\t*       订    票——2      *\n");
		printf("\t\t*       退    票——3      *\n");
		printf("\t\t*       查询航班——4      *\n");
		printf("\t\t*       查询订单——5      *\n");
		printf("\t\t*       查询预约——6      *\n");
		printf("\t\t*       修改航线——7      *\n");
		printf("\t\t*       保存退出——0      *\n");
		printf("\t\t****************************\n");
		printf("\t\t请选择服务：");
		choice = getch();
		printf("%c\n", choice);
		system("cls");
		if (choice == '1')
		{
			add_flight(flight);
			getch();
			system("cls");
		}
		else if (choice == '2')
		{
			book(flight, PList, WList);
			getch();
			system("cls");
		}
		else if (choice == '3')
		{
			cancel(PList, flight);
			getch();
			system("cls");
		}
		else if (choice == '4')
		{
			flight_check(flight);
			getch();
			system("cls");
		}
		else if (choice == '5')
		{
			passenger_check(PList);
			getch();
			system("cls");
		}
		else if (choice == '6')
		{
			wait_check(WList);
			getch();
			system("cls");
		}
		else if (choice == '7')
		{
			modify_flight(flight, PList);
			getch();
			system("cls");
		}
		else if (choice == '0')
		{
			printf("\t\t再见！\n");
			t = 0;
		}
	}
	save_flight(flight);
	save_passenger(PList);
	save_wait(WList);
	return 0;
}