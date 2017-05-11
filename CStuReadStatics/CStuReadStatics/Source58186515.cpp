#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_INPUT "input.txt"
#define FILE_ALLOUTPUT "alloutput.txt"
#define FILE_GRADES "grades.txt"
#define MAX_STRLEN 20
#define COURSES_COUNT 5
#define GRADES_COUNT 5

typedef struct student
{
	char name[MAX_STRLEN];
	int score[COURSES_COUNT];
	float average;
	int order;
}student;
student allstudents[100];
int allstudentscount = 0;

typedef struct course
{
	int oldindex;
	float average;
	int countingrade[GRADES_COUNT];
}course;
course allcourses[COURSES_COUNT];


#define TEST 0
int cmpcourseindex;
//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

void displaystudent(student stu)
{
	printf("\r\n");
	printf("%s\t%d\t%d\t%d\t%d\t%d\t%.1f\t%d\n", stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
		stu.average, stu.order);
}

void displayallstudents()
{
	int i;
	printf("所有%d位同学分数如下\r\n", allstudentscount);
	printf("姓名\t科目1\t科目2\t科目3\t科目4\t科目5\t平均\t排名\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void displayonecourseorder()
{
	int i;
	printf("第%d科目分数如下\r\n", cmpcourseindex + 1);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		printf("\r\n");
		student stu = allstudents[i];
		printf("%s\t\%d\n", stu.name,
			stu.score[cmpcourseindex]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void displayallcoursesaveorder()
{
	int i;
	printf("所有科目平均分排序如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < COURSES_COUNT; i++)
	{
		printf("\r\n");
		course cou = allcourses[i];
		printf("第%d科\t\%.1f\n", cou.oldindex + 1,
			cou.average);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void writestudentsaveorder()
{
	int i;
	FILE *fp;
	fp = fopen(FILE_ALLOUTPUT, "w");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_ALLOUTPUT);
		getchar();
		exit(1);
	}
	fprintf(fp, "姓名\t科目1\t科目2\t科目3\t科目4\t科目5\t平均\t排名\n");
	for (i = 0; i < allstudentscount; i++)
	{
		student stu = allstudents[i];
		fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%d\t%.1f\t%d\n", stu.name,
			stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4],
			stu.average, stu.order);
	}
	fclose(fp);
	printf("学生综合成绩已输出到文件%s\n", FILE_ALLOUTPUT);
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
			strcpy(stu.name, part);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			stu.score[index - 2] = toint(part);
			break;

		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

void calctotalandave()
{
	int i, j;
	float sum = 0;
	for (i = 0; i < allstudentscount; i++)
	{
		sum = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			sum += allstudents[i].score[j];
		}
		allstudents[i].average = sum / (float)COURSES_COUNT;
	}
}


void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_INPUT, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_INPUT);
		getchar();
		exit(1);
	}
	allstudentscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		++allstudentscount;
		allstudents[allstudentscount - 1] = getstudentfromline(line);
	}
	calctotalandave();
}



int cmpstuavefunc(const void * a, const void * b)
{
	return (((student*)a)->average - ((student*)b)->average);
}
void sortstuave()
{
	int i;
	qsort(allstudents, allstudentscount, sizeof(student), cmpstuavefunc);
	allstudents[0].order = 1;
	for (i = 1; i < allstudentscount; i++)
	{
		if (allstudents[i].average == allstudents[i - 1].average)
			allstudents[i].order = allstudents[i - 1].order;
		else
			allstudents[i].order = allstudents[i - 1].order + 1;
	}
}

void countbygradesforonecourse(int courseindex)
{
	int i, t;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].score[courseindex];
		if (t < 60)
			allcourses[courseindex].countingrade[0]++;
		else if (t >= 60 && t <= 69)
			allcourses[courseindex].countingrade[1]++;
		else if (t >= 70 && t <= 79)
			allcourses[courseindex].countingrade[2]++;
		else if (t >= 80 && t <= 89)
			allcourses[courseindex].countingrade[3]++;
		else if (t >= 90)
			allcourses[courseindex].countingrade[4]++;
	}
}

void countbygradesforallcourses()
{
	int i;
	for (i = 0; i < COURSES_COUNT; i++)
	{
		countbygradesforonecourse(i);
	}
}


void writeandprintgradescount()
{
	int i, j;
	char *grades[GRADES_COUNT] = { "<60","60~69", "70~79", "80~89", ">=90", };
	FILE *fp;
	fp = fopen(FILE_GRADES, "w");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_GRADES);
		getchar();
		exit(1);
	}
	printf("分数段\t科目1\t科目2\t科目3\t科目4\t科目5\n");
	fprintf(fp, "分数段\t科目1\t科目2\t科目3\t科目4\t科目5\n");
	for (i = 0; i < GRADES_COUNT; i++)
	{
		printf("%s", grades[i]);
		fprintf(fp, "%s", grades[i]);
		for (j = 0; j < COURSES_COUNT; j++)
		{
			course cou = allcourses[j];
			printf("\t%d", cou.countingrade[i]);
			fprintf(fp, "\t%d", cou.countingrade[i]);
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("分数段已输出到文件%s\n", FILE_GRADES);
}

void displayallbelow60()
{
	int i, j, t;
	printf("所有不及格信息如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		for (j = 0; j < COURSES_COUNT; j++)
		{
			t = allstudents[i].score[j];
			if (t < 60)
			{
				printf("%s\t科目%d\t%d分\n",
					allstudents[i].name, j + 1, t);
			}
		}
	}
	printf("\r\n--------------------------------------------\r\n");
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
		fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%d\r\n", stu.name,
			stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

void addstudent(char no[], char name[], int s0, int s1, int s2, int s3, int s4)
{
	student stu;
	strcpy(stu.name, name);
	stu.score[0] = s0;
	stu.score[1] = s1;
	stu.score[2] = s2;
	stu.score[3] = s3;
	stu.score[4] = s4;
	allstudents[allstudentscount++] = stu;
	calctotalandave();
	writeallstudents();
}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3, s4, s5;
	printf("\n请输入学生姓名\n");
	scanf("%s", name);
	printf("\n请输入5科成绩（整数），空格隔开\n");
	scanf("%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5);
	addstudent(no, name, s1, s2, s3, s4, s5);
	printf("完成第%d个学生成绩录入!\r\n", allstudentscount);
}

int main()
{
#if TEST
	readallstudents();
	//sorttotal();
	//displayallstudents();
	ascending = -1;
	cmpcourseindex = 4;
	sortonecourse();
	displayonecourseorder();
#else

	int choice = -1;
	printf("\n开始读文件...\n");
	readallstudents();
	printf("\n读文件结束！\n");

	while (choice != 0)
	{
		printf("\n\t 学生成绩读入统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 综合成绩名次计算输出");
		printf("\n\t 2. 课程分段人数输出");
		printf("\n\t 3. 输出所有不及格");
		printf("\n\t 4. 添加学生成绩");
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
			sortstuave();
			displayallstudents();
			writestudentsaveorder();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			countbygradesforallcourses();
			writeandprintgradescount();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			displayallbelow60();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			promptaddstudent();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
	}
#endif
	system("pause");
	return 0;
}
