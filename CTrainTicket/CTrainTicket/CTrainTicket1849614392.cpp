#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

int cmpfunc(const void * a, const void * b)
{
	int ha = ((shift*)a)->hour;
	int ma = ((shift*)a)->minute;
	int hb = ((shift*)b)->hour;
	int mb = ((shift*)b)->minute;
	return (ha - hb) * 60 + ma - mb;
}

void displayallshifts()
{
	int i;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("所有%d位班次信息如下\r\n", allshiftscount);
	printf("班次\t时间\t起点\t终点\t座位\t余票\n"),
		printf("--------------------------------------------\r\n");
	for (i = 0; i < allshiftscount; i++)
	{
		displayshift(allshifts[i]);
	}
	printf("--------------------------------------------\r\n");
}

int getshiftidexbytime(int hour, int minute)
{
	int i;
	for (i = 0; i < allshiftscount; i++)
	{
		if (allshifts[i].hour == hour
			&& allshifts[i].minute == minute)
			return i;
	}
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
	int hour;
	int minute;
	int exphour;
	int expminute;
	i = getshiftidexbyno(id);
	if (i >= 0)
	{
		if (allshifts[i].leftseats < SEAT_COUNT)
		{
			printf("本次列车已经有票售出，无法修改时间！\n");
			return;
		}
		printf("\n请输入新发车时间（24小时制时 分，空格隔开）：");
		scanf("%d%d", &hour, &minute);
		checktimevalid(hour, minute, &exphour, &expminute);
		if (getshiftidexbytime(exphour, expminute) >= 0)
		{
			printf("时间与已有班次重复！\n");
			return;
		}
		allshifts[i].hour = exphour;
		allshifts[i].minute = expminute;
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
	printf("请输入要修改时间的班次:");
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
	int exphour;
	int expminute;
	printf("\n请输入班次（不重复）:\n");
	scanf("%s", id);
	if (getshiftidexbyno(id) >= 0)
	{
		printf("班次与已有班次重复！\n");
		return;
	}
	printf("\n请输入新发车时间（24小时制时 分，空格隔开）：");
	scanf("%d%d", &hour, &minute);
	checktimevalid(hour, minute, &exphour, &expminute);
	if (getshiftidexbytime(exphour, expminute) >= 0)
	{
		printf("时间与已有班次重复！\n");
		return;
	}
	addshift(id, exphour, expminute);
	printf("完成第%d班次录入!\r\n", allshiftscount);
}


void removeshift(char no[20])
{
	int i;
	int index;
	index = getshiftidexbyno(no);
	if (index >= 0)
	{
		if (allshifts[index].leftseats < SEAT_COUNT)
		{
			printf("本次列车已经有票售出，无法删除！\n");
			return;
		}
		for (i = index; i < allshiftscount - 1; i++)
			allshifts[i] = allshifts[i + 1];
		allshiftscount--;
		printf("删除完毕，剩下%d次。\r\n", allshiftscount);
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

void searchandbuy(int hour, int minute)
{
	int i;
	char c;
	i = getshiftidexbytime(hour, minute);
	if (i >= 0)
	{
		printf("查到此班次信息如下：\r\n");
		displayshift(allshifts[i]);
		if (allshifts[i].leftseats > 0)
		{
			printf("要购买车票吗？输入y购买，其他键取消:");
			fseek(stdin, 0, SEEK_END);
			c = getchar();
			if (c == 'y' || c == 'Y')
			{
				allshifts[i].leftseats--;
				printf("成功购买车票！\n");
			}
		}
		else
			printf("抱歉，此车次票已售完。");
	}
	else
	{
		printf("没找到对应班次的班次。\r\n");
	}

}

void promptsearchandbuy()
{
	int hour;
	int minute;
	printf("请输入要查询的发车时间（24小时制时 分，空格隔开）：");
	scanf("%d%d", &hour, &minute);
	searchandbuy(hour, minute);
}

void add8shifts()
{
	addshift("k001", 6, 0);
	addshift("k002", 7, 0);
	addshift("k003", 9, 0);
	addshift("k004", 10, 30);
	addshift("k005", 14, 0);
	addshift("k006", 15, 30);
	addshift("k007", 16, 30);
	addshift("k008", 17, 30);
}

int main()
{
	int choice = -1;
	add8shifts();
#if 0
	//promptaddshift();
	displayallshifts();
	allshifts[1].leftseats = 44;
	promptaddshift();
	//prompteditshift();
	//promptsearchandbuy();
	//searchandbuy(7, 0);
	//promptremoveshift();
	displayallshifts();
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
			promptaddshift();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			prompteditshift();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptremoveshift();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptsearchandbuy();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			displayallshifts();
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

