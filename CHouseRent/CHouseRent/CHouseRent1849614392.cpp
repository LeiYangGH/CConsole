#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//1.李明，保定市，北市区，中华小区，2-5-203，100，三室一厅，1500，13700000001；
typedef struct house
{
	char name[20];
	char address[50];
	char area[20];
	char type[20];
	int price;
	char telephone[20];
	int isrent;
}house;

house allhouses[20];
int allhousescount = 0;
int filteredindex[20] = { -1 };
int filteredindexcount = 0;
//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

char *isrentstring(int index)
{
	return allhouses[index].isrent ? "已租" : "未租";
}

void displayhouse(int i)
{
	house s = allhouses[i];
	printf("%4d %4s %20s %3s %6s %5d %11s %s\n",
		i + 1, s.name, s.address, s.area, s.type, s.price, s.telephone, isrentstring(i));
}

int cmpprice(const void * a, const void * b)
{
	return ((house*)a)->price - ((house*)b)->price;
}

void displayallhouses(int isrent, char location[50], char type[20])
{
	int i;
	char *msg[2] = { "未租","已租" };
	printf("所有%s房源信息如下\r\n", msg[isrent]);
	//出租者姓名，房屋地址（城市、区、小区、门牌号）（房屋地址看成一个字段），房屋面积、房屋格局（例如：一室一厅）、出租价格、联系电话
	printf("%4s %4s %20s %3s %6s %5s %11s %s\n", "序号",
		"姓名", "地址", "面积", "格局", "价格", "电话", "状态");
	printf("--------------------------------------------\r\n");
	filteredindexcount = 0;
	for (i = 0; i < allhousescount; i++)
	{
		if (isrent == allhouses[i].isrent
			&& (streq(location, "") || streq(allhouses[i].address, location))
			&& (streq(type, "") || streq(allhouses[i].type, type)))
		{
			displayhouse(i);
			filteredindex[filteredindexcount++] = i;
		}
	}
	printf("--------------------------------------------\r\n");
}

void addhouse(char location[50], char area[20], char type[20], int price)
{
	house s;
	strcpy(s.name, "?");
	strcpy(s.address, location);
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
	addhouse(location, area, type, price);
	printf("完成第%d房源录入!\r\n", allhousescount);
}

int isindexinfiltered(int index)
{
	int i;
	for (i = 0; i < filteredindexcount; i++)
		if (filteredindex[i] == index)
			return 1;
	return 0;
}

void removehouse(int index)
{
	int i;
	if (index >= 0 && index < allhousescount)
	{
		if (!allhouses[index].isrent)
		{
			printf("序号为%d的房源尚未出租，无法删除！\n", index + 1);
			return;
		}
		for (i = index; i < allhousescount - 1; i++)
			allhouses[i] = allhouses[i + 1];
		allhousescount--;
		printf("删除完毕。\r\n");
	}
	else
	{
		printf("没找到序号为%d的房源。\r\n", index + 1);
	}

}

void promptremovehouse()
{
	int id;
	printf("请输入要删除的房源的序号:");
	scanf("%d", &id);
	removehouse(id - 1);
}

void renthouse(int index)
{
	int i;
	char name[20];
	char telephone[20];
	if (isindexinfiltered(index))
	{
		if (allhouses[index].isrent)
		{
			printf("序号为%d的房源已经出租，无法再租！\n", index + 1);
			return;
		}
		printf("\n请输入出租人姓名 电话（都是不带空格的字符串), 空格隔开：\n");
		scanf("%s%s", name, telephone);

		strcpy(allhouses[index].name, name);
		strcpy(allhouses[index].telephone, telephone);
		allhouses[index].isrent = 1;
		printf("出租成功。\r\n");
	}
	else
	{
		printf("序号为%d的房源没在筛选结果范围内。\r\n", index + 1);
	}

}

void promptrenthouse()
{
	int id;
	printf("请输入要出租的房源的序号:");
	scanf("%d", &id);
	renthouse(id - 1);
}

void add4houses()
{
	addhouse("保定市北市区中华小区2-5-203", "100", "三室一厅", 1500);
	addhouse("add2", "200", "type2", 2500);
	addhouse("add3", "300", "typex", 350);
	addhouse("add4", "400", "typex", 45);

}

void menu1()
{
	int choice = -1;
	while (choice != 0)
	{
		printf("\n\t 房屋租赁管理系统");
		printf("\n\t 0. 返回上级菜单");
		printf("\n\t  我要出租");
		printf("\n\t\t 1 添加房源");
		printf("\n\t\t 2 删除已租信息");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			fseek(stdin, 0, SEEK_END);
			return;
		case '1':
			printf("\n\n你选择了 1\n");
			promptaddhouse();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallhouses(1, "", "");
			promptremovehouse();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
}

void menu22()
{
	int choice = -1;
	char location[50];
	char type[20];
	while (choice != 0)
	{
		printf("\n\t 房屋租赁管理系统");
		printf("\n\t 0. 返回上级菜单");
		printf("\n\t   我要租房");
		printf("\n\t\t    查找");
		printf("\n\t\t\t  1 按照地址查找");
		printf("\n\t\t\t  2 按照格局查找");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			fseek(stdin, 0, SEEK_END);
			return;
		case '1':
			printf("\n\n你选择了 1\n");
			printf("请输入要查询的房屋地址（必须精确匹配）：");
			scanf("%s", location);
			qsort(allhouses, allhousescount, sizeof(house), cmpprice);
			displayallhouses(0, location, "");
			if (filteredindexcount > 0)
			{
				promptrenthouse();
			}
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			printf("请输入要查询的房屋格局（必须精确匹配）：");
			scanf("%s", type);
			qsort(allhouses, allhousescount, sizeof(house), cmpprice);
			displayallhouses(0, "", type);
			if (filteredindexcount > 0)
			{
				promptrenthouse();
			}
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
}


void menu2()
{
	int choice = -1;
	while (choice != 0)
	{
		printf("\n\t 房屋租赁管理系统");
		printf("\n\t 0. 返回上级菜单");
		printf("\n\t   我要租房");
		printf("\n\t\t  1 房源信息");
		printf("\n\t\t  2 查找");
		printf("\n\t\t\t   按照地址查找");
		printf("\n\t\t\t   按照格局查找");
		printf("\n\n  请选择: ");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			fseek(stdin, 0, SEEK_END);
			return;
		case '1':
			printf("\n\n你选择了 1\n");
			displayallhouses(0, "", "");
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			menu22();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
}

int main()
{
	int choice = -1;
	add4houses();
#if 0
	displayallhouses(0, "", "");

	//promptaddhouse();
	//displayallhouses();
	//allhouses[1].leftseats = 44;
	//promptaddhouse();
	//promptedithouse();
	//promptsearchandrent();
	//searchandrent(7, 0);
	//promptremovehouse();
	promptremovehouse();
	displayallhouses(0, "", "");
	system("pause");
#endif
	while (choice != 0)
	{
		printf("\n\t 房屋租赁管理系统");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 我要出租");
		printf("\n\t\t   添加房源");
		printf("\n\t\t   删除已租信息");
		printf("\n\t 2. 我要租房");
		printf("\n\t\t   房源信息");
		printf("\n\t\t   查找");
		printf("\n\t\t\t   按照地址查找");
		printf("\n\t\t\t   按照格局查找");
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
			menu1();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			menu2();
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

