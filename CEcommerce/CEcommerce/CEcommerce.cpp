#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_USER "user.txt"//消费者文件
#define FILE_ADMIN "admin.txt"//管理员文件
#define FILE_WARE "ware.txt"//商品文件，可增删改查，下次运行exe时读入
#define FILE_LOG "log.txt"//购物记录文件，只提供一次性追加，下次运行exe时不读入
typedef struct ware//商品
{
	char wid[20];//产品标识码
	char name[20];//名称
	float price;//单价
	char address[20];//产地
	int quantity;//库存
	int warnquantity;//警告最低库存阈值
}ware;

ware allwares[20];//所有商品，下同
int allwarescount = 0;//所有商品种类数量，下同

typedef struct user//用户
{
	char name[20];//姓名
	char password[20];//密码
	int isadmin;//是否管理员
	float money;//余额
}user;
user allusers[20];
int alluserscount = 0;

typedef struct log//购买记录
{
	char uname[20];//消费者姓名
	char wid[20];//商品识别码
	float quantity;//数量
	int paid;//是否付费，1为购买，0为没购买，相当于购物车
}log;

user alllogs[10];
int alllogscount = 0;

char currentusername[20] = "";

int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
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

//是否已经存在相同用户
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

//密码复杂度，暂时规定长度>=6
int ispassowrdcomplicated(char password[20])
{
	return strlen(password) >= 6;
}

//写所有用户和管理员到文件
void writeallusersandadmins()
{
	int i;
	user u;
	FILE *fp = fopen(FILE_USER, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_USER);
		getchar();
		exit(1);
	}
	for (i = 0; i < alluserscount; i++)
	{
		u = allusers[i];
		if (!u.isadmin)
			fprintf(fp, "%s\t%s\n", u.name, u.password);
	}
	fclose(fp);

	fp = fopen(FILE_ADMIN, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_ADMIN);
		getchar();
		exit(1);
	}
	for (i = 0; i < alluserscount; i++)
	{
		u = allusers[i];
		if (u.isadmin)
			fprintf(fp, "%s\t%s\n", u.name, u.password);
	}
	fclose(fp);
	printf("已保存记录到文件。");
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
	writeallusersandadmins();
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

//从一行文本拆分为用户
user getuserfromline(char *line, int isadmin)
{
	char *part;
	int index = 0;
	user u;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(u.name, part);
			break;
		case 2:
			strcpy(u.password, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	u.isadmin = isadmin;
	u.money = 0;//余额开始都为0
	return u;
}

//读入所有消费者和管理员
void readallusersandadmins()
{
	char line[200];
	FILE *fp = fopen(FILE_USER, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_USER);
	}
	else
	{
		alluserscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allusers[alluserscount++] = getuserfromline(line, 0);
		}
		printf("\n已读入消费者文件!\n");
	}
	fp = fopen(FILE_ADMIN, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_ADMIN);
	}
	else
	{
		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allusers[alluserscount++] = getuserfromline(line, 1);
		}
		printf("\n已读入管理员文件!\n");
	}
}

#pragma endregion



//显示所有商品
void displayallwares()
{
}

//读入所有商品
void readallwares()
{
}

//根据商品识别码得出数组下标
int getwareidexbyno(char wid[20])
{
	return 1;

}

//写所有商品信息到文件
void writeallwares()
{
}

//修改商品只允许修改价格和库存
void editware(char wid[20])
{
}

//添加商品
void addware(char wid[20], char uname[], float price, char address, int quantity, int warnquantity)
{
}

//删除商品
void removeware(char wid[20])
{
}

//通过名称查找商品
void searchwarebyname(char *uname)
{
}

//写所有购物记录
void writealllogs()
{

}

//每次加入购物车就检查库存如果不足则警告
void warnlack(char wid[20])
{

}
//加购物车，log里加
void addwant(char uname[], char wid[], int quantity)
{

}

//充值
void recharge(char uname[], float money)
{

}

//支付，把log里所有当前用户的未支付的全部置为支付
void pay(char uname[])
{

}

//退货，倒着遍历log，退货数量上限是上一次购买的数量
void returnware(char uname[], char wid[], int quantity)
{

}




int main()
{
	char choice = -1;
	readallusersandadmins();
#if 0
	readallusers();
	login();
	promptregisteruser(0);
#endif
	while (choice != 'g')
	{
		printf("\n\t 超市管理系统");
		printf("\n\t 1---用户登录");
		printf("\n\t 2---注册消费者");
		printf("\n\t 3---注册管理员");
		printf("\n\t 4---用户登出");
		printf("\n\t 0---退出程序\n\n");
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
			promptregisteruser(0);
			break;
		case '3':
			printf("\n\n你选择了 2\n");
			promptregisteruser(1);
			break;
		case '4':
			printf("\n\n你选择了 2\n");
			logout();
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