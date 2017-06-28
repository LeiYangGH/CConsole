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

int cmpfunc(const void * a, const void * b)
{
	return ((user*)a)->name - ((user*)b)->name;
}

void displayallusers()
{
	int i;
	qsort(allusers, alluserscount, sizeof(user), cmpfunc);
	printf("所有%d位用户信息如下\r\n", alluserscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < alluserscount; i++)
	{
		displayuser(allusers[i]);
	}
	printf("--------------------------------------------\r\n");
}

void displayalllockedusers()
{
	int i;
	qsort(allusers, alluserscount, sizeof(user), cmpfunc);
	printf("所有被锁定用户信息如下\r\n", alluserscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < alluserscount; i++)
	{
		if (allusers[i].islocked)
			displayuser(allusers[i]);
	}
	printf("--------------------------------------------\r\n");
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

//登录
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

	if (allusers[index].islocked)
	{
		printf("\n用户%s为锁定状态，请联系管理员解锁\n", name);
		return 0;
	}

	strcpy(exppwd, allusers[index].password);

	printf("请输入密码: ");
	fseek(stdin, 0, SEEK_END);
	scanf("%s", pwd);
	while (!streq(exppwd, pwd) && retryleft-- > 0)
	{
		printf("密码错误,请重新输入:");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", pwd);
	}
	if (streq(exppwd, pwd))
	{
		printf("%s登录成功！\n", name);
		strcpy(currentusername, name);
		return 1;
	}
	else
	{
		allusers[index].islocked = 1;
		printf("抱歉，用户%s已被锁定", name);
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

void promptunlockuser()
{
	int index;
	char name[20];//姓名
	printf("\n请输入要解锁的用户名:");
	scanf("%s", name);
	index = getuseridexbyuname(name);
	if (index < 0)
	{
		printf("\n用户名不存在\n");
		return;
	}

	if (allusers[index].islocked)
	{
		allusers[index].islocked = 0;
		printf("\n为用户%s解锁成功\n", name);
	}
	else
		printf("\n用户%s当前为活跃状态，不需要解锁\n", name);
}

void edituser(char name[50])
{
	int index;
	char gender[20];//性别
	char birthday[20];//出生年月	i = getuseridexbyuname(name);
	index = getuseridexbyuname(name);
	if (index >= 0)
	{
		printf("\n请输入新的性别、出生年月\n");
		scanf("%s%s", allusers[index].gender, allusers[index].birthday);
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应用户名的用户。\r\n");
	}
}


//登出
void logout()
{
	strcpy(currentusername, "");
	printf("登出成功!");
}


#pragma endregion


void menu22()
{
	int choice = -1;
	char location[50];
	char type[20];
	while (choice != 0)
	{
		printf("\n\t 用户管理");
		printf("\n\t 0. 返回上级菜单");
		printf("\n\t    登录");
		printf("\n\t\t   管理员登录");
		printf("\n\t\t\t   1.显示所有用户");
		printf("\n\t\t\t   2.显示锁定用户");
		printf("\n\t\t\t   3.锁定用户解锁");
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
			displayallusers();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayalllockedusers();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptunlockuser();
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
		printf("\n\t 用户管理");
		printf("\n\t 0. 返回上级菜单");
		printf("\n\t    登录");
		printf("\n\t\t   1.普通用户登录（并修改自己的基本信息）");
		printf("\n\t\t   2.管理员登录");
		printf("\n\t\t\t   显示所有用户");
		printf("\n\t\t\t   显示锁定用户");
		printf("\n\t\t\t   锁定用户解锁");
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
			if (userlogin())
			{
				edituser(currentusername);
			}
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			if (adminlogin())
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
	char choice = -1;
	registeruser("u1", "p1", "g1", "b1", "e1");
	registeruser("u3", "p3", "g3", "b3", "e3");
	registeruser("u2", "p2", "g2", "b2", "e2");
#if 0 //测试用
	//login();
	registeruser("u1", "p1", "g1", "b1", "e1");
	registeruser("u3", "p3", "g3", "b3", "e3");
	registeruser("u2", "p2", "g2", "b2", "e2");
	//promptregisteruser();
	//promptregisteruser();
	edituser("u1");
	displayallusers();
	strcpy(currentusername, "u1");
#endif
	while (choice != 0)
	{
		printf("\n\t 用户管理");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 注册");
		printf("\n\t 2. 登录");
		printf("\n\t\t   普通用户登录（并修改自己的基本信息）");
		printf("\n\t\t   管理员登录");
		printf("\n\t\t\t   显示所有用户");
		printf("\n\t\t\t   显示锁定用户");
		printf("\n\t\t\t   锁定用户解锁");
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
			promptregisteruser();
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