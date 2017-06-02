#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define USE_QUESTIONS_COUNT 3
#define FILE_SEL "file1.txt"
#define FILE_TF "file2.txt"
#define FILE_SCORE "num_name.txt"
#define MIN 2
#define MAX 9

int add(int a, int b)
{
	return a + b;
}
int minus(int a, int b)
{
	return a - b;
}
int multiply(int a, int b)
{
	return a * b;
}
int devide(int a, int b)
{
	return a / b;
}

typedef struct opr
{
	char str[2];
	int(*op)(int a, int b);
}opr;
opr alloprators[4];
//int(*op[4])(int a, int b) = { add ,minus ,multiply ,devide };



typedef struct truefalseqestion
{
	char title[50];
	int best;//0~1
	int userchoice;
}tfq;


typedef struct examscore
{
	int no;
	char name[50];
	int score;
}escore;




escore allescores[100];
int allescorecnt = 0;

tfq alltfqs[100];
tfq usetfqs[USE_QUESTIONS_COUNT];
int alltfqcnt = 0;

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

tfq gettfqfromline(char *line)
{
	char *part;
	int index = 0;
	tfq q;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(q.title, part);
			break;
		case 2:
			q.best = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return q;
}

escore getescorefromline(char *line)
{
	char *part;
	int index = 0;
	escore q;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			q.no = toint(part);
			break;
		case 2:
			strcpy(q.name, part);
			break;
		case 3:
			q.score = toint(part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return q;
}



void readalltfqs()
{
	char line[200];
	FILE *fp = fopen(FILE_SEL, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SEL);
		getchar();
		exit(1);
	}
	alltfqcnt = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		alltfqs[alltfqcnt++] = gettfqfromline(line);
	}
	printf("\n已读入文件!\n");

}

void readallescores()
{
	char line[200];
	FILE *fp = fopen(FILE_SCORE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_SCORE);
		getchar();
		exit(1);
	}
	allescorecnt = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		allescores[allescorecnt++] = getescorefromline(line);
	}
	printf("\n已读入文件!", FILE_SEL);

}

int cmpbyno(const void * a, const void * b)
{
	return  ((escore*)a)->no - ((escore*)b)->no;
}

int cmpbyscore(const void * a, const void * b)
{
	return  ((escore*)a)->score - ((escore*)b)->score;
}

void sortanddisplayallescores()
{
	int i;
	qsort(allescores, allescorecnt, sizeof(escore), cmpbyno);
	printf("所有成绩按学好排序后如下\r\n");
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allescorecnt; i++)
	{
		printf("%d  %s %d\n", allescores[i].no, allescores[i].name, allescores[i].score);
	}
	printf("--------------------------------------------\r\n");
}


int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int randomminmax()
{
	return rand() % (MAX - MIN + 1) + MIN;
}

void generateuseids(int allcnt, int usecnt, int useids[])
{
	int i;
	int r, ri, ucnt = 0, tmp, top;
	int allids[100];
	for (i = 0; i < allcnt; i++)
	{
		allids[i] = i;
	}
	while (ucnt < usecnt)
	{
		ri = random(0, allcnt - ucnt);
		useids[ucnt++] = r = allids[ri];
		top = allcnt - ucnt - 1;
		if (r < top)
		{
			allids[r] = allids[top];
		}
	}
}


void testonetfq(tfq *q)
{
	int i, b, r, answer = 0, repeat = -2;
	char o;
	printf("--%s--\n\n", q->title);
	printf("请输入你的判断（0表是错误，1表示正确），并以回车结束:");
	scanf("%d", &answer);
	q->userchoice = answer;
}


void testalltfqs()
{
	int i;
	int useids[USE_QUESTIONS_COUNT] = { 0 };
	generateuseids(alltfqcnt, USE_QUESTIONS_COUNT, useids);
	printf("----------判断题-----------\n\n");
	for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	{
		usetfqs[i] = alltfqs[useids[i]];
		testonetfq(&usetfqs[i]);
	}
}

int displaytfqstestresult()
{
	int i, score = 0;
	//int useids[USE_QUESTIONS_COUNT] = { 0 };
	//generateuseids(allselqcnt, USE_QUESTIONS_COUNT, useids);
	//for (i = 0; i < USE_QUESTIONS_COUNT; i++)
	//{
	//	printf("\n第%d题：%s\n", i + 1, useselqs[i].title);
	//	printf("你的答案：%s\n", useselqs[i].choices[useselqs[i].userchoice - 1]);

	//	if (useselqs[i].userchoice == useselqs[i].best)
	//	{
	//		printf("\t\t\t\t正确！\n");
	//		score += 5;
	//	}
	//	else
	//		printf("--错误，正确答案是：%s\n", useselqs[i].choices[useselqs[i].best - 1]);
	//}
	//printf("\n你的总分：%d\n", score);
	return score;
}


