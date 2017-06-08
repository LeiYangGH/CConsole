#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_USER "user.txt"//消费者文件
#define FILE_ADMIN "admin.txt"//管理员文件
#define FILE_WARE "ware.txt"//商品文件，可增删改查，下次运行exe时读入
#define FILE_LOG "log.txt"//购物记录文件，只提供一次性追加，下次运行exe时不读入
#pragma region typedef
typedef struct ware//商品
{
	char wid[20];//产品标识码
	char name[20];//名称
	char address[20];//产地
	float price;//单价
	int quantity;//库存
	int leastleft;//警告最低库存阈值
	int leastout;//警告最低库存阈值
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

log alllogs[10];
int alllogscount = 0;
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

#pragma region ware


void displayware(ware w)
{
	printf("%s\t%s\t%s\t%.1f\t%d\t%d\t%d\n",
		w.wid, w.name, w.address, w.price, w.quantity, w.leastleft, w.leastout);
}
//显示所有商品
void displayallwares()
{
	int i;
	printf("所有%d种商品信息如下\r\n", allwarescount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allwarescount; i++)
	{
		displayware(allwares[i]);
	}
	printf("--------------------------------------------\r\n");
}

//显示所有库存不足商品
void displaylowleftwares()
{
	int i;
	printf("库存不足商品信息如下\r\n", allwarescount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allwarescount; i++)
	{
		if (allwares[i].quantity < allwares[i].leastleft)
			displayware(allwares[i]);
	}
	printf("--------------------------------------------\r\n");
}

int getsoldquantity(char wid[])
{
	int i, sum = 0;
	for (i = 0; i < alllogscount; i++)
	{
		if (alllogs[i].paid)
			sum += alllogs[i].quantity;
	}
	return sum;
}

//显示所有销量不足商品
void displaylowoutwares()
{
	int i;
	printf("销量不足商品信息如下\r\n", allwarescount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allwarescount; i++)
	{
		if (getsoldquantity(allwares[i].wid) < allwares[i].leastout)
			displayware(allwares[i]);
	}
	printf("--------------------------------------------\r\n");
}

//从一行文本读入并根据\t符号拆分，组合成一个ware
ware getwarefromline(char *line)
{
	char *part;
	int index = 0;
	ware w;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(w.wid, part);
			break;
		case 2:
			strcpy(w.name, part);
			break;
		case 3:
			strcpy(w.address, part);
			break;
		case 4:
			w.price = tofloat(part);
			break;
		case 5:
			w.quantity = toint(part);
			break;
		case 6:
			w.leastleft = toint(part);
			break;
		case 7:
			w.leastout = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return w;
}

//读入所有商品
void readallwares()
{
	char line[200];
	FILE *fp = fopen(FILE_WARE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_WARE);
	}
	else
	{
		allwarescount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allwares[allwarescount++] = getwarefromline(line);
		}
		printf("\n已读入商品文件!");
	}
}


//根据商品识别码得出数组下标
int getwareidexbywid(char wid[20])
{
	int i;
	for (i = 0; i < allwarescount; i++)
	{
		ware w = allwares[i];
		if (streq(w.wid, wid))
			return i;
	}
	return -1;
}

//写所有商品信息到文件
void writeallwares()
{
	int i;
	ware w;
	FILE *fp = fopen(FILE_WARE, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_WARE);
		getchar();
		exit(1);
	}
	for (i = 0; i < allwarescount; i++)
	{
		w = allwares[i];
		fprintf(fp, "%s %s %s %.1f %d %d %d\n",
			w.wid, w.name, w.address, w.price, w.quantity, w.leastleft, w.leastout);
	}
	fclose(fp);
	printf("已保存记录到商品文件。");
}


//修改商品只允许修改价格和库存
void editware(char wid[50])
{
	int i;
	char pwd[20] = "";
	i = getwareidexbywid(wid);
	if (i >= 0)
	{
		printf("\n请输入新的价格（整数或浮点数）和库存（整数），空格隔开\n");
		scanf("%f%d", &allwares[i].price, &allwares[i].quantity);
		writeallwares();
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应识别码的商品。\r\n");
	}
}

