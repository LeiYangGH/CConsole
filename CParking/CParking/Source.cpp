#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define PARK_FILE "park.txt"

int price = 5;//每小时费用
typedef struct park
{
	char no[20];
	int intime;
	int outtime;
}park;
park allparks[50];
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

int checktimevalid(int t)
{
	if (t > 0 && t < 24)
		return 1;
	else
	{
		printf("时间只能限制在1～23之间的整数！\n");
		return 0;
	}
}

int calcmoney(park p)
{
	if (p.outtime > p.intime)
		return price*(p.outtime - p.intime);
	else
		return 0;
}

void displaypark(park stu)
{
	printf("%8s\t%d\t%d\t%d元\r\n", stu.no, stu.intime, stu.outtime, calcmoney(stu));
}

void displayallparks()
{
	int i;
	printf("所有%d辆车信息如下\r\n", allparkscount);
	printf("车牌号\t进入\t离开\t费用\n");
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

void createsampleparks()
{
	char *format = "%s\t%d\t%d\r\n";
	FILE *fp;
	fp = fopen(PARK_FILE, "r");
	if (fp != NULL)
		return;
	fp = fopen(PARK_FILE, "w");
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
	allparkscount = 5;
	fclose(fp);
	printf("5条示例成绩数据已保存到park.txt。\n");
}

void readallparks()
{
	char line[200];
	FILE *fp = fopen(PARK_FILE, "r");
	if (fp == NULL)
	{
		exit(0);
		return;
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

void writeallparks()
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

int getparkindexbyno(char *no)
{
	int i;
	for (i = 0; i < allparkscount; i++)
	{
		if (streq(allparks[i].no, no))
		{
			return i;
		}
	}
	return -1;
}

int checkparkinexists(char *no)
{
	int i;
	for (i = 0; i < allparkscount; i++)
	{
		if (streq(allparks[i].no, no) && allparks[i].intime > 0)
		{
			return 1;
		}
	}
	return 0;
}

int checkparkoutexists(char *no)
{
	int i;
	for (i = 0; i < allparkscount; i++)
	{
		if (streq(allparks[i].no, no) && allparks[i].outtime > 0)
		{
			return 1;
		}
	}
	return 0;
}

void addparkin(char *no, int intime)
{
	int i, index;
	park p;
	index = getparkindexbyno(no);
	if (index >= 0)
	{
		if (checkparkinexists(no))
		{
			printf("车牌%s已经进入，不能再次登记！\n", no);
		}
		else
		{
			if (checktimevalid(intime))
			{
				allparks[index].intime = intime;
				writeallparks();
			}
		}
	}
	else
	{
		strcpy(p.no, no);
		p.intime = intime;
		p.outtime = 0;
		allparks[allparkscount++] = p;
		writeallparks();
	}
}


void promptaddparkin()
{
	char no[20] = "";
	int intime = 0;
	printf("请依次输入要进入的车牌号和时间(1-23)，空格隔开，回车结束:\n");
	scanf("%s%d", no, &intime);
	fseek(stdin, 0, SEEK_END);
	addparkin(no, intime);
}

void addparkout(char *no, int outtime)
{
	int i, index;
	index = getparkindexbyno(no);
	if (index >= 0)
	{
		if (checkparkoutexists(no))
			printf("车牌%s已经登记过离开，不能再次登记！\n", no);
		else
		{
			if (allparks[index].intime < outtime)
			{
				if (checktimevalid(outtime))
				{
					allparks[index].outtime = outtime;
					writeallparks();
				}
			}
			else
				printf("车牌%s于%d点进入，离开时间必须晚于进入时间！\n", no, allparks[i].intime);
		}
	}
	else
		printf("车牌%s还未登记进入，不能登记离开！\n", no);
}


void promptaddparkout()
{
	char no[20] = "";
	int outtime = 0;
	printf("请依次输入要离开的车牌号和时间(1-23)，空格隔开，回车结束:\n");
	scanf("%s%d", no, &outtime);
	fseek(stdin, 0, SEEK_END);
	addparkout(no, outtime);
}

void editpark(char *no, char *newno)
{
	char c;
	int i, index;
	index = getparkindexbyno(no);
	if (index >= 0)
	{
		if (streq(no, newno))
			printf("要修改的车牌号和原来相同，不用修改。");
		else
		{
			strcpy(allparks[index].no, newno);
			writeallparks();
			printf("成功修改车牌%s为%s相关信息。\n", no, newno);
		}
	}
	else
		printf("车牌%s还未登记！\n", no);
}


void prompteditpark()
{
	char no[20] = "";
	char newno[20] = "";
	printf("请依次输入要修改的车牌号和新车牌号，空格隔开，回车结束:\n");
	scanf("%s%s", no, newno);
	fseek(stdin, 0, SEEK_END);
	editpark(no, newno);
}
//--
void findpark(char *no)
{
	char c;
	park p;
	int i, index;
	index = getparkindexbyno(no);
	if (index >= 0)
	{
		p = allparks[index];
		if (p.outtime > 0)
			printf("查找到：车牌%s，%d点进入，%d点离开，停车费%d元。\n", p.no, p.intime, p.outtime, calcmoney(p));
		else
			printf("查找到：车牌%s，%d点进入，还未离开。\n", p.no, p.intime);
	}
	else
		printf("车牌%s还未登记！\n", no);
}


void promptfindpark()
{
	char no[20] = "";
	printf("请输入要查找的车牌号:");
	scanf("%s", no);
	fseek(stdin, 0, SEEK_END);
	findpark(no);
}
//

void deletepark(char *no)
{
	char c;
	int i, index;
	index = getparkindexbyno(no);
	if (index >= 0)
	{
		printf("真的要删除车牌%s相关信息吗？y/n\n", no);
		c = getchar();
		fseek(stdin, 0, SEEK_END);
		if (c == 'y' || c == 'Y')
		{
			for (i = index; i < allparkscount - 1; i++)
				allparks[i] = allparks[i + 1];
			allparkscount--;
			writeallparks();
			printf("成功删除车牌%s相关信息。\n", no);
		}
	}
	else
		printf("车牌%s还未登记！\n", no);
}


void promptdeletepark()
{
	char no[20] = "";
	printf("请输入要删除的车牌号:");
	scanf("%s", no);
	fseek(stdin, 0, SEEK_END);
	deletepark(no);
}


int main()
{
	char choice = ' ';
	createsampleparks();
	readallparks();
	while (choice != 0)
	{
		printf("\n\n\t---停车收费管理系统---\n");
		printf("\t 1. 添加停车进入\n");
		printf("\t 2. 添加停车离开\n");
		printf("\t 3. 删除停车信息\n");
		printf("\t 4. 修改车牌号\n");
		printf("\t 5. 查看所有停车信息\n");
		printf("\t 6. 查看某辆车信息\n");
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
			promptaddparkin();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			promptaddparkout();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptdeletepark();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			prompteditpark();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			displayallparks();
			break;
		case '6':
			printf("\n\n你选择了 5\n");
			promptfindpark();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
			fseek(stdin, 0, SEEK_END);
			system("pause");
		}
	}
	system("pause");
	return 0;
}