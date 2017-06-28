//管理员登录
//录入火车信息（起点终点，起发时间，到达时间，车次，席别，余票）
//增删信息 修改信息
//用户登录（ 判断密码和ID是否正确）
//通过 车次 查询车辆
//输入要购买的票的车次
//查看已购买的票
//若付款成功，且系统时间距出发时间大于两小时
//退票：相关车票余额－１，扣除手续费退还至账户
//改签：重复买票阶段，相关车票余额 - 1，扣除手续费
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define ADMIN "admin"
typedef struct shift
{
	char id[20];
	int hour;
	int minute;
	char start[20];
	char end[20];
	char seattype[20];
	int totalseats;
	int leftseats;
}shift;

shift allshifts[20];
int allshiftscount = 0;

typedef struct user//用户
{
	char name[20];//姓名
	char password[20];//密码
}user;
user allusers[20];
int alluserscount = 0;

char currentusername[20] = "";


typedef struct buy//用户
{
	char id[20];
	char name[20];
}buy;
buy allbuys[20];
int allbuyscount = 0;

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

int getuseridexbyuname(char uname[20])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		user u = allusers[i];
		if (streq(u.name, uname))
			return i;
	}
	return -1;
}
void registeruser(char name[20], char password[20])
{
	user u;
	strcpy(u.name, name);
	strcpy(u.password, password);
	allusers[alluserscount++] = u;
}

int userlogin()
{
	int i, index, retryleft = 2;
	char name[20] = "";
	char pwd[20] = "^";
	char exppwd[20] = "";


	printf("\n请输入用户名：");
	scanf("%s", name);
	index = getuseridexbyuname(name);
	if (index < 0)
	{
		printf("\n用户名不存在\n");
		return 0;
	}

	strcpy(exppwd, allusers[index].password);

	printf("请输入密码: ");
	fseek(stdin, 0, SEEK_END);
	scanf("%s", pwd);

	if (streq(exppwd, pwd))
	{
		printf("%s登录成功！\n", name);
		strcpy(currentusername, name);
		return 1;
	}
	else
	{
		printf("抱歉，密码错误登录失败");
		return 0;
	}
}

int adminlogin()
{
	int i;
	char uname[20] = "";
	char pwd[20] = "";
	printf("\n请输入管理员用户名：");
	scanf("%s", uname);
	printf("\n请输入管理员密码：");
	scanf("%s", pwd);

	if (streq(uname, ADMIN)
		&& streq(pwd, ADMIN))
	{
		printf("%s登录成功！\n", uname);
		strcpy(currentusername, ADMIN);
		return 1;
	}
	printf("用户名或密码错误，登录失败！\n");
	return 0;
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
		s.id, s.hour, s.minute, s.start, s.end, s.totalseats, s.leftseats);
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

void displaymyshifts(char name[20])
{
	int i, j;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("旅客%s购买的所有班次信息如下\n", name);
	printf("班次\t时间\t起点\t终点\t座位\t余票\n"),
		printf("--------------------------------------------\r\n");
	for (i = 0; i < allbuyscount; i++)
	{
		if (streq(allbuys[i].name, name))
		{
			j = getshiftidexbyno(allbuys[i].id);
			displayshift(allshifts[j]);
		}
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
		if (allshifts[i].leftseats < allshifts[i].totalseats)
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

void addshift(char id[], int hour, int minute, char start[20], char end[20], char seattype[20], int totalseats)
{
	shift s;
	strcpy(s.id, id);
	s.hour = hour;
	s.minute = minute;
	strcpy(s.start, start);
	strcpy(s.end, end);
	strcpy(s.seattype, seattype);
	s.totalseats = totalseats;
	s.leftseats = totalseats;
	allshifts[allshiftscount++] = s;
}

void promptaddshift()
{
	char id[20];
	int hour;
	int minute;
	int exphour;
	char start[20];
	char end[20];
	char seattype[20];
	int expminute;
	int totalseats;
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
	printf("\n请输入始发站和终点站(空格隔开）：");
	scanf("%s%s", start, end);
	printf("\n请输入席别和座位数(空格隔开）：");
	scanf("%s%d", seattype, &totalseats);
	addshift(id, exphour, expminute, start, end, seattype, totalseats);
	printf("完成第%d班次录入!\r\n", allshiftscount);
}


void removeshift(char no[20])
{
	int i;
	int index;
	index = getshiftidexbyno(no);
	if (index >= 0)
	{
		if (allshifts[index].leftseats < allshifts[index].totalseats)
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


void addbuy(char id[20], char name[20])
{
	int i;
	buy b;
	strcpy(b.id, id);
	strcpy(b.name, name);
	i = getshiftidexbyno(id);
	allshifts[i].leftseats--;
	allbuys[allbuyscount++] = b;
}


void searchandbuy(char id[20])
{
	int i;
	char c;
	i = getshiftidexbyno(id);
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
				addbuy(id, currentusername);
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
	char id[20];
	printf("请输入要购买的车次：");
	scanf("%s", id);
	searchandbuy(id);
}

void addsampleshifts()
{
	addshift("d001", 6, 0, "北京", "上海", "硬座", 3);
	addshift("k002", 11, 20, "成都", "重庆", "硬卧", 6);
	addshift("k003", 15, 0, "长沙", "广州", "软卧", 9);
}

int main()
{
	int choice = -1;
	addsampleshifts();
	registeruser("u1", "p1");
	registeruser("u3", "p3");
	registeruser("u2", "p2");
#if 1
	displayallshifts();

	strcpy(currentusername, "u1");
	searchandbuy("d001");
	searchandbuy("k002");
	displaymyshifts(currentusername);

	strcpy(currentusername, "u2");
	searchandbuy("d001");
	displaymyshifts(currentusername);

	//promptaddshift();
	//allshifts[1].leftseats = 44;
	//promptaddshift();
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