void prompteditware()
{
	char wid[50];
	printf("请输入要修改的识别码:");
	scanf("%s", &wid);
	editware(wid);
}

////添加商品
void addware(char wid[20], char wname[], char address[],
	float price, int quantity, int leastleft, int leastout)
{
	ware w;
	strcpy(w.wid, wid);
	strcpy(w.name, wname);
	strcpy(w.address, address);
	w.price = price;
	w.quantity = quantity;
	w.leastleft = leastleft;
	w.leastout = leastout;
	allwares[allwarescount++] = w;
	writeallwares();
}

//是否已经存在相同商品
int iswarewidexists(char wid[20])
{
	int i;
	for (i = 0; i < allwarescount; i++)
	{
		if (streq(wid, allwares[i].wid))
			return 1;
	}
	return 0;
}



void promptaddware()
{
	char wid[20];//产品标识码
	char wname[20];//名称
	char address[20];//产地
	float price;//单价
	int quantity;//库存
	int leastleft;//警告最低库存阈值
	int leastout;//警告最低库存阈值
	printf("\n请输入商品识别码:\n");
	scanf("%s", wid);
	if (iswarewidexists(wid))
	{
		printf("识别码%s已经存在，不能重复添加商品!", wid);
		return;
	}
	printf("\n请输入商品名称、产地（都是不带空格的字符串），空格隔开\n");
	scanf("%s%s", wname, address);
	printf("\n单价（整数或浮点数）、库存、警告库存下限和销量下限（都是整数），空格隔开\n");
	scanf("%f%d%d%d", &price, &quantity, &leastleft, &leastout);
	addware(wid, wname, address, price, quantity, leastleft, leastout);
	printf("完成第%d种商品录入!\r\n", allwarescount);
}

//删除商品
void removeware(char no[20])
{
	int i;
	int index;
	index = getwareidexbywid(no);
	if (index >= 0)
	{
		for (i = index; i < allwarescount - 1; i++)
			allwares[i] = allwares[i + 1];
		allwarescount--;
		writeallwares();
		printf("删除完毕，剩下%d种商品。\r\n", allwarescount);
	}
	else
	{
		printf("没找到对应识别码的商品。\r\n");
	}

}

void promptremoveware()
{
	char no[20];
	printf("请输入要删除的商品的识别码:");
	scanf("%s", no);
	removeware(no);
}

//通过名称查找商品
void searchwarebyname(char *name)
{
	int i;
	for (i = 0; i < allwarescount; i++)
		if (strcmp(name, allwares[i].name) == 0)
		{
			displayware(allwares[i]);
			return;
		}
	printf("没找到对应商品的信息。\r\n");
}
//用户输入名称并查找商品信息
void promptsearchbyname()
{
	char name[20];
	printf("请输入要查找的商品名称:");
	scanf("%s", name);
	searchwarebyname(name);
}


#pragma endregion
//写所有购物记录
void writealllogs()
{
	int i;
	char choice;
	log l;
	FILE *fp;
	printf("即将往%s追加购买记录，注意最好在程序结束前一次性追加，否则多次追加会有重复记录。\n按y继续，其他键取消：", FILE_LOG);
	fseek(stdin, 0, SEEK_END);
	choice = getchar();
	if (choice != 'y')
	{
		printf("已取消!");
		return;
	}
	fp = fopen(FILE_LOG, "a");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_LOG);
		getchar();
		exit(1);
	}
	for (i = 0; i < allwarescount; i++)
	{
		l = alllogs[i];
		fprintf(fp, "%s %s %s %.1f %d %d %d\n",
			l.uname, l.wid, l.quantity, l.paid);
	}
	fclose(fp);
	printf("已保存记录到商品文件。");
}

