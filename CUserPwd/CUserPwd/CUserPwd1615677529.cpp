#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma region typedef
typedef struct user//用户
{
	char name[20];//姓名
	char password[20];//密码
	int isadmin;//是否管理员
	float money;//余额
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

//密码复杂度，暂时规定长度>=6
int ispassowrdcomplicated(char password[20])
{
	return strlen(password) >= 6;
}


//注册用户，已经通过验证的参数
void registeruser(char uname[20], char password[20], int isadmin)
{
	user u;
	strcpy(u.name, uname);
	strcpy(u.password, password);
	u.isadmin = isadmin;
	u.money = 0;//余额开始都为0
	allusers[alluserscount++] = u;
}

//当前用户是否管理员
int iscurrentuseradmin()
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (allusers[i].isadmin
			&& streq(currentusername, allusers[i].name))
			return 1;
	}
	return 0;
}

//当前用户是否消费者
int iscurrentuserconsumer()
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (!allusers[i].isadmin
			&& streq(currentusername, allusers[i].name))
			return 1;
	}
	return 0;
}

//prompt交互式提示用户输入
void promptregisteruser(int willbeadmin)
{
	char uname[20];
	char password[20];
	char *role = willbeadmin ? "管理员" : "消费者";
	if (willbeadmin && !iscurrentuseradmin())
	{
		printf("当前用户%s不是管理员，不能注册管理员!", currentusername);
		return;
	}
	printf("请输入要注册的%s的用户名:", role);
	scanf("%s", uname);
	if (isusernameexists(uname))
	{
		printf("%s已经存在，不能重复注册!", uname);
		return;
	}
	printf("请输入要注册的密码:");
	scanf("%s", password);
	if (!ispassowrdcomplicated(password))
	{
		printf("密码%s太简单，至少6位!", password);
		return;
	}
	registeruser(uname, password, willbeadmin);
	printf("新%注册成功!", role);
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
 
#if 0 //测试用
	//login();
	//promptregisteruser(0);
	strcpy(currentusername, "u1");
	addtocart("u1", "006", 2);
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
			promptregisteruser(0);
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptregisteruser(1);
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
		case 'b':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			break;
		case 'c':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			break;
		case 'd':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			break;
		case 'e':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			break;
		case 'f':
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