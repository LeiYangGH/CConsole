#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define FORMAT "%s\t%s\t%d\t%d\t%d\t%d\r\n"
#define MAX_STRLEN 20
#define QUESTIONS_COUNT 35
#define STUDENTS_COUNT 10
#define STU_MEMBERS_FULL stu.no, stu.name,  stu.score[0], stu.score[1], stu.score[2], stu.total
#define STU_MEMBERS_NET stu.no, stu.name,  stu.score[0], stu.score[1], stu.score[2], stu.total
typedef struct student
{
	char no[50];
	char name[50];
	int score[3];
	int total;
}student;

student allstudents[STUDENTS_COUNT];
int allstudentscount = 0;

//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

////字符串转整数
//int toint(char *s)
//{
//	char *end;
//	return (int)strtol(s, &end, 10);
//}

void displaystudent(student stu)
{
	printf("\r\n");
	printf(FORMAT, STU_MEMBERS_NET);
}

void displayallstudents()
{
	int i;
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}

//快速排序用
int cmpfunc(const void * a, const void * b)
{
	return ((student*)b)->total - ((student*)a)->total;
}

void sortanddisplay()
{
	int i;
	qsort(allstudents, allstudentscount, sizeof(student), cmpfunc);
	printf("按总成绩降序排序后如下\r\n");
	displayallstudents();
}

void countbygrades()
{
	int i, t, cnt270300 = 0, cnt240269 = 0, cnt210239 = 0, cnt180209 = 0, cnt150179 = 0, cnt149 = 0;
	student stu;
	printf("总成绩在各分值段的成绩比例及及格率统计如下：\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].total;
		if (t >= 270)
			cnt270300++;
		else if (t >= 240 && t <= 269)
			cnt240269++;
		else if (t >= 210 && t <= 239)
			cnt210239++;
		else if (t >= 180 && t <= 209)
			cnt180209++;
		else if (t >= 150 && t <= 179)
			cnt150179++;
		else if (t < 149)
			cnt149++;
	}
	printf("270~300\t240~269\t210~239\t180~209\t150~179\t149以下\t及格率\r\n");
	printf("%d\t%d\t%d\t%d\t%d\t%d\r\n",
		cnt270300, cnt240269, cnt210239, cnt180209, cnt150179, cnt149);
	//因为正好是10个人，所以百分比就是人数*10
	printf("%d%%\t%d%%\t%d%%\t%d%%\t%d%%\t%d%%\t%d%%\r\n",
		cnt270300 * 10, cnt240269 * 10, cnt210239 * 10, cnt180209 * 10, cnt150179 * 10, cnt149 * 10,
		(cnt270300 + cnt240269 + cnt210239 + cnt180209) * 10);
	printf("--------------------------------------------\r\n");
}

void calcminmaxave()
{
	int i, min = 300, max = 0, t;
	float sum = 0, ave;
	for (i = 0; i < allstudentscount; i++)
	{
		t = allstudents[i].total;
		sum += t;
		min = t < min ? t : min;
		max = t > max ? t : max;
	}
	ave = sum / STUDENTS_COUNT;
	printf("总成绩最高分：%d人, 最低分:%d人, 平均分:%f人\r\n",
		max, min, ave);
}

//void inputstring(char str[])
//{
//	int len = -1;
//	char input[50] = "";
//	while (len < 1 || len > MAX_STRLEN)
//	{
//		printf("请输入姓名:");
//		fseek(stdin, 0, SEEK_END);
//		scanf("%s", input);
//		len = strlen(input);
//	}
//	strcpy(str, input);
//}

void searchtotalbyname(char *name)
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

void promptsearchtotalbyname()
{
	char name[MAX_STRLEN] = "";
	printf("请输入要查询的学生姓名:");
	scanf("%s", &name);
	searchtotalbyname(name);
}

void searchtotalbyno(char no[])
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

void promptsearchtotalbyno()
{
	char no[MAX_STRLEN];
	printf("请输入要查询的学号:");
	scanf("%s", &no);
	searchtotalbyno(no);
}

void addstudent(char no[], char name[], int s0, int s1, int s2)
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.score[0] = s0;
	stu.score[1] = s1;
	stu.score[2] = s2;
	stu.total = s0 + s1 + s2;
	allstudents[allstudentscount++] = stu;
}

void createsamplestudents()
{
	printf("创建示例成绩数据...");
	addstudent("16001", "Smile", 93, 96, 91);
	addstudent("16002", "Shawn", 95, 85, 65);
	addstudent("16003", "Tony", 92, 82, 62);
	addstudent("16004", "Flex", 91, 81, 61);
	addstudent("16005", "Smile5", 63, 63, 66);
	addstudent("16006", "Smile6", 96, 83, 63);
	addstudent("16007", "Smile7", 93, 83, 56);
	addstudent("16008", "Smile8", 97, 83, 73);
	addstudent("16009", "Smile9", 55, 55, 58);
	addstudent("16010", "Smile10", 13, 13, 43);
	allstudentscount = 9;
	printf("9条示例成绩数据已创建。\n");

}

void promptaddstudent()
{
	char no[MAX_STRLEN];
	char name[MAX_STRLEN] = "";
	int s1, s2, s3;
	printf("\n请输入学号\n");
	scanf("%s", &no);
	printf("\n请输入用户名\n");
	scanf("%s", name);
	printf("\n请输入三科成绩（整数），空格隔开\n");
	scanf("%d%d%d", &s1, &s2, &s3);
	addstudent(no, name, s1, s2, s3);
	printf("完成第%d个入库录入!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;
	//createsamplestudents();
	//displayallstudents();
	//calcminmaxave();
	//countbygrades();
	//sortanddisplay();
	//system("pause");
	while (choice != 0)
	{
		printf("\n\t (如果按键回车后没反应，请再按一次)");
		printf("\n\t 学生成绩输入查询统计");
		printf("\n\t 0. 退出");
		printf("\n\t 1. 添加学生成绩");
		printf("\n\t 2. 计算最高最低平均");
		printf("\n\t 3. 分段比例和及格率");
		printf("\n\t 4. 按总分倒序排序");
		printf("\n\t 5. 根据学号查询");
		printf("\n\t 6. 根据姓名查询");
		printf("\n\t 7. 创建9条示例数据");
		printf("\n\n  请选择: ");
		scanf("%1[01234567]d%*c", &choice);
		choice = getche();
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
			calcminmaxave();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			countbygrades();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			sortanddisplay();
			break;
		case '5':
			printf("\n\n你选择了 5\n");
			promptsearchtotalbyno();
			break;
		case '6':
			printf("\n\n你选择了 6\n");
			promptsearchtotalbyname();
			break;
		case '7':
			printf("\n\n你选择了 7\n");
			createsamplestudents();
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}

