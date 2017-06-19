//杂志订阅管理杂志订阅信息
//杂志代码  订阅户名  身份证号  订阅份数  单价  小计
//122          李平        4512245    2            5.5    11.0
//新增、修改、删除，并能按身份证号查找订阅户名情况，以及统计指定杂志的订阅份数。
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_per "magazine.txt"
#define MAX_STRLEN 20
typedef struct magazine
{
	char id[20];
	char name[20];
	char card[20];
	int quantity;
	float price;
	float total;
}magazine;

magazine allmagazines[100];
int allmagazinescount = 0;

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

void calctotal(magazine *m)
{
	m->total = m->price*m->quantity;
}

void displaymagazine(magazine m)
{
	printf("%s\t%s\t%s\t%d\t%.1f\t%.1f\n",
		m.id, m.name, m.card, m.quantity, m.price, m.total);
}



void displayallmagazines()
{
	int i;
	printf("所有%d位杂志订购信息信息如下\r\n", allmagazinescount);
	printf("%s\t%s\t%s\t%s\t%s\t%s\n",
		"代码", "户名", "身份证", "份数", "单价", "小计");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allmagazinescount; i++)
	{
		displaymagazine(allmagazines[i]);
	}
	printf("--------------------------------------------\r\n");
}

//从一行文本读入并根据\t符号拆分，组合成一个magazine
magazine getmagazinefromline(char *line)
{
	char *part;
	int index = 0;
	magazine m;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(m.id, part);
			break;
		case 2:
			strcpy(m.name, part);
			break;
		case 3:
			strcpy(m.card, part);
			break;
		case 4:
			m.quantity = toint(part);
			break;
		case 5:
			m.price = tofloat(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	calctotal(&m);
	return m;
}

void readallmagazines()
{
	char line[200];
	FILE *fp = fopen(FILE_per, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_per);
	}
	else
	{
		allmagazinescount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allmagazines[allmagazinescount++] = getmagazinefromline(line);
		}
		printf("\n已读入文件!", FILE_per);
	}
}





//根据编号查数组里的序号
int getmagazineidexbycard(char card[50])
{
	int i;
	for (i = 0; i < allmagazinescount; i++)
	{
		if (streq(allmagazines[i].card, card))
			return i;
	}
	return -1;//没找到
}

void writeallmagazines()
{
	int i;
	magazine m;
	FILE *fp = fopen(FILE_per, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_per);
		getchar();
		exit(1);
	}
	for (i = 0; i < allmagazinescount; i++)
	{
		m = allmagazines[i];
		fprintf(fp, "%s\t%s\t%s\t%d\t%.1f\n",
			m.id, m.name, m.card, m.quantity, m.price);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void editmagazine(char card[50])
{
	int i;
	i = getmagazineidexbycard(card);
	if (i >= 0)
	{
		printf("\n请输入新的订购数量、价格，空格隔开:");
		scanf("%d%f", &allmagazines[i].quantity, &allmagazines[i].price);
		calctotal(&allmagazines[i]);
		writeallmagazines();
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应身份证号的杂志订购信息。\r\n");
	}
}

void prompteditmagazine()
{
	char card[50];
	printf("请输入要修改的身份证号:");
	scanf("%s", &card);
	editmagazine(card);
}


void addmagazine(char id[], char name[], char card[], int quantity, float price)
{
	magazine m;
	strcpy(m.id, id);
	strcpy(m.name, name);
	strcpy(m.card, card);
	m.quantity = quantity;
	m.price = price;
	calctotal(&m);
	allmagazines[allmagazinescount++] = m;
	writeallmagazines();
}


void promptaddmagazine()
{
	char id[20];
	char name[20];
	char card[20];
	int quantity;
	float price;

	printf("\n请输入杂志代码  订阅户名  身份证号（都是不带空格的字符串） 订阅份数  单价，空格隔开\n");
	scanf("%s%s%s%d%f", id, name, card, &quantity, &price);
	addmagazine(id, name, card, quantity, price);
	printf("完成第%d条杂志订购信息录入!\r\n", allmagazinescount);
}


void removemagazine(char no[20])
{
	int i;
	int index;
	index = getmagazineidexbycard(no);
	if (index >= 0)
	{
		for (i = index; i < allmagazinescount - 1; i++)
			allmagazines[i] = allmagazines[i + 1];
		allmagazinescount--;
		writeallmagazines();
		printf("删除完毕，剩下%d条。\r\n", allmagazinescount);
	}
	else
	{
		printf("没找到对应身份证号的杂志订购信息。\r\n");
	}

}

void promptremovemagazine()
{
	char id[20];
	printf("请输入要删除的身份证号:");
	scanf("%s", id);
	removemagazine(id);
}


void searchbycard(char card[20])
{
	int i, found = 0;
	for (i = 0; i < allmagazinescount; i++)
		if (streq(allmagazines[i].card, card))
		{
			displaymagazine(allmagazines[i]);
			found = 1;
		}
	if (!found)
		printf("没找到对应杂志订购信息的信息。\r\n");
}

void promptsearchbycard()
{
	char card[20];
	printf("请输入要查找的订阅者的身份证号:");
	scanf("%s", card);
	searchbycard(card);
}

//
void gettotalquantitybyid(char id[20])
{
	int i, total = 0;
	for (i = 0; i < allmagazinescount; i++)
		if (streq(allmagazines[i].id, id))
		{
			total += allmagazines[i].quantity;
		}
	printf("编号%s的杂志订购总量为:%d\n", id, total);
}

void promptgettotalquantitybyid()
{
	char id[20];
	printf("请输入要查找的杂志的编号:");
	scanf("%s", id);
	gettotalquantitybyid(id);
}

//

int main()
{
	char choice = -1;
#if 0//测试用，if块可删除
	readallmagazines();
	//addmagazine("05", "n5", "20170605", 41, 92, 93);
	//addmagazine("06", "n6", "20170606", 46, 96, 96);

	//editmagazine("01");
	////printf("\n%d\n", allmagazinescount);
	displayallmagazines();
	promptgettotalquantitybyid();
	//promptaddmagazine();
	//prompteditmagazine();
	//promptremovemagazine();
	promptsearchbycard();
	//displayallmagazines();
	//promptsearchbetweenquantity();
	//writeallmagazines();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	//sortmagazinesbytotalanddisplay();
	//displayallmagazines();
	//sortmagazinesbytotal();
	//prompteditmagazine();
	//displayallmagazines();


	system("pause");

#endif
	readallmagazines();
	while (choice != 0)
	{
		printf("\n\t 杂志订购信息信息管理系统");
		printf("\n\t 0---退出");
		printf("\n\t 1---杂志订阅信息添加");
		printf("\n\t 2---杂志订阅信息修改");
		printf("\n\t 3---杂志订阅信息删除");
		printf("\n\t 4---查看所有杂志订阅信息");
		printf("\n\t 5---按身份证查询");
		printf("\n\t 6---按杂志编号统计");
		printf("\n请选择:");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0); break;
		case '1':
			printf("\n\n你选择了 1\n");
			promptaddmagazine();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			prompteditmagazine();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptremovemagazine(); 
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			displayallmagazines();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptsearchbycard();
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			promptgettotalquantitybyid();
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

