#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SEAT_COUNT 45

//1.李明，保定市，北市区，中华小区，2-5-203，100，三室一厅，1500，13700000001；
typedef struct house
{
	//int id;
	char name[20];
	char location[50];
	char area[20];
	char type[20];
	int price;
	char telephone[20];
	int isrent;
}house;

house allhouses[20];
int allhousescount = 0;

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

//char *isrentstring[2] = { "未租","已租" };

char *isrentstring(int index)
{
	return allhouses[index].isrent ? "已租" : "未租";
}

void displayhouse(int i)
{
	house s = allhouses[i];
	printf("%4d %4s %20s %3s %6s %5d %11s %s\n",
		i + 1, s.name, s.location, s.area, s.type, s.price, s.telephone, isrentstring(i));
}

int cmpfunc(const void * b, const void * a)
{
	return ((house*)a)->price - ((house*)b)->price;
}

void displayallhouses()
{
	int i;
	//qsort(allhouses, allhousescount, sizeof(house), cmpfunc);
	printf("所有%d位班次信息如下\r\n", allhousescount);
	//出租者姓名，房屋地址（城市、区、小区、门牌号）（房屋地址看成一个字段），房屋面积、房屋格局（例如：一室一厅）、出租价格、联系电话
	//printf("序号\t姓名\t地址\t面积\t格局\t价格\t电话\n");
	printf("%4s %4s %20s %3s %6s %5s %11s %s\n", "序号",
		"姓名", "地址", "面积", "格局", "价格", "电话", "状态");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allhousescount; i++)
	{
		displayhouse(i);
	}
	printf("--------------------------------------------\r\n");
}

int gethouseidexbytime(int hour, int minute)
{
	int i;
	//for (i = 0; i < allhousescount; i++)
	//{
	//	if (allhouses[i].hour == hour
	//		&& allhouses[i].minute == minute)
	//		return i;
	//}
	return -1;
}

void checktimevalid(int hour, int minute, int *exphour, int *expminute)
{
	while (hour > 23 || hour < 0 || minute > 59 || hour < 0)
	{
		printf("请输入合法时间(2个整数，类似14 5):");
		fseek(stdin, 0, SEEK_END);
		scanf("%d%d", &hour, &minute);
	}
	*exphour = hour;
	*expminute = minute;
}


int gethouseidexbyno(char id[50])
{
	int i;
	//for (i = 0; i < allhousescount; i++)
	//{
	//	if (streq(allhouses[i].id, id))
	//		return i;
	//}
	return -1;//没找到
}

void edithouse(char id[50])
{
	int i;
	int hour;
	int minute;
	int exphour;
	int expminute;
	i = gethouseidexbyno(id);
	//if (i >= 0)
	//{
	//	if (allhouses[i].price < SEAT_COUNT)
	//	{
	//		printf("本次列车已经有票售出，无法修改时间！\n");
	//		return;
	//	}
	//	printf("\n请输入新发车时间（24小时制时 分，空格隔开）：");
	//	scanf("%d%d", &hour, &minute);
	//	checktimevalid(hour, minute, &exphour, &expminute);
	//	if (gethouseidexbytime(exphour, expminute) >= 0)
	//	{
	//		printf("时间与已有班次重复！\n");
	//		return;
	//	}
	//	allhouses[i].hour = exphour;
	//	allhouses[i].minute = expminute;
	//	printf("修改完毕。\r\n");
	//}
	//else
	//{
	//	printf("没找到对应班次的班次。\r\n");
	//}
}

void promptedithouse()
{
	char id[50];
	printf("请输入要修改时间的班次:");
	scanf("%s", &id);
	edithouse(id);
}

void addhouse(char location[50], char area[20], char type[20], int price)
{
	house s;
	strcpy(s.name, "?");
	strcpy(s.location, location);
	strcpy(s.area, area);
	strcpy(s.type, type);
	s.price = price;
	strcpy(s.telephone, "?");
	s.isrent = 0;
	allhouses[allhousescount++] = s;
}

void promptaddhouse()
{
	char location[50];
	char area[20];
	char type[20];
	int price;
	printf("\n请输入地址 面积 格局（都是不带空格的字符串) 和价格(整数), 空格隔开：\n");
	scanf("%s%s%s%d", location, area, type, &price);
	/*checktimevalid(hour, minute, &exphour, &expminute);
	if (gethouseidexbytime(exphour, expminute) >= 0)
	{
		printf("时间与已有班次重复！\n");
		return;
	}*/
	addhouse(location, area, type, price);
	printf("完成第%d班次录入!\r\n", allhousescount);
}


void removehouse(char no[20])
{
	int i;
	int index;
	index = gethouseidexbyno(no);
	if (index >= 0)
	{
		if (allhouses[index].price < SEAT_COUNT)
		{
			printf("本次列车已经有票售出，无法删除！\n");
			return;
		}
		for (i = index; i < allhousescount - 1; i++)
			allhouses[i] = allhouses[i + 1];
		allhousescount--;
		printf("删除完毕，剩下%d次。\r\n", allhousescount);
	}
	else
	{
		printf("没找到对应班次的班次。\r\n");
	}

}

void promptremovehouse()
{
	int id;
	//printf("请输入要删除的班次:");
	//scanf("%s", id);
	//removehouse(id);
}

void searchandbuy(int hour, int minute)
{
	int i;
	char c;
	i = gethouseidexbytime(hour, minute);
	//if (i >= 0)
	//{
	//	printf("查到此班次信息如下：\r\n");
	//	displayhouse(allhouses[i]);
	//	if (allhouses[i].price > 0)
	//	{
	//		printf("要购买车票吗？输入y购买，其他键取消:");
	//		fseek(stdin, 0, SEEK_END);
	//		c = getchar();
	//		if (c == 'y' || c == 'Y')
	//		{
	//			allhouses[i].price--;
	//			printf("成功购买车票！\n");
	//		}
	//	}
	//	else
	//		printf("抱歉，此车次票已售完。");
	//}
	//else
	//{
	//	printf("没找到对应班次的班次。\r\n");
	//}

}

void promptsearchandbuy()
{
	int hour;
	int minute;
	printf("请输入要查询的发车时间（24小时制时 分，空格隔开）：");
	scanf("%d%d", &hour, &minute);
	searchandbuy(hour, minute);
}

void add8houses()
{
	addhouse("保定市北市区中华小区2-5-203", "100", "三室一厅", 1500);

}

int main()
{
	int choice = -1;
	//add8houses();
#if 1
	promptaddhouse();
	//displayallhouses();
	//allhouses[1].leftseats = 44;
	//promptaddhouse();
	//promptedithouse();
	//promptsearchandbuy();
	//searchandbuy(7, 0);
	//promptremovehouse();
	displayallhouses();
	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t 火车订票系统");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 添加车次");
		printf("\n\t 2. 修改发车时间");
		printf("\n\t 3. 删除");
		printf("\n\t 4. 查询");
		printf("\n\t 5. 浏览");
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
			promptaddhouse();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptedithouse();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptremovehouse();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptsearchandbuy();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			displayallhouses();
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

