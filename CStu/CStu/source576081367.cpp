#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STRLEN 20
#define STUDENTS_COUNT 6
#define COURSES_COUNT 5
#define GRADES_COUNT 5

typedef struct student
{
	char no[MAX_STRLEN];// 学号
	char name[MAX_STRLEN];//姓名
	int score[COURSES_COUNT];//分数
	int total;//总分
	float average;//平均
}student;
student allstudents[6];//所有学生
int allstudentscount = 0;//学生数量

typedef struct calcstudent
{
	int highest;//最高
	int lowest;//最低
	int total;//总分
	float average;//平均

}calcstudent;
calcstudent allcalcstudents[6];//所有学生


typedef struct course//课程
{
	int highest;
	int lowest;
	int total;
	float average;
}course;
course allcourses[COURSES_COUNT];//5门课程
char *coursenames[MAX_STRLEN] = { "语文","数学", "英文", "体育", "艺术" };

//显示一个学生成绩
void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n", stu.no, stu.name,
		stu.score[0], stu.score[1], stu.score[2], stu.score[3], stu.score[4]);
}

//显示所有学生成绩
void displayallstudents()
{
	int i;
	printf("所有%d位同学分数如下\r\n", allstudentscount);
	printf("%s\t%s\t%s\t%s\t%s\n", "语文", "数学", "英文", "体育", "艺术");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("\r\n--------------------------------------------\r\n");
}

//科目平均分排序
int cmpstubyonecourse(const void * a, const void * b)
{
	return (int)(((student*)a)->score[0] - ((student*)b)->score[0]);
}
//1
void displaystudentonecourse(student stu, int courseid)
{
	printf("%s\t%s\t%d\n", stu.no, stu.name, stu.score[courseid]);
}

//显示所有学生成绩
void displayonecoursesort()
{
	int i;
	printf("\n\n选取第一科成绩从小到大排序，输出学号，姓名，成绩\r\n", allstudentscount);
	printf("%s\t%s\t%d\n", "学号", "姓名", "成绩");
	qsort(allstudents, STUDENTS_COUNT, sizeof(student), cmpstubyonecourse);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudentonecourse(allstudents[i], 0);
	}
	printf("\r\n--------------------------------------------\r\n");
}
//2


//显示所有学生成绩
void displayallcalcstudents()
{
	int i;
	printf("计算每个人的最高成绩，最低成绩，平均成绩\r\n");
	printf("%s\t%s\t%s\t%s\n", "姓名", "最高", "最低", "平均");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < STUDENTS_COUNT; i++)
	{
		calcstudent stu = allcalcstudents[i];
		printf("%s\t%d\t%d\t%.1f\n", allstudents[i].name,
			stu.highest, stu.lowest, stu.average);
	}
	printf("\r\n--------------------------------------------\r\n");
}

void calchighlowave()
{
	int i, t, j, h, l, sum;
	float ave;
	for (i = 0; i < STUDENTS_COUNT; i++)
	{
		h = 0, l = 100, sum = 0;
		for (j = 0; j < COURSES_COUNT; j++)
		{
			t = allstudents[i].score[j];
			h = h < t ? t : h;
			l = l > t ? t : l;
			sum += t;
		}
		ave = sum / (float)COURSES_COUNT;
		allcalcstudents[i].highest = h;
		allcalcstudents[i].lowest = l;
		allcalcstudents[i].total = sum;
		allcalcstudents[i].average = ave;
	}
}

void calchighlowaveanddisplay()
{
	calchighlowave();
	displayallcalcstudents();
}

//显示所有科目平均分排序
void displayallcourses()
{
	int i;
	printf("计算每科成绩中的最高成绩，最低成绩，平均成绩\r\n");
	printf("%s\t%s\t%s\t%s\n", "科目", "最高", "最低", "平均");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < COURSES_COUNT; i++)
	{
		course cou = allcourses[i];
		printf("%s\t%d\t%d\t%.1f\n", coursenames[i],
			cou.highest, cou.lowest, cou.average);
	}
	printf("\r\n--------------------------------------------\r\n");
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

//计算每个科目的平均分
void calccoursesanddisplay()
{
	int i, t, j, h, l, sum;
	float ave;
	for (j = 0; j < COURSES_COUNT; j++)
	{
		h = 0, l = 100, sum = 0;

		for (i = 0; i < STUDENTS_COUNT; i++)
		{
			t = allstudents[i].score[j];
			h = h < t ? t : h;
			l = l > t ? t : l;
			sum += t;
		}
		ave = sum / (float)STUDENTS_COUNT;
		allcourses[j].highest = h;
		allcourses[j].lowest = l;
		allcourses[j].total = sum;
		allcourses[j].average = ave;
	}
	displayallcourses();
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
	calctotalandave();
}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3, s4, s5;
	printf("\n请输入学生学号、姓名，空格隔开\n");
	scanf("%s%s", no, name);
	printf("\n请输入5科成绩（整数），空格隔开\n");
	scanf("%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5);
	addstudent(no, name, s1, s2, s3, s4, s5);
	printf("完成第%d个学生成绩录入!\r\n", allstudentscount);
}

//查找姓名
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
//用户输入并查找姓名
void promptsearchbyname()
{
	char name[20];
	printf("请输入姓名:");
	scanf("%s", name);
	printf("%s\t%s\t%s\t%s\t%s\n", "语文", "数学", "英文", "体育", "艺术");
	searcbyname(name);
}

void displaystudentsgrade()
{
	int i, gradeindex;
	float ave;
	calchighlowave();

	char *grades[GRADES_COUNT] = { "不及格(0～59)","及格(60～69)", "中等(70～79)", "良好(80～89)", "优秀(90～100)", };
	printf("按平均成绩计算每人的优，良，中，及格，不及格\r\n");
	printf("%s\t%s\t%s\n", "姓名", "平均分", "等级");
	for (i = 0; i < allstudentscount; i++)
	{
		ave = allstudents[i].average;
		if (ave < 60)
			gradeindex = 0;
		else if (ave >= 60 && ave <= 69)
			gradeindex = 1;
		else if (ave >= 70 && ave <= 79)
			gradeindex = 2;
		else if (ave >= 80 && ave <= 89)
			gradeindex = 3;
		else if (ave >= 90)
			gradeindex = 4;
		printf("%s\t%.1f\t%s\n", allstudents[i].name, ave, grades[gradeindex]);
	}
}

int main()
{
	int choice = -1;

	addstudent("04", "n4", 41, 42, 43, 44, 45);
	addstudent("01", "n1", 11, 12, 13, 14, 15);
	addstudent("02", "n2", 21, 22, 23, 24, 25);
	addstudent("06", "n6", 61, 62, 63, 64, 65);
	addstudent("03", "n3", 31, 32, 33, 34, 35);
	//addstudent("05", "n5", 51, 52, 53, 54, 55);

#if 0
	addstudent("05", "n5", 51, 52, 53, 54, 55);

	//displayallstudents();
	//calchighlowaveanddisplay();
	//calccoursesanddisplay();
	//searcbyname("n1");
	//displayonecoursesort();
	//displaystudentsgrade();
	//system("pause");
#endif
	printf("已自动添加5名学生成绩，请再添加1名学生成绩（为了方便测试，交作业的时候可以修改代码为全部重新输入）\n");
	promptaddstudent();
	displayallstudents();
	calchighlowaveanddisplay();
	calccoursesanddisplay();
	displaystudentsgrade();
	displayonecoursesort();
	printf("输入（用scanf）查询每个人各项成绩信息\n");
	promptsearchbyname();
	system("pause");
	return 0;
}

