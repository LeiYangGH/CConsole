//C语言课程设计，用c语言设计一户籍管理系统，求所写代码要求:
//户籍信息包括身份证号、姓名、性别、年龄、学历、住址、电话等（身份证号不重复）。
//试设计一户籍管理系统，该系统具有如下功能：
//1. 户籍信息录入功能(户籍信息用文件保存，并可在电脑中直接查找并打开该文件）
//	2．户籍信息浏览功能
//	3．按年龄排序
//	4．按年龄区间查询
//	5．户籍信息删除
//	6．户籍信息修改

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_per "per.txt"
#define MAX_STRLEN 20
typedef struct person
{
	char id[20];
	char name[20];
	char sex[10];
	int age;
	char scholar[30];
	char address[50];
	char telephone[20];

}person;

person allpersons[100];
int allpersonscount = 0;

float averagechinese, averageage, averagescholar;

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


void displayperson(person per)
{
	printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\n", per.id, per.name, per.sex, per.age, per.scholar, per.address, per.telephone);
}

void displayallpersons()
{
	int i;
	printf("所有%d位居民信息如下\r\n", allpersonscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allpersonscount; i++)
	{
		displayperson(allpersons[i]);
	}
	printf("--------------------------------------------\r\n");
}

//从一行文本读入并根据\t符号拆分，组合成一个person
person getpersonfromline(char *line)
{
	char *part;
	int index = 0;
	person per;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(per.id, part);
			break;
		case 2:
			strcpy(per.name, part);
			break;
		case 3:
			strcpy(per.sex, part);
			break;
		case 4:
			per.age = toint(part);
			break;
		case 5:
			strcpy(per.scholar, part);
			break;
		case 6:
			strcpy(per.address, part);
			break;
		case 7:
			strcpy(per.telephone, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return per;
}

void readallpersons()
{
	char line[200];
	FILE *fp = fopen(FILE_per, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_per);
	}
	else
	{
		allpersonscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allpersons[allpersonscount++] = getpersonfromline(line);
		}
		printf("\n已读入文件!", FILE_per);
	}
}

//qsort是快速排序，要求如下写法，根据total排序
int cmpfunc(const void * a, const void * b)
{
	return ((person*)a)->age - ((person*)b)->age;
}
void sortpersonsbyage()
{
	qsort(allpersons, allpersonscount, sizeof(person), cmpfunc);
}

void sortpersonsbytotalanddisplay()
{
	int i;
	sortpersonsbyage();
	printf("按每个居民年龄排序后如下\r\n");
	displayallpersons();
}

//根据编号查数组里的序号
int getpersonidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allpersonscount; i++)
	{
		if (streq(allpersons[i].id, no))
			return i;
	}
	return -1;//没找到
}

