#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "stu.txt"
#define MAX_STRLEN 20
#define COURSES_COUNT 5

typedef struct student
{
	char no[MAX_STRLEN];//学号
	char name[MAX_STRLEN];//姓名
	int score[COURSES_COUNT];//分数
	int total;//总分
	float average;//平均
}student;
student allstudents[100];//所有学生
int allstudentscount = 0;//学生数量

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

void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n", stu.no, stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
}

//显示所有学生成绩
void displayallstudents()
{
	int i;
	printf("所有%d位同学分数如下:\r\n", allstudentscount);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
		"学号", "姓名", "语文", "数学", "英文", "体育", "艺术");
	printf("--------------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------------\r\n");
}

//从一行拆分构造出一个学生
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	part = strtok(line, "\t");//通过\t符号拆分不同分数
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
		case 4:
		case 5:
		case 6:
		case 7:
			stu.score[index - 3] = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

//计算总分和平均分
void calctotalandave()
{
	int i, j;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		allstudents[i].total = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			allstudents[i].total += allstudents[i].score[j];
		}
		allstudents[i].average = allstudents[i].total / (float)COURSES_COUNT;
	}
}

//读文件到学生数组
void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_INPUT, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_INPUT);
	}
	else
	{
		allstudentscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			++allstudentscount;
			allstudents[allstudentscount - 1] = getstudentfromline(line);
		}
	}

}

//提示输入要排序的科目
int promptaskcmpcourseindex()
{
	int courseid;
	printf("\n请输入要排序的课程序号(1~5)，以回车结束：");
	scanf("%d", &courseid);
	return courseid - 1;
}

void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_INPUT, "w+");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_INPUT);
		getchar();
		exit(1);
	}
	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\r\n", stu.no, stu.name,
			stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void addstudent(char no[], char name[], int s0, int s1, int s2, int s3, int s4)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.score[0] = s0;
	stu.score[1] = s1;
	stu.score[2] = s2;
	stu.score[3] = s3;
	stu.score[4] = s4;
	allstudents[allstudentscount++] = stu;
	writeallstudents();
}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3, s4, s5;
	printf("\n请输入要添加的学生学号、姓名，空格隔开\n");
	scanf("%s%s", no, name);
	printf("\n请输入5科成绩（整数），空格隔开\n");
	scanf("%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5);
	addstudent(no, name, s1, s2, s3, s4, s5);
	printf("完成第%d个学生成绩录入!\r\n", allstudentscount);
}

void calcdisplayhighlowave(int courseid)
{
	int i, t, h = 0, l = 100, sum = 0;
	float ave;
	int  below60stuindexes[20], belowcount = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score[courseid];
		h = h < t ? t : h;
		l = l > t ? t : l;
		sum += t;
		if (t < 60)
			below60stuindexes[belowcount++] = i;
	}
	ave = sum / (float)allstudentscount;
	printf("第%d门课程统计信息：\r\n", courseid + 1);
	printf("平均分:%.1f、最高分%d、最低分%d\n", ave, h, l);
	printf("补考名单:", ave, h, l);
	for (i = 0; i < belowcount; i++)
	{
		printf("%s\t", allstudents[below60stuindexes[i]].name);
	}
	printf("\n");
}

void calcdisplaybeststudetns()
{
	int i, j, below60courseexist;
	float ave;
	int  beststuindexes[20], bestcount = 0;

	calctotalandave();
	for (i = 0; i < allstudentscount; i++)
	{
		if (allstudents[i].average > 85)
		{
			below60courseexist = 0;
			for (j = 0; j < COURSES_COUNT; j++)
			{
				if (allstudents[i].score[j] < 60)
				{
					below60courseexist = 1;
					break;
				}
			}
			if (below60courseexist == 0)
			{
				beststuindexes[bestcount++] = i;
			}
		}
	}
	if (bestcount == 0)
		printf("奖学金获得者（平均分大于85而且没有不及格课程）:（没人）");
	else
	{
		printf("奖学金获得者（平均分大于85而且没有不及格课程）:");
		for (i = 0; i < bestcount; i++)
		{
			printf("%s\t", allstudents[beststuindexes[i]].name);
		}
	}
	printf("\n");
}

//根据编号查数组里的序号
int getstudentidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
	{
		if (streq(allstudents[i].no, no))
			return i;
	}
	return -1;//没找到
}

void editstudent(char no[50])
{
	int i;
	int s1, s2, s3, s4, s5;
	i = getstudentidexbyno(no);
	if (i >= 0)
	{
		printf("\n请输入5科成绩（整数），空格隔开\n");
		scanf("%d%d%d%d%d",
			&allstudents[i].score[0],
			&allstudents[i].score[1],
			&allstudents[i].score[2],
			&allstudents[i].score[3],
			&allstudents[i].score[4]);
		writeallstudents();
		printf("修改完毕。\r\n");
	}
	else
	{
		printf("没找到对应学号的学生。\r\n");
	}

}

void prompteditstudent()
{
	char no[50];
	printf("请输入要修改的学号:");
	scanf("%s", &no);
	editstudent(no);
}

void welcome()
{
	////////////////你自己加/////////////
	printf("-----------这里输入欢迎界面---------");
	getchar();
	system("cls");
}

int main()
{
	int choice = -1;
	welcome();
	readallstudents();
	while (choice != 0)
	{
		printf("\n\t 学生成绩读入统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 录入新记录");
		printf("\n\t 2. 显示所有记录");
		printf("\n\t 3. 修改分数");
		printf("\n\t 4. 按照单门课程统计、查询平均分、最高分、最低分、补考（不及格）学生名单");
		printf("\n\t 5. 获奖学金学生名单");
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
			promptaddstudent();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			displayallstudents();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			prompteditstudent();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			calcdisplayhighlowave(promptaskcmpcourseindex());
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			calcdisplaybeststudetns();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}

	system("pause");
	return 0;
}

