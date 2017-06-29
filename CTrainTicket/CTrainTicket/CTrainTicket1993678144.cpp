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
	int price;
	int totalseats;
	int leftseats;
}shift;

shift allshifts[20];
int allshiftscount = 0;

typedef struct user//用户
{
	char name[20];//姓名
	char password[20];//密码
	int money;//余额
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

int getuseridexbyname(char name[20])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		user u = allusers[i];
		if (streq(u.name, name))
			return i;
	}
	return -1;
}

int getbuyidbyshiftuser(char name[], char id[])
{
	int i;
	for (i = allbuyscount - 1; i >= 0; i--)
		if (streq(allbuys[i].name, name)
			&& streq(allbuys[i].id, id))
		{
			return i;
		}
	return -1;
}

int iscurrentuseradmin()
{
	return streq(currentusername, ADMIN);
}

int iscurrentuserpassenger()
{
	int i = getuseridexbyname(currentusername);
	return i >= 0;
}

void registeruser(char name[20], char password[20])
{
	user u;
	strcpy(u.name, name);
	strcpy(u.password, password);
	u.money = 1000;
	allusers[alluserscount++] = u;
}

int userbuyin()
{
	int i, index, retryleft = 2;
	char name[20] = "";
	char pwd[20] = "^";
	char exppwd[20] = "";


	printf("\n请输入用户名：");
	scanf("%s", name);
	index = getuseridexbyname(name);
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

int adminbuyin()
{
	int i;
	char name[20] = "";
	char pwd[20] = "";
	printf("\n请输入管理员用户名：");
	scanf("%s", name);
	printf("\n请输入管理员密码：");
	scanf("%s", pwd);

	if (streq(name, ADMIN)
		&& streq(pwd, ADMIN))
	{
		printf("%s登录成功！\n", name);
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
	printf("%s\t%02d:%02d\t%s\t%s\t%d\t%d\t%d\n",
		s.id, s.hour, s.minute, s.start, s.end, s.price, s.totalseats, s.leftseats);
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
	printf("班次\t时间\t起点\t终点\t价格\t总票数\t余票\n"),
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
	int i, j, u;
	qsort(allshifts, allshiftscount, sizeof(shift), cmpfunc);
	printf("旅客%s购买的所有班次信息如下\n", name);
	printf("班次\t时间\t起点\t终点\t价格\t总票数\t余票\n"),
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
	u = getuseridexbyname(name);
	printf("旅客%s的余额为%d\n", name, allusers[u].money);

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
	int price;
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
		printf("\n请输入新价格（正整数）：");
		scanf("%d", &price);
		allshifts[i].hour = exphour;
		allshifts[i].minute = expminute;
		allshifts[i].price = price;
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
	int price;
	printf("请输入要修改时间的班次:");
	scanf("%s", &id);
	editshift(id);
}

void addshift(char id[], int hour, int minute, char start[20], char end[20], int price, int totalseats)
{
	shift s;
	strcpy(s.id, id);
	s.hour = hour;
	s.minute = minute;
	strcpy(s.start, start);
	strcpy(s.end, end);
	s.price = price;
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
	int price;
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
	printf("\n请输入价格和座位数(正整数，空格隔开）：");
	scanf("%d%d", &price, &totalseats);
	addshift(id, exphour, expminute, start, end, price, totalseats);
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
	int i, uindex;
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
				uindex = getuseridexbyname(currentusername);
				if (allusers[uindex].money < allshifts[i].price)
				{
					printf("旅客%s，抱歉，您的余额不足(%d元)，购票失败！\n", currentusername, allusers[uindex].money);
					return;
				}
				addbuy(id, currentusername);
				allusers[uindex].money -= allshifts[i].price;
				printf("旅客%s，购买车次%s成功，余额%d！\n", currentusername, id, allusers[uindex].money);
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



int returnticket(char name[], char id[])
{
	int i, sindex, uindex;
	int bindex = getbuyidbyshiftuser(name, id);
	buy b = allbuys[bindex];
	if (bindex < 0)
	{
		printf("旅客%s，抱歉，没有查到您购买车次%s的记录，退票失败！\n", name, id);
		return 0;
	}


	for (i = bindex; i < allbuyscount - 1; i++)
		allbuys[i] = allbuys[i + 1];
	allbuyscount--;

	sindex = getshiftidexbyno(id);
	allshifts[sindex].leftseats++;

	uindex = getuseridexbyname(name);
	allusers[uindex].money += allshifts[sindex].price*0.15;
	printf("旅客%s，退票车次%s成功，余额%d！\n", name, id, allusers[uindex].money);

	return 1;
}

void promptreturnticket()
{
	char id[20];
	int sindex, quantity;
	printf("尊敬的旅客%s，请输入退票的车次:", currentusername);
	scanf("%s", id);
	sindex = getshiftidexbyno(id);
	if (sindex < 0)
	{
		printf("尊敬的旅客%s，您输入的车次找不到，请检查后重新输入，谢谢。", currentusername);
		return;
	}
	returnticket(currentusername, id);
}


//id0 id1 valid
int changeticket(char name[], char id0[], char id1[])
{
	int i, sindex0, sindex1, uindex, reducemoney;
	int bindex0 = getbuyidbyshiftuser(name, id0);
	int bindex1 = getbuyidbyshiftuser(name, id1);
	if (bindex0 < 0)
	{
		printf("旅客%s，抱歉，没有查到您购买车次%s的记录，改签失败！\n", name, id0);
		return 0;
	}

	if (bindex1 >= 0)
	{
		printf("旅客%s，抱歉，改签的车次%s不能和已经购买的车次一样一样，改签失败！\n", name, id0);
		return 0;
	}


	uindex = getuseridexbyname(name);
	sindex0 = getshiftidexbyno(id0);
	sindex1 = getshiftidexbyno(id1);
	reducemoney = (allshifts[sindex1].price - allshifts[sindex0].price) + allshifts[sindex0].price*0.15;
	if (allusers[uindex].money < reducemoney)
	{
		printf("旅客%s，抱歉，您的余额不足（%d），改签失败！\n", name, allusers[uindex].money);
		return 0;
	}


	allshifts[sindex0].leftseats++;

	allshifts[sindex1].leftseats--;

	strcpy(allbuys[bindex0].id, id1);

	allusers[uindex].money -= reducemoney;
	printf("旅客%s，改签车次%s为%s成功，余额%d！\n", name, id0, id1, allusers[uindex].money);

	return 1;
}

void promptchangeticket()
{
	char id0[20], id1[20];
	int sindex0, sindex1, quantity;
	printf("尊敬的旅客%s，请输入您已购买并需要改签的车次:", currentusername);
	scanf("%s", id0);
	sindex0 = getshiftidexbyno(id0);
	if (sindex0 < 0)
	{
		printf("尊敬的旅客%s，您输入的车次找不到，请检查后重新输入，谢谢。", currentusername);
		return;
	}
	printf("尊敬的旅客%s，请输入改签为哪个车次:", currentusername);
	scanf("%s", id1);
	sindex1 = getshiftidexbyno(id1);
	if (sindex1 < 0)
	{
		printf("尊敬的旅客%s，您输入的车次找不到，请检查后重新输入，谢谢。", currentusername);
		return;
	}
	changeticket(currentusername, id0, id1);
}

int login()
{
	int i;
	char name[20] = "";
	char pwd[20] = "";
	printf("\n请输入用户名：");
	scanf("%s", name);
	printf("\n请输入密码：");
	scanf("%s", pwd);

	if (streq(name, ADMIN)
		&& streq(pwd, ADMIN))
	{
		printf("%s管理员登录成功！\n", name);
		strcpy(currentusername, ADMIN);
		return 1;
	}

	i = getuseridexbyname(name);
	if (streq(allusers[i].password, pwd))
	{
		printf("%s旅客登录成功！\n", name);
		strcpy(currentusername, name);
		return 1;
	}

	printf("用户名或密码错误，登录失败！\n");
	return 0;
}

int main()
{
	int choice = -1;
	//示例列车数据，可删除
	addshift("d001", 6, 0, "北京", "上海", 200, 3);
	addshift("k002", 11, 20, "成都", "重庆", 150, 6);
	addshift("k003", 15, 0, "长沙", "广州", 500, 9);
	//示例用户，由于需求没有写用户管理，因此写死3个用户
	registeruser("u1", "p1");
	registeruser("u3", "p3");
	registeruser("u2", "p2");
#if 0
	displayallshifts();

	strcpy(currentusername, "u1");
	searchandbuy("d001");
	searchandbuy("k002");
	displaymyshifts(currentusername);

	strcpy(currentusername, "u2");
	searchandbuy("d001");
	displaymyshifts(currentusername);

	//changeticket(currentusername, "d001", "k002");
	returnticket(currentusername, "d001");
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
		printf("\n\t 1. 登录");
		printf("\n\t 2. 添加车次");
		printf("\n\t 3. 修改发车时间和价格");
		printf("\n\t 4. 删除车次");
		printf("\n\t 5. 浏览所有车次");
		printf("\n\t 6. 查询车次并购票");
		printf("\n\t 7. 退票");
		printf("\n\t 8. 改签");
		printf("\n\t 9. 查询我的余额和已购买的车票");
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
			login();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			promptaddshift();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			prompteditshift();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			promptremoveshift();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			displayallshifts();
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			if (!iscurrentuserpassenger())
			{
				printf("当前用户%s不是旅客，没有权限操作!", currentusername);
				break;
			}
			promptsearchandbuy();
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			if (!iscurrentuserpassenger())
			{
				printf("当前用户%s不是旅客，没有权限操作!", currentusername);
				break;
			}
			promptreturnticket();
			break;
		case '8':
			printf("\n\n你选择了 8\n");
			if (!iscurrentuserpassenger())
			{
				printf("当前用户%s不是旅客，没有权限操作!", currentusername);
				break;
			}
			promptchangeticket();
			break;
		case '9':
			printf("\n\n你选择了 9\n");
			if (!iscurrentuserpassenger())
			{
				printf("当前用户%s不是旅客，没有权限操作!", currentusername);
				break;
			}
			displaymyshifts(currentusername);
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