void writeallpersons()
{
	int i;
	person per;
	FILE *fp = fopen(FILE_per, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_per);
		getchar();
		exit(1);
	}
	for (i = 0; i < allpersonscount; i++)
	{
		per = allpersons[i];
		fprintf(fp, "%s %s %s %d %s %s %s\n", per.id, per.name, per.sex, per.age, per.scholar, per.address, per.telephone);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void editperson(char no[50])
{
	int i;
	char pwd[20] = "";
	i = getpersonidexbyno(no);
	if (i >= 0)
	{
		printf("\n请输入新的学历、住址、电话（都是不带空格的字符串，尽量简短），空格隔开\n");
		scanf("%s%s%s", allpersons[i].scholar, allpersons[i].address, allpersons[i].telephone);
		writeallpersons();
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应身份证号的居民。\r\n");
	}
}

void prompteditperson()
{
	char no[50];
	printf("请输入要修改的身份证号:");
	scanf("%s", &no);
	editperson(no);
}

void addperson(char id[], char name[], char sex[], int age, char scholar[], char address[], char telephone[])
{
	person per;
	strcpy(per.id, id);
	strcpy(per.name, name);
	strcpy(per.sex, sex);
	per.age = age;
	strcpy(per.scholar, scholar);
	strcpy(per.address, address);
	strcpy(per.telephone, telephone);
	allpersons[allpersonscount++] = per;
	writeallpersons();
}


void promptaddperson()
{
	char id[20];
	char name[20];
	char sex[10];
	int age;
	char scholar[30];
	char address[50];
	char telephone[20];
	printf("\n请身份证（不重复）:\n");
	scanf("%s", id);
	if (getpersonidexbyno(id) >= 0)
	{
		printf("身份证与已有居民重复！\n");
		return;
	}
	printf("\n请输入姓名、性别（都是不带空格的字符串）、年龄(正整数)，空格隔开\n");
	scanf("%s%s%d", name, sex, &age);
	printf("\n请输入学历、住址、电话（都是不带空格的字符串，尽量简短），空格隔开\n");
	scanf("%s%s%s", scholar, address, telephone);
	addperson(id, name, sex, age, scholar, address, telephone);
	printf("完成第%d位居民录入!\r\n", allpersonscount);
}


void removeperson(char no[20])
{
	int i;
	int index;
	index = getpersonidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allpersonscount - 1; i++)
			allpersons[i] = allpersons[i + 1];
		allpersonscount--;
		writeallpersons();
		printf("删除完毕，剩下%d个。\r\n", allpersonscount);
	}
	else
	{
		printf("没找到对应身份证号的居民。\r\n");
	}

}

void promptremoveperson()
{
	char no[20];
	printf("请输入要删除的身份证号:");
	scanf("%s", no);
	removeperson(no);
}


void searcbetweenage(int from, int to)
{
	int i, found = 0;
	for (i = 0; i < allpersonscount; i++)
		if (allpersons[i].age >= from && allpersons[i].age <= to)
		{
			displayperson(allpersons[i]);
			found = 1;
		}
	if (!found)
		printf("没找到对应居民的信息。\r\n");
}

void promptsearchbetweenage()
{
	int from, to;
	printf("请输入要查找的最低和最高年龄(正整数，空格分隔):");
	scanf("%d%d", &from, &to);
	searcbetweenage(from, to);
}

int main()
{
	char choice = -1;
#if 1//测试用，if块可删除
	readallpersons();
	//addperson("05", "n5", "20170605", 41, 92, 93);
	//addperson("06", "n6", "20170606", 46, 96, 96);

	//editperson("01");
	////printf("\n%d\n", allpersonscount);
	displayallpersons();
	promptaddperson();
	displayallpersons();
	//promptsearchbetweenage();
	//prompteditperson();
	//writeallpersons();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();
	//promptremoveperson();
	//sortpersonsbytotalanddisplay();
	//displayallpersons();
	//sortpersonsbytotal();
	//prompteditperson();
	//displayallpersons();


	system("pause");

#endif
	readallpersons();
	while (choice != 'g')
	{
		printf("\n\t 居民信息管理系统");
		printf("\n\t 0---居民信息的创建");
		printf("\n\t 1---居民信息的排序");
		printf("\n\t 2---居民信息的增加");
		printf("\n\t 3---居民信息的删除");
		printf("\n\t 4---居民信息的修改");
		printf("\n\t 5---居民信息的查找");
		printf("\n\t 6---居民信息的浏览");
		printf("\n\t 7---退出\n\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n你选择了 0\n");
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			sortpersonsbytotalanddisplay();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptaddperson();
			break;
		case '3':
			printf("\n\n你选择了 c\n");
			promptremoveperson();
			break;
		case '4':
			printf("\n\n你选择了 d\n");
			prompteditperson();
			break;
		case '5':
			printf("\n\n你选择了 e\n");
			promptsearchbetweenage();
			break;
		case '6':
			printf("\n\n你选择了 f\n");
			displayallpersons();
			break;
		case '7':
			printf("\n\n 你选择了退出。");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
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