void addlog(char uname[], char wid[], int quantity, int paid)
{
	log l;
	strcpy(l.uname, uname);
	strcpy(l.wid, wid);
	l.quantity = quantity;
	l.paid = paid;
	alllogs[alllogscount++] = l;
}

//加购物车，log里加
void addtocart(char uname[], char wid[], int quantity)
{
	int i, found = 0;//found:此消费者的购物车里有相同物品，则只加数量
	for (i = alllogscount - 1; i >= 0; i--)
		if (streq(alllogs[i].uname, uname)
			&& streq(alllogs[i].wid, wid)
			&& alllogs[i].paid == 0)
		{
			alllogs[i].quantity += quantity;
			found = 1;
			break;
		}
	if (!found)//没有找到则添加新商品
	{
		addlog(uname, wid, quantity, 0);
	}
}

//扣除库存，库存不足则返回0
int deductwareleft(char wid[], int quantity)
{
	int index = getwareidexbywid(wid);
	if (index < 0)//不可能运行到这行
	{
		printf("没找到识别码为%d的商品！\n", wid);
		return 0;
	}
	if (allwares[index].quantity >= quantity)
	{
		allwares[index].quantity -= quantity;
		return 1;
	}
	else
	{
		printf("商品%s库存为%d，库存不足！\n", allwares[index].name, allwares[index].quantity);
		return 0;
	}
}

void promptaddtocart(char uname[])
{
	char wid[20];
	int windex, quantity;
	printf("尊敬的客户%s，请输入加入购物车的商品识别码:", uname);
	scanf("%s", wid);
	windex = getwareidexbywid(wid);
	if (windex < 0)
	{
		printf("尊敬的客户%s，您输入的商品识别码找不到，请检查后重新输入，谢谢。", uname);
		return;
	}
	printf("尊敬的客户%s，请输入要购买的%s的数量（整数）:", uname, allwares[windex].name);
	scanf("%d", &quantity);
	if (deductwareleft(wid, quantity))
	{
		printf("尊敬的客户%s，您要购买的产品%s数量%d成功添加到购物车!", uname, allwares[windex].name, quantity);
	}
}


int recharge(char uname[], int money)
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(allusers[i].name, uname))
		{
			allusers[i].money += money;
			printf("尊敬的客户%s，已为您充值成功，当余额为%d元！\n", uname, allusers[i].money);
			return 1;
		}
	}
	return 0;
}

//充值，假定uname一定是消费者
void promptrecharge()
{
	int i, money;
	printf("尊敬的客户%s，您好！请输入要充值的金额（正整数）:", currentusername);
	scanf("%d", &money);
	if (recharge(currentusername, money))
		printf("尊敬的客户%s，已为您充值成功，当余额为%d元！\n", currentusername, allusers[i].money);
}



//扣除余额，余额不足则返回0
int deductusermoney(char uname[], float money)
{
	int index = getuseridexbyuname(uname);
	if (index < 0)//不可能运行到这行
	{
		printf("没找到用户名为%d的消费者！\n", uname);
		return 0;
	}
	if (allusers[index].money >= money)
	{
		allusers[index].money -= money;
		return 1;
	}
	else
	{
		printf("尊敬的客户%s，抱歉，您余额为%.1f，余额不足！\n", allusers[index].name, allusers[index].money);
		return 0;
	}
}

int getlatestlogidbyuserwareandpaid(char uname[], char wid[], int paid)
{
	int i;
	for (i = alllogscount - 1; i >= 0; i--)
		if (streq(alllogs[i].uname, uname)
			&& streq(alllogs[i].wid, wid)
			&& alllogs[i].paid == paid)
		{
			return i;
		}
	return -1;
}

