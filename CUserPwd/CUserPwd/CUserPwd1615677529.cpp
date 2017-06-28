//1、 设计并实现一个用户管理，实现用户的管理。要求实现两种角色：普通用户和管理员（用户名admin，密码：admin）。一级菜单：
//1)       注册
//2)       登录
//请选择：
//选择1.注册后，要求输入用户基本信息：用户名、密码、确认密码、性别、出生年月以及验证信息（邮箱）；要求①验证信息必须是邮箱，且不能重复注册，若输入的邮箱不正确，请重新输入。提示：邮箱必须有@和.，@在.前面，且@不能开头，.不能结尾。②密码以及确认密码应该保持一致，若不一样，请重新输入。
//选择2.登录后，实现二级菜单：
//1)       普通用户登录
//2)       管理员登录
//请选择：
//选择1.普通用户登录后，输入用户名以及密码，密码有三次输入机会，若三次都输入错误，用户被锁定不可以再进行登录；若登录成功，用户可以修改自己的基本信息（邮箱不能修改）。
//选择2.管理员登录后，输入用户名（admin）密码（admin）后，实现三级菜单：
//1)       显示所有用户（按照用户名排序）
//2)       显示锁定用户（按照用户名排序）
//选择2.显示锁定用户后，实现如下功能：按照用户名进行查询后，若存在该用户，将该用户的锁定状态解除。
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define ADMIN "admin"
#pragma region typedef
typedef struct user//用户
{
	char name[20];//姓名
	char password[20];//密码
	char gender[20];//性别
	char birthday[20];//出生年月
	char email[20];//验证邮箱
	int islocked;
}user;
user allusers[20];
int alluserscount = 0;


#pragma endregion

char currentusername[20] = "";

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}
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
#pragma region users
void displayuser(user u)
{
	printf("%s\t%s\t%s\t%s\n",
		  u.name, u.gender, u.birthday, u.email);
}

//int cmpfunc(const void * a, const void * b)
//{
//	return ((user*)a)->author - ((user*)b)->author;
//}

void displayallusers()
{
	int i;
	//qsort(allusers, alluserscount, sizeof(user), cmpfunc);
	printf("所有%d位用户信息如下\r\n", alluserscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < alluserscount; i++)
	{
		displayuser(allusers[i]);
	}
	printf("--------------------------------------------\r\n");
}


//登录
void login()
{
	int i;
	char uname[20] = "";
	char pwd[20] = "";
	printf("\n请输入用户名\n");
	scanf("%s", uname);
	printf("\n请输入密码\n");
	scanf("%s", pwd);
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(uname, allusers[i].name)
			&& streq(pwd, allusers[i].password))
		{
			printf("%s登录成功！\n", uname);
			strcpy(currentusername, uname);
			return;
		}
	}
	printf("用户名或密码错误，登录失败！\n");
}

//是否已经存在相同用户名
int isusernameexists(char uname[20])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(uname, allusers[i].name))
			return 1;
	}
	return 0;
}

//根据用户名得出数组下标
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

//int ispassowrdcomplicated(char password[20])
//{
//	return strlen(password) >= 6;
//}

int isemailvalid(char email[20])
{
	int i, len = strlen(email), iat = -1, idot = -1;
	for (i = 0; i < len; i++)
	{
		if (email[i] == '@')
			iat = i;
		else if (email[i] == '.')
			idot = i;
	}
	return iat != -1 && idot != -1
		&& iat < idot
		&& iat != 0 && idot != len - 1;
}


//注册用户，已经通过验证的参数
void registeruser(char name[20], char password[20], char gender[20], char birthday[20], char email[20])
{
	user u;
	strcpy(u.name, name);
	strcpy(u.password, password);
	strcpy(u.gender, gender);
	strcpy(u.birthday, birthday);
	strcpy(u.email, email);
	u.islocked = 0;
	allusers[alluserscount++] = u;
}

//当前用户是否管理员
int iscurrentuseradmin()
{
	return streq(currentusername, ADMIN);
}


