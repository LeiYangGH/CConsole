#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#define FILE_UNAME "uname.txt"
typedef struct user//定义一个denglu结构体
{
	char name[20];//存放用户名
	char password[20];//相应的密码
}user;//定义结构体变量
user allusers[30];
int alluserscount = 0;
//字符串相等
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//从一行文本读入并根据\t符号拆分，组合成一个user
user getuserfromline(char *line)
{
	char *part;
	int index = 0;
	user u;
	part = strtok(line, " \n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(u.name, part);
			break;
		case 2:
			strcpy(u.password, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \n");
	}
	return u;
}

void readallusers()
{
	char line[200];
	FILE *fp = fopen(FILE_UNAME, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", FILE_UNAME);
	}
	else
	{
		alluserscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allusers[alluserscount++] = getuserfromline(line);
		}
		//printf("\n已读入用户名和密码!", FILE_UNAME);
	}
}

void welcome()//主页面
{
	system("cls");
	printf("\t\t       -----------------------------------------------\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t欢迎进入系统\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       -----------------------------------------------\n");
}
void choices()//副页面
{
	system("cls");
	printf("\t\t\t0、查看菜品");
	printf("\t\t\t1、选择菜品");
}

int getpassword(char name[], char password[])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(allusers[i].name, name))
		{
			strcpy(password, allusers[i].password);
			return 1;
		}
	}
	return 0;
}

int validatepassword(char password[])
{
	int i = 3;
	char input[20] = "";

	do {
		printf("\n请输入密码(还有%d次机会)：", i);
		scanf("%s", input);
		if (streq(input, password))
			return 1;
	} while (--i > 0);
	return 0;
}

void exitprogram()
{
	printf("\n\n按任意键退出\n");
	system("pause");
	exit(0);
}
void login()
{
	char name[20] = "";
	char password[20] = "";
	printf("\n请输入用户名：");
	scanf("%s", name);
	if (getpassword(name, password))
	{
		if (!validatepassword(password))
		{
			printf("\n登录失败！\n");
			exitprogram();
		}
	}
	else
	{
		printf("用户名不存在！\n");
		exitprogram();
	}

}
//顾客点菜，当输入0的时候停止
void book(int dishs[])
{
	int i = 0, n;
	printf("您选择的菜品是：");
	while (scanf("%d", &dishs[i]) && dishs[i])
		i++;
	n = i;
	printf("您选择的菜品是：");
	for (i = 0; i<n; i++)
		printf("%4d", dishs[i]);
}
#define TEST 1
int main()
{
	int cho;
	int dish[20];
	int choicetry = 3;
	char name[20] = "";
	char password[20];
	char choice[3] = "";

	readallusers();
#if TEST
	login();

	/*printf("\n\n按任意键退出\n");
	system("pause");*/
#endif // TEST

	welcome();
	Sleep(3000);
	choices();
	printf("\n请选择：");
	scanf("%d", cho);
	switch (cho)
	{
	case 0:
		while (!streq(choice, "0"))
		{
			system("cls");
			printf("\n\t 上海小吃");
			printf("\n\t 1、小绍兴白斩鸡");
			printf("\n\t 2、老大房鲜肉月饼");
			printf("\n\t 3、德兴馆焖蹄面");
			printf("\n\t 4、城隍庙五香豆");
			printf("\n\t 5、崇明糕");
			printf("\n\t 6、高桥松饼");
			printf("\n\t 7、南翔小笼");
			printf("\n\t 8、荠菜肉丝炒年糕");
			printf("\n\t 9、两面黄");
			printf("\n\t 10、烂糊面");
			printf("\n\t 0、退出系统\n\n");
			printf("\n\t 请选择需要查看的菜品：");
			fseek(stdin, 0, SEEK_END);
			scanf("%s", choice);
			if (streq(choice, "1"))
				printf("\t\t小绍兴白斩鸡\n\t\t小绍兴的白斩鸡是众多外地游客来上海吃过后念念不忘的美味。经过六十多年的创业历史，小绍兴已经从当年一个小小的鸡粥摊子发展成为了饮食集团。虽说做法相同的白斩鸡虽说满大街都能吃到，但是说到起源最早味道最正宗的还是要来这里。。");
			else if (streq(choice, "2"))
				printf("\t\t老大房鲜肉月饼\n\t\t在上海，说起月饼，最先想起的就是鲜肉月饼了，而提到鲜肉月饼，就不得不提“老大房”了。他们家鲜肉月饼一盒十个，都是刚出锅的，四块钱一个，热气腾腾，外面酥酥的，里面肉馅软嫩多汁，酥酥的外皮感觉香脆，肉馅感觉肥而不腻。");
			else if (streq(choice, "3"))
				printf("\t\t德兴馆焖蹄面\n\t\t\t德兴馆最大众的焖蹄面，一直被上海人视为“上海第一面”。酥软脱骨的焖肉焐入面中，化而不失其形，浇头与汤面融为一体，咸中带甜，甜中蕴鲜，是苏州面在上海扎根变幻的百年典范。");
			else if (streq(choice, "4"))
				printf("\t\t城隍庙五香豆\n\t\t城隍庙五香豆是上海地区传统小吃。城隍庙五香豆皮薄肉松，盐霜均匀，咬嚼柔糯。吃到嘴里香喷喷、甜滋滋，别有风味");
			else if (streq(choice, "5"))
				printf("\t\t崇明糕\n\t\t崇明糕是上海崇明地区传统特色糕点之一，特色风味小吃。有松糕和硬糕两种。选料讲究，配比合理，甜度适中，果肉适量，蒸煮科学，清香松口，糯而不粘。");
			else if (streq(choice, "6"))
				printf("\t\t高桥松饼\n\t\t高桥松饼为上海市浦东新区高桥镇四大名点，因其入口酥松而得名。又因酥皮层次分明，每层薄如纸，别称千层饼。");
			else if (streq(choice, "7"))
				printf("\t\t南翔小笼\n\t\t南翔小笼的馅心是夹心腿肉作成肉酱，仅撒少许姜末和肉皮冻、盐、酱油、糖和水调制而成；皮是用不发酵的精面粉制作而成的。");
			else if (streq(choice, "8"))
				printf("\t\t荠菜肉丝炒年糕\n\t\t荠菜肉丝炒年糕是一道由年糕、荠菜、瘦猪肉等做成的美食。");
			else if (streq(choice, "9"))
				printf("\t\t两面黄\n\t\t两面黄是一种江苏省苏州市传统的面食名吃，曾被称为“面条中的皇帝”，价格不菲。解放后就很少供应，消失已有二三十年，近年来在苏州老字号餐饮界再次兴起");
			else if (streq(choice, "10"))
				printf("\t\t烂糊面\n\t\t上海烂糊面是上海人的叫法，通俗一点说--就是把面煮得烂烂的，带有一定的糊状，但却又要烂而不黏，糊而不焦，简单却非常“吃功夫”。考究点的烂糊面，里面有青菜，肉丝、虾仁，鸭肫干碎粒，茭白碎粒等不少辅料，味道鲜美，鲜的落眉毛。");
			else if (streq(choice, "0"))
				exitprogram();
			else
			{
				if (choicetry-- > 0)
					printf("输入有错，请重新输入\n");
				else
				{
					printf("输入错误超出3次，程序将退出！\n");
					exitprogram();
				}
			}
			system("pause");

		}break;
	case 1:
		book(dish); break;
	}
	return 0;
}