float showcarttouser(char uname[])
{
	int i, windex;
	float multiple, total = 0;

	printf("尊敬的客户%s，您的购物车商品信息如下\r\n", uname);
	printf("商品\t单价\t数量\t总价\n");
	printf("--------------------------------------------\n");
	for (i = 0; i < alllogscount; i++)
		if (streq(alllogs[i].uname, uname)
			&& alllogs[i].paid == 0)
		{
			windex = getwareidexbywid(alllogs[i].wid);
			ware w = allwares[windex];
			multiple = w.price* alllogs[i].quantity;
			total += multiple;
			printf("%s\t%.1f\t%d\t%.1f\n，\n",
				w.name, w.price, alllogs[i].quantity, multiple);
		}
	printf("--------------------------------------------\n");
	printf("总应付金额：%.1f\n", total);
	return total;
}

//支付，把log里所有当前用户的未支付的全部置为支付
void pay(char uname[])
{
	int i, found = 0;//found:此消费者的购物车里有（未支付）商品
	float total = showcarttouser(uname);
	if (deductusermoney(uname, total))
	{
		//所有相关查找都可以算法优化，
		//因为每次都要求购物车里的商品全部支付，
		//因此一旦遍历到已经支付的就不用再继续了，
		//此处没优化
		for (i = alllogscount - 1; i >= 0; i--)
			if (streq(alllogs[i].uname, uname)
				&& alllogs[i].paid == 0)
			{
				alllogs[i].paid = 1;
			}
		printf("尊敬的客户%s，付款成功，欢迎您下次光临！\n", uname);
	}
}

//能退货的数量，倒着遍历log，退货数量上限是上一次购买的数量
int maxquantitycanreturn(char uname[], char wid[])
{
	int index = getlatestlogidbyuserwareandpaid(uname, wid, 1);
	if (index >= 0)
		return alllogs[index].quantity;
	else
		return 0;
}

int returnware(char uname[], char wid[], int quantity)
{
	int i;
	log l;
	int windex = getwareidexbywid(wid);
	if (quantity > maxquantitycanreturn(uname, wid))
	{
		printf("尊敬的客户%s，您要退货的商品数量大于最近一次购买的数量，退货失败！\n", uname);
		return 0;
	}
	//退货是购买的逆操作，因此余额和库存都加去负数
	deductusermoney(uname, -allwares[windex].price*quantity);
	deductwareleft(wid, -quantity);
	//退货操作也加入历史记录，因为影响用户癖好
	addlog(uname, wid, -quantity, 1);
	return 1;
}

void promptreturnware(char uname[])
{
	char wid[20];
	int windex, quantity;
	printf("尊敬的客户%s，请输入退货的商品识别码:", uname);
	scanf("%s", wid);
	windex = getwareidexbywid(wid);
	if (windex < 0)
	{
		printf("尊敬的客户%s，您输入的商品识别码找不到，请检查后重新输入，谢谢。", uname);
		return;
	}
	printf("尊敬的客户%s，请输入要退货的%s的数量（整数）:", uname, allwares[windex].name);
	scanf("%d", &quantity);
	if (returnware(uname, wid, quantity))
	{
		printf("尊敬的客户%s，退货成功，本店会努力以最好的商品报答您的支持!", uname);
	}
}


int main()
{
	char choice = -1;
	readallusersandadmins();
	readallwares();
#if 0
	readallusers();
	login();
	promptregisteruser(0);
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
			displayallwares();
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			promptsearchbyname();
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			promptaddware();
			break;
		case '8':
			printf("\n\n你选择了 8\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			prompteditware();
			break;
		case '9':
			printf("\n\n你选择了 9\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			promptremoveware();
			break;
		case 'a':
			printf("\n\n你选择了 a\n");
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			displaylowleftwares();
			displaylowoutwares();
			break;
		case 'b':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			promptaddtocart(currentusername);
			break;
		case 'c':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			pay(currentusername);
			break;
		case 'd':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			promptrecharge();
			break;
		case 'e':
			if (!iscurrentuserconsumer())
			{
				printf("当前用户%s不是消费者，没有权限操作!", currentusername);
				break;
			}
			promptreturnware(currentusername);
			break;
		case 'f':
			if (!iscurrentuseradmin())
			{
				printf("当前用户%s不是管理员，没有权限操作!", currentusername);
				break;
			}
			writealllogs();
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