void promptregisteruser()
{
	char name[20];//姓名
	char password[20] = "1";//密码
	char password1[20] = "2";//密码
	char gender[20];//性别
	char birthday[20];//出生年月
	char email[20];//验证邮箱

	printf("\n请输入要注册的的用户名:");
	scanf("%s", name);
	if (isusernameexists(name))
	{
		printf("%s已经存在，不能重复注册!", name);
		return;
	}
	while (!streq(password, password1))
	{
		printf("请输入要注册的密码:");
		scanf("%s", password);
		printf("请再次输入要注册的密码:");
		scanf("%s", password1);
		if (!streq(password, password1))
		{
			printf("两次输入的密码不一致！");
		}
	}
	printf("请输入性别和生日，空格隔开:");
	scanf("%s%s", gender, birthday);
	while (!isemailvalid(email))
	{
		printf("请输入验证邮箱:");
		scanf("%s", email);
		if (!isemailvalid(email))
		{
			printf("邮箱必须有@和.，@在.前面，且@不能开头，.不能结尾!");
		}
	}
	registeruser(name, password, gender, birthday, email);
	printf("新用户注册成功!");
}

//登出
void logout()
{
	strcpy(currentusername, "");
	printf("登出成功!");
}


#pragma endregion

#pragma region ware





//
////修改商品只允许修改价格和库存
//void editware(char wid[50])
//{
//	int i;
//	char pwd[20] = "";
//	i = getwareidexbywid(wid);
//	if (i >= 0)
//	{
//		printf("\n请输入新的价格（整数或浮点数）和库存（整数），空格隔开\n");
//		scanf("%f%d", &allwares[i].price, &allwares[i].quantity);
//		writeallwares();
//		printf("修改完毕。\r\n");
//	}
//	else
//	{
//		printf("没找到对应识别码的商品。\r\n");
//	}
//}
//
//void prompteditware()
//{
//	char wid[50];
//	printf("请输入要修改的识别码:");
//	scanf("%s", &wid);
//	editware(wid);
//}

////添加商品
//void addware(char wid[20], char wname[], char address[],
//	float price, int quantity, int leastleft, int leastout)
//{
//	ware w;
//	strcpy(w.wid, wid);
//	strcpy(w.name, wname);
//	strcpy(w.address, address);
//	w.price = price;
//	w.quantity = quantity;
//	w.leastleft = leastleft;
//	w.leastout = leastout;
//	allwares[allwarescount++] = w;
//	writeallwares();
//}


//通过名称查找商品
//void searchwarebyname(char *name)
//{
//	int i;
//	for (i = 0; i < allwarescount; i++)
//		if (strcmp(name, allwares[i].name) == 0)
//		{
//			displayware(allwares[i]);
//			return;
//		}
//	printf("没找到对应商品的信息。\r\n");
//}
////用户输入名称并查找商品信息
//void promptsearchbyname()
//{
//	char name[20];
//	printf("请输入要查找的商品名称:");
//	scanf("%s", name);
//	searchwarebyname(name);
//}


#pragma endregion




int main()
{
	char choice = -1;

#if 1 //测试用
	//login();
	registeruser("u1", "p1", "g1", "b1", "e1");
	registeruser("u3", "p3", "g3", "b3", "e3");
	registeruser("u2", "p2", "g2", "b2", "e2");
	promptregisteruser();
	//promptregisteruser();
	displayallusers();
	strcpy(currentusername, "u1");
#endif
	while (choice != 'g')
	{
		printf("\n\t 超市管理系统");
		printf("\n\t 1---用户登录");
		printf("\n\t 2---用户登出");
		printf("\n\t 3---注册消费者");
		printf("\n\t 4---注册管理员");
		printf("\n\t 5---查看所有商品信息");
		printf("\n\t 6---根据名称查找商品");
		printf("\n\t 7---添加商品");
		printf("\n\t 8---输入识别码修改商品价格和库存");
		printf("\n\t 9---输入识别码删除商品");
		printf("\n\t a---显示库存不足和滞销商品");
		printf("\n\t b---添加商品到购物车");
		printf("\n\t c---结帐付款");
		printf("\n\t d---充值");
		printf("\n\t e---退货");
		printf("\n\t f---把本次运行的消费记录追加到文件");
		printf("\n\t 0---退出程序\n\n");
		printf("\n---请选择：");
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
			logout();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			break;
		case '8':
			printf("\n\n你选择了 8\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			break;
		case '9':
			printf("\n\n你选择了 9\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			break;
		case 'a':
			printf("\n\n你选择了 a\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			break;
		 
		 
	  
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
	printf("\n\n按任意键退出\n");
	system("pause");
	return 0;
}