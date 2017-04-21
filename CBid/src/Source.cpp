#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "windows.h" 
#define BID_FORMAT_STRING "%s\t%d\t%d\t%d\t%d\t%d\t%d\r\n"
typedef struct bid
{
	char name[20];
	int price;
	int design;
	int fame;
	int duration;
	int quality;
	int total;
}bid;

bid allbids[50];//最多存50条
int allbidscount = 0;//记录数

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//显示投标者信息
void displaybid(bid b)
{
	printf("\r\n");
	printf(BID_FORMAT_STRING,
		b.name,
		b.price, b.design, b.fame, b.duration, b.quality,
		b.total);
}

//查看所有投标者信息
void viewallbids()
{
	int i;
	printf("所有%d位投标者信息如下\r\n", allbidscount);
	printf("--------------------------------------------\r\n");
	printf("投标者\t报价\t施工\t综合\t工期\t质量\t总分\r\n");
	for (i = 0; i < allbidscount; i++)
	{
		displaybid(allbids[i]);
	}
	printf("--------------------------------------------\r\n");
}

int calculatetotal(bid b)
{
	//可选的算法：加权平均
	/*int result = b.price * 60
		+ b.design * 10
		+ b.fame * 20
		+ b.duration * 5
		+ b.quality * 5;
	return (int)result / 100.0f;*/
	return b.price + b.design + b.fame + b.duration + b.quality;
}

void addbid(char name[20],
	int price, int design, int fame, int duration, int quality)
{
	bid b;
	strcpy(b.name, name);
	b.price = price;
	b.design = design;
	b.fame = fame;
	b.duration = duration;
	b.quality = quality;
	b.price = price;
	b.total = calculatetotal(b);
	allbids[allbidscount++] = b;
}

//创建示例投标者信息
void createsamplebids()
{
	printf("创建示例投标者信息...");
	addbid("张三", 59, 9, 19, 4, 4);
	addbid("李四", 58, 2, 5, 4, 1);
	addbid("王五", 55, 3, 15, 1, 1);
	addbid("黄光标", 30, 5, 14, 1, 3);
	addbid("凤姐", 23, 5, 17, 3, 5);
	addbid("刘强东", 45, 8, 5, 2, 2);
	addbid("马化腾", 54, 4, 9, 2, 3);
	addbid("马云", 25, 4, 11, 1, 1);
	addbid("李彦宏", 56, 6, 18, 5, 5);
	printf("示例投标者信息已创建。");
}


//输入信息
void inputstring(char str[], int maxlenth, char* purpose)
{
	int len = -1;
	char input[50] = "";
	while (len<1 || len > maxlenth)
	{
		printf("请输入%s，%d个字符以内，不能带Tab或回车符:", purpose, maxlenth);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("您的 %s 为 %s \r\n", purpose, str);
}

int inputint(int max, char* purpose)
{
	int len = -1;
	char input[50] = "";
	int score = 0;
	while (score <= 0 || score > max)
	{
		printf("请输入%s分数，最大值不超过%d:", purpose, max);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
		score = toint(input);
	}
	printf("输入的 %s 为 %d \r\n\r\n", purpose, score);
	return score;
}



//根据name查投标者
void findpatientbyid(char *name)
{
	int i;
	int found = 0;
	for (i = 0; i < allbidscount; i++)
	{
		bid b = allbids[i];
		if (strcmp(b.name, name) == 0)
		{
			found = 1;
			printf("查找到投标者信息如下\r\n");
			printf("--------------------------------------------\r\n");
			displaybid(b);
			break;
		}
	}
	if (found == 0)
		printf("没找到投标者:%s!\r\n", name);
}

void promptaddbid()
{
	char name[20] = "";
	inputstring(name, 20, "投标者姓名");
	addbid(name,
		inputint(60, "报价"),
		inputint(10, "施工组织设计"),
		inputint(20, "投标单位综合成绩"),
		inputint(5, "工期"),
		inputint(5, "质量")
	);
	printf("完成第%d个投标者信息录入!\r\n", allbidscount);
}

void promptfindbyname()
{
	char name[20] = "";
	inputstring(name, 20, "要查找的投标者姓名");
	findpatientbyid(name);
}

int iscountequal(int expected)
{
	if (allbidscount == expected)
		return 1;
	else
	{
		printf("现在有%d个投标，只有投标数为%d时才能执行此操作。\r\n", allbidscount, expected);
		return 0;
	}
}

int findworstid()
{
	int i;
	int worsttotal = 10000;
	int worstid;
	for (i = 0; i < allbidscount; i++)
	{
		bid b = allbids[i];
		if (b.total < worsttotal)
		{
			worsttotal = b.total;
			worstid = i;
		}
	}
	printf("最低分：%s\t 分数:%d\r\n", allbids[worstid].name, allbids[worstid].total);
	return worstid;
}



void deleteworst()
{
	int i;
	int besttotal = 0;
	if (iscountequal(10))
	{
		int worstid = findworstid();
		if (worstid < allbidscount - 1)
			for (i = worstid; i < allbidscount - 1; i++)
				allbids[i] = allbids[i + 1];
		allbidscount--;
		printf("删除最低分投标者完毕，剩下%d个投标者。\r\n", allbidscount);
	}

}

void displaybest()
{
	int i;
	int besttotal = 0;
	bid best;
	if (iscountequal(9))
	{
		for (i = 0; i < allbidscount; i++)
		{
			bid b = allbids[i];
			if (b.total > besttotal)
			{
				besttotal = b.total;
				best = b;
			}
		}
		printf("中标者：%s\t 分数:%d\r\n", best.name, best.total);
	}

}


int main()
{
	int choice = -1;

	//下面这句是生成示例数据
	createsamplebids();

	while (choice != 0)
	{
		system("CLS");
		printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
		printf("\n\t------------------------------");
		printf("\n\n\t 1. 输入投标者信息");
		printf("\n\t 2. 显示全部投标者信息");
		printf("\n\t 3. 根据投标者名称查找");
		printf("\n\t 4. 删除最低分");
		printf("\n\t 5. 显示中标者");
		printf("\n\t 0. 退出");
		printf("\n\n 请选择: ");
		scanf("%1[012345]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			promptaddbid();
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			viewallbids();
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			promptfindbyname();
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			deleteworst();
			break;
		case '5':
			printf("\n\n你选择了 4\n");
			displaybest();
			break;

		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}

	system("pause");
	return 0;
}