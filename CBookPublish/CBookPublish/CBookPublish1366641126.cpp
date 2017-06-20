//图书信息管理系统
//图书信息包括：图书编号、书名、作者名、出版单位、出版时间、价格等、试设计一图书信息管理系统，使之能提供以下功能：
//1.图书信息录入（图书信息用文件保存，并可在电脑上直接查找并打开该文件）
//2.图书信息浏览
//3.按作者名排序
//4.查询
//a.按出版单位查询
//b.按书名查询
//5.图书信息的删除
//5.图是信息的修改
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_BOOK "book.txt"
#define MAX_STRLEN 20
typedef struct book
{
	char id[20];
	char name[20];
	char author[10];
	char publisher[30];
	char publishdate[50];
	int price;
}book;

book allbooks[100];
int allbookscount = 0;

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


void displaybook(book b)
{
	printf("%s\t%8s%10s%16s%10s\t%d\n",
		b.id, b.name, b.author, b.publisher, b.publishdate, b.price);
}

int cmpfunc(const void * a, const void * b)
{
	return ((book*)a)->author - ((book*)b)->author;
}

void displayallbooks()
{
	int i;
	qsort(allbooks, allbookscount, sizeof(book), cmpfunc);
	printf("所有%d条图书信息如下\r\n", allbookscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allbookscount; i++)
	{
		displaybook(allbooks[i]);
	}
	printf("--------------------------------------------\r\n");
}

//从一行文本读入并根据\t符号拆分，组合成一个book
book getbookfromline(char *line)
{
	char *part;
	int index = 0;
	book b;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(b.id, part);
			break;
		case 2:
			strcpy(b.name, part);
			break;
		case 3:
			strcpy(b.author, part);
			break;
		case 4:
			strcpy(b.publisher, part);
			break;
		case 5:
			strcpy(b.publishdate, part);
			break;
		case 6:
			b.price = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return b;
}

void readallbooks()
{
	char line[200];
	FILE *fp = fopen(FILE_BOOK, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_BOOK);
	}
	else
	{
		allbookscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allbooks[allbookscount++] = getbookfromline(line);
		}
		printf("\n已读入文件!", FILE_BOOK);
	}
}


int getbookidexbyno(char id[50])
{
	int i;
	for (i = 0; i < allbookscount; i++)
	{
		if (streq(allbooks[i].id, id))
			return i;
	}
	return -1;//没找到
}

void writeallbooks()
{
	int i;
	book b;
	FILE *fp = fopen(FILE_BOOK, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_BOOK);
		getchar();
		exit(1);
	}
	for (i = 0; i < allbookscount; i++)
	{
		b = allbooks[i];
		fprintf(fp, "%s %s %s %s %s %d\n",
			b.id, b.name, b.author, b.publisher, b.publishdate, b.price);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void editbook(char id[50])
{
	int i;
	i = getbookidexbyno(id);
	if (i >= 0)
	{
		printf("\n请输入新的出版单位、出版时间、价格，空格隔开\n");
		scanf("%s%s%d", allbooks[i].publisher, allbooks[i].publishdate, &allbooks[i].price);
		writeallbooks();
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应图书编号号的图书。\r\n");
	}
}

void prompteditbook()
{
	char id[50];
	printf("请输入要修改的图书编号号:");
	scanf("%s", &id);
	editbook(id);
}

void addbook(char id[], char name[], char author[], char publisher[], char publishdate[], int price)
{
	book b;
	strcpy(b.id, id);
	strcpy(b.name, name);
	strcpy(b.author, author);
	strcpy(b.publisher, publisher);
	strcpy(b.publishdate, publishdate);
	b.price = price;
	allbooks[allbookscount++] = b;
	writeallbooks();
}


void promptaddbook()
{
	char id[20];
	char name[20];
	char author[10];
	int price;
	char publisher[30];
	char publishdate[50];
	char telephone[20];
	printf("\n请输入图书编号（不重复）:\n");
	scanf("%s", id);
	if (getbookidexbyno(id) >= 0)
	{
		printf("图书编号与已有图书重复！\n");
		return;
	}
	printf("\n请输入书名、作者名、出版单位、出版时间（都是不带空格的字符串）、价格(整数)，空格隔开\n");
	scanf("%s%s%s%s%d", name, author, publisher, publishdate, &price);
	addbook(id, name, author, publisher, publishdate, price);
	printf("完成第%d种图书录入!\r\n", allbookscount);
}


void removebook(char no[20])
{
	int i;
	int index;
	index = getbookidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allbookscount - 1; i++)
			allbooks[i] = allbooks[i + 1];
		allbookscount--;
		writeallbooks();
		printf("删除完毕，剩下%d个。\r\n", allbookscount);
	}
	else
	{
		printf("没找到对应图书编号号的图书。\r\n");
	}

}

void promptremovebook()
{
	char id[20];
	printf("请输入要删除的图书编号号:");
	scanf("%s", id);
	removebook(id);
}


void searchbyname(char name[20])
{
	int i, found = 0;
	for (i = 0; i < allbookscount; i++)
		if (strstr(allbooks[i].name, name) != NULL)
		{
			displaybook(allbooks[i]);
			found = 1;
		}
	if (!found)
		printf("没找到对应图书的信息。\r\n");
}

void promptsearchbyname()
{
	char name[20];
	printf("请输入要查找的书名:");
	scanf("%s", name);
	searchbyname(name);
}

void searchbypublisher(char publisher[20])
{
	int i, found = 0;
	for (i = 0; i < allbookscount; i++)
		if (strstr(allbooks[i].publisher, publisher) != NULL)
		{
			displaybook(allbooks[i]);
			found = 1;
		}
	if (!found)
		printf("没找到对应图书的信息。\r\n");
}

void promptsearchbypublisher()
{
	char publisher[20];
	printf("请输入要查找的出版社:");
	scanf("%s", publisher);
	searchbypublisher(publisher);
}

int main()
{
	char choice = -1;
#if 0//测试用，if块可删除
	readallbooks();
	//addbook("01", "三国演义", "罗贯中", "人民出版社", "1950-4-3", 99);
	//addbook("02", "C语言", "谭浩强", "机械出版社", "1995-12-1", 50);

	//editbook("01");
	////printf("\n%d\n", allbookscount);
	displayallbooks();
	//promptsearchbypublisher();
	promptsearchbyname();
	//prompteditbook();
	//promptremovebook();
	//promptaddbook();
	//promptsearchbyname();
	//writeallbooks();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	//sortbooksbytotalanddisplay();
	//displayallbooks();
	//sortbooksbytotal();
	//prompteditbook();
	////displayallbooks();


	system("pause");

#endif
	readallbooks();
	while (choice != 0)
	{
		printf("\n\t 图书信息管理系统");
		printf("\n\t 0---退出");
		printf("\n\t 1---图书信息录入");
		printf("\n\t 2---图书信息浏览");
		printf("\n\t 3---按出版单位查询");
		printf("\n\t 4---按书名查询");
		printf("\n\t 5---图书信息删除");
		printf("\n\t 6---图书信息修改");
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
			promptaddbook();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallbooks();
			break;
		case '3':
			printf("\n\n你选择了 c\n");
			promptsearchbypublisher();
			break;
		case '4':
			printf("\n\n你选择了 d\n");
			promptsearchbyname();
			break;
		case '5':
			printf("\n\n你选择了 e\n");
			promptremovebook();
			break;
		case '6':
			printf("\n\n你选择了 f\n");
			prompteditbook();
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

