#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FILE_STU "stu.txt"
typedef struct student
{
	char no[20];
	char name[20];
	int age;
	char sex[5];
	char birthday[20];
	char address[20];
	char telephone[20];
	char email[20];
}student;

student allstudents[100];
student sortstudents[100];
int allstudentscount = 0;

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

void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", stu.no, stu.name, stu.age, stu.sex,
		stu.birthday, stu.address, stu.telephone, stu.email);
	//printf("%s\t%s\t%d\n", stu.no, stu.name, stu.age);
}

int cmpstubyno(const void * a, const void * b)
{
	return ((student*)a)->no - ((student*)b)->no;
}

void displayallstudents()
{
	int i;
	qsort(allstudents, allstudentscount, sizeof(student), cmpstubyno);//快速排序
	printf("所有%d分数如下\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			stu.age = toint(part);
			break;
		case 4:
			strcpy(stu.sex, part);
			break;
		case 5:
			strcpy(stu.birthday, part);
			break;
		case 6:
			strcpy(stu.address, part);
			break;
		case 7:
			strcpy(stu.telephone, part);
			break;
		case 8:
			strcpy(stu.email, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
		return;
	else
	{

		allstudentscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allstudents[allstudentscount++] = getstudentfromline(line);
		}
		printf("\n已读入文件!", FILE_STU);
	}

}






void searcbyname(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("没找到对应学生的信息。\r\n");
}

void promptsearchbyname()
{
	char name[20];
	printf("请输入姓名:");
	scanf("%s", name);
	searcbyname(name);
}

void searchbyno(char no[20])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (streq(allstudents[i].no, no))
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("没找到对应学生的信息。\r\n");
}

void promptsearchbyno()
{
	char no[20];
	printf("请输入要查询的学号:");
	scanf("%s", no);
	searchbyno(no);
}

//输入成绩信息
void inputname(char str[])
{
	printf("请输入姓名(2-45个字符)，不能带空格、Tab或回车符:");
	scanf("%s", str);
	printf("您输入的姓名为为 %s \r\n", str);
}

int inputscore()
{
	int n = -1;
	while (n < 1 || n > 100)
	{
		printf("请输入分数1～100:");
		scanf("%d", &n);
	}
	return n;
}

void removestudent(char no[20])
{
	int i, index, found = 0;
	for (index = 0; index < allstudentscount; index++)
	{
		if (streq(allstudents[index].no, no))
		{
			found = 1;
			break;
		}
	}
	if (found)
	{
		for (i = index; i < allstudentscount - 1; i++)
			allstudents[i] = allstudents[i + 1];
		allstudentscount--;
		printf("删除完毕，剩下%d个。\n", allstudentscount);
	}
	else
	{
		printf("没找到，无法删除\n");

	}
}

void promptremove()
{
	char no[20];
	printf("请输入要删除的学号:");
	scanf("%s", no);
	removestudent(no);
}


void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_STU, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_STU);
		getchar();
		exit(1);
	}


	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		//fprintf(fp, "%s\t%s\t%d\n", stu.no, stu.name, stu.age);
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s\r\n", stu.no, stu.name, stu.age, stu.sex,
			stu.birthday, stu.address, stu.telephone, stu.email);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}


void addstudent(char no[20], char name[], int age, char sex[5],
	char birthday[20], char address[20], char telephone[20], char email[20])
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.age = age;
	strcpy(stu.sex, sex);
	strcpy(stu.birthday, birthday);
	strcpy(stu.address, address);
	strcpy(stu.telephone, telephone);
	strcpy(stu.email, email);
	allstudents[allstudentscount++] = stu;
}


void promptaddstudent()
{
	char no[20];
	char name[20];
	int age;
	char sex[5];
	char birthday[20];
	char address[20];
	char telephone[20];
	char email[20];


	printf("\n请输入学号，姓名，年龄，性别，出生年月，地址，电话，E-mail，空格隔开，回车结束\n");
	scanf("%s%s%d%s%s%s%s%s", no, name, &age, sex, birthday, address, telephone, email);
	addstudent(no, name, age, sex, birthday, address, telephone, email);
	printf("完成第%d个入库录入!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;
	readallstudents();

#if 0

	//addstudent("01", "name1", 1, "F", "b1", "add1", "tel1111", "1dsfsfs@ssss");
	//addstudent("03", "name3", 3, "F", "b3", "add3", "tel1333", "3dsfsfs@ssss");
	//addstudent("02", "name2", 2, "M", "b2", "add2", "tel2222", "2ddfdsfs@fsss");

	//displayallstudents();
	//promptaddstudent();

	///*promptremovestudent();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	//removestudent("03");
	//promptremovestudent();
	//promptsearchbyname();
	//promptsearchbyno();
	//displayallstudents();
	//searcbyname("name2");
	//searchbyno("033");
	//writeallstudents();

#else
	while (choice != 0)
	{
		printf("\n\t 学生信息管理系统");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 按学号升序输出所有学生信息");
		printf("\n\t 2. 添加学生信息");
		printf("\n\t 3. 按学号查询");
		printf("\n\t 4. 按姓名查询");
		printf("\n\t 5. 按学号删除");
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
			displayallstudents();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptaddstudent();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptsearchbyno();
			break;
		case '4':
			printf("\n\n你选择了 3\n");
			promptsearchbyname();
			break;
		case '5':
			printf("\n\n你选择了 3\n");
			promptremove();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
#endif
	printf("\n\n按任意键退出\n");
	system("pause");

	return 0;
}

