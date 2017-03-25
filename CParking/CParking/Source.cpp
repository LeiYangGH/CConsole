#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define MAX_QUESTIONS_COUNT 98
#define PARK_FILE "park.txt"

#define TEST 1

typedef struct park
{
	char no[20];
	int intime;
	int outtime;
}park;
park allparks[20];
int allparkscount = 0;

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

void displaypark(park stu)
{
	printf("%s\t%d\t%d\r\n", stu.no, stu.intime, stu.outtime);
}

void displayallparks()
{
	int i;
	printf("所有%d车辆信息如下\r\n", allparkscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allparkscount; i++)
	{
		displaypark(allparks[i]);
	}
	printf("--------------------------------------------\r\n");
}

park getparkfromline(char *line)
{
	char *part;
	int index = 0;
	park q;
	part = strtok(line, "\t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.no, part);
			break;
		case 2:
			q.intime = toint(part);
			break;
		case 3:
			q.outtime = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t\n");
	}
	return q;
}


void readallparks()
{
	char line[200];
	FILE *fp = fopen(PARK_FILE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", PARK_FILE);
		getchar();
		exit(1);
	}
	allparkscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allparks[allparkscount++] = getparkfromline(line);
	}
	printf("\n已读入文件!\n");

}

void writeallparks(park re)
{
	int i;
	FILE *fp = fopen(PARK_FILE, "w");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", PARK_FILE);
		getchar();
		exit(1);
	}
	for (i = 0; i < allparkscount; i++)
	{
		park p = allparks[i];
		fprintf(fp, "%s\t%d\t%d\r\n", p.no, p.intime, p.outtime);
	}
	fclose(fp);
	printf("已保存到文件。");
}

int checkparkexists(char *no)
{
	int i;
	for (i = 0; i < allparkscount; i++)
	{
		if (streq(allparks[i].no, no))
		{
			return 1;
		}
	}
	return 0;
}

void addpark(char *no, int intime, int outtime)
{
	park re;
	char teamname[20] = "";
	//if (checkparkexists(name))
	//{
	//	printf("学生%s已存在不能重复添加。\n", name);
	//	return;
	//}
	strcpy(re.no, no);
	re.intime = intime;
	re.outtime = outtime;
	allparks[allparkscount++] = re;
	writeallparks(re);
}


//void promptaddpark()
//{
//	char no[20] = "";
//	char name[20] = "";
//	char idcard[20] = "";
//
//	printf("请依次输入要添加的学生考号、姓名、身份证号（都不带空格），空格隔开，回车结束:\n");
//	scanf("%s%s%s", no, name, idcard);
//	fseek(stdin, 0, SEEK_END);
//	addpark(no, name, idcard);
//}

void createsampleparks()
{
	FILE *fp = fopen(PARK_FILE, "w");
	char *format = "%s\t%d\t%d\r\n";
	printf("创建示例成绩数据...");
	if (fp == NULL)
	{
		printf("\nerror on open file!");
		getchar();
		exit(1);
	}
	fprintf(fp, format, "111", 1, 2);
	fprintf(fp, format, "222", 2, 4);
	fprintf(fp, format, "333", 3, 6);
	fprintf(fp, format, "444", 4, 8);
	fprintf(fp, format, "555", 5, 10);

	fclose(fp);
	printf("5条示例成绩数据已保存到park.txt。\n");
}
int main()
{
	createsampleparks();
	readallparks();
	displayallparks();
#if TEST
	;
#else


	char choice = ' ';
	readallparks();

	while (choice != 0)
	{
		printf("\n\n\t---考试系统---\n");
		printf("\t 1. 登录\n");
		printf("\t 2. 学生考试\n");
		printf("\t 3. 查看所有成绩\n");
		printf("\t 4. 添加考生信息\n");
		printf("\t 5. 添加考题\n");
		printf("\t 0. 退出");
		printf("\n\n 请选择: ");
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
			inputcountandexam();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			displayallresults();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptaddpark();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptaddquestion();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
			fseek(stdin, 0, SEEK_END);
			system("pause");
		}
	}
#endif // TEST

	system("pause");
	return 0;
}