void inputstudentandexam()
{
	//int i, no, score, save;
	//char name[50] = "";
	//srand(time(NULL));
	//printf("\n请输入要考生学号(1~100)，并以回车结束:");
	//scanf("%d", &no);
	//printf("\n请输入考生姓名，不能带空格、Tab或回车符，并以回车结束:");
	//scanf("%s", name);
	//readallselqs();
	//readalltfqs();
	//testallselqs();
	//testalltfqs();
	//score = displayselqstestresult() + displaytfqstestresult();
	//printf("\n题目全部做完，请选择是否保存成绩？选1保存，否则考试记录清除。以回车结束:");
	//scanf("%d", &save);
	//if (save == 1)
	//{
	//	appendscores(no, name, score);
	//}
	//printf("\n\n要选其他菜单，请按任意键\n");
	//system("pause");
}

void avehighlowescores()
{
	int i;
	float sum = 0;
	qsort(allescores, allescorecnt, sizeof(escore), cmpbyscore);
	for (i = 0; i < allescorecnt; i++)
		sum += allescores[i].score;
	printf("%s\t%d\r\n", "最高", allescores[allescorecnt - 1].score);
	printf("%s\t%d\r\n", "最低", allescores[0].score);
	printf("%s\t%.1f\r\n", "平均", sum / (float)allescorecnt);
}

//1+2*3/4 n={1,2,3,4} op ={+,*,/} oplen =3
int calc(int n[], int opindex[], int oplen)
{
	int i, re = n[0];
	for (i = 0; i < oplen; i++)
	{
		re = alloprators[opindex[i]].op(re, n[i + 1]);
	}
	return re;
}



void init()
{
	strcpy(alloprators[0].str, "+");
	strcpy(alloprators[1].str, "-");
	strcpy(alloprators[2].str, "*");
	strcpy(alloprators[3].str, "/");
	alloprators[0].op = add;
	alloprators[1].op = minus;
	alloprators[2].op = multiply;
	alloprators[3].op = devide;
}

void concatstringandint(char des[], int n)
{
	char str[10];
	itoa(n, str, 10);
	strcat(des, str);
}

int testone(int nums[], int opindex[], int oplen)
{
	int i, re, input;
	char exp[50] = "";
	concatstringandint(exp, nums[0]);
	for (i = 0; i < oplen; i++)
	{
		strcat(exp, alloprators[opindex[i]].str);
		concatstringandint(exp, nums[i + 1]);
	}
	printf("%s =? ", exp);
	re = calc(nums, opindex, oplen);
	scanf("%d", &input);
	if (re == input)
	{

		printf("正确！\n\n");
		return 1;
	}
	else
	{
		printf("错误！正确答案应该是 %d\n\n", re);
		return 0;
	}
}
void testop()
{
	int nums[] = { 1,2,3,4 };
	int opindex[] = { 1,2,3 };
	int len = 3;
	int c = calc(nums, opindex, len);
	printf("c=%d\n", c);
	testone(nums, opindex, len);
}

int module2_2(int op)
{
	int i, total = 0;
	int nums[4];
	int opindex[3];
	int len;
	nums[0] = randomminmax();
	nums[1] = randomminmax();
	opindex[0] = op - 1;
	return testone(nums, opindex, 1);
}

int module2_4(int op)
{
	int i, total = 0;
	int nums[4];
	int opindex[3];
	int len;
	nums[0] = randomminmax();
	nums[1] = randomminmax();
	nums[2] = randomminmax();
	opindex[0] = op - 1;
	opindex[1] = op - 1;
	return testone(nums, opindex, 2);
}

int module2_6(int op)
{
	int i, total = 0;
	int nums[4];
	int opindex[3];
	int len;
	nums[0] = randomminmax();
	nums[1] = randomminmax();
	nums[2] = randomminmax();
	nums[3] = randomminmax();
	opindex[0] = op - 1;
	opindex[1] = op - 1;
	opindex[2] = op - 1;
	return testone(nums, opindex, 3);
}

int module2()
{
	int i, op = 1, total = 0;
	int nums[4];
	int opindex[3];
	int len;
	int(*f[3])(int) = { module2_2 ,module2_4 ,module2_6 };
	printf("\n请输入运算符（整数）\n1 +\n2 -\n3 *\n4 /:");
	scanf("%d", &op);
	for (i = 0; i < 2; i++)
	{
		if (module2_2(op))
		{
			total += 5;
		}
	}

	for (i = 0; i < 4; i++)
	{
		if (module2_4(op))
		{
			total += 5;
		}
	}

	for (i = 0; i < 6; i++)
	{
		if (module2_6(op))
		{
			total += 5;
		}
	}

	for (i = 0; i < 8; i++)
	{
		if (f[random(0, 2)](op))
		{
			total += 5;
		}
	}
	return total;
}

int main()
{
	int total = 0;
	char choice = 0;
	init();
	while (1)
	{
		total = module2();
		printf("总分=%d\n", total);
		if (total >= 60)
			break;
		else
		{
			printf("按q退出模块2，否则重新测试模块2:", total);
			fseek(stdin, 0, SEEK_END);
			if (getchar() == 'q')
			{
				break;
			}
		}
	}

	system("pause");
	return 0;
}