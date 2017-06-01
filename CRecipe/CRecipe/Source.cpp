#include <stdio.h>
#include<stdlib.h>
#include <windows.h>
struct denglu//定义一个denglu结构体
{
	char name[20];//存放用户名
	int key[20];//相应的密码
}str[20];//定义结构体变量
void main_menu()
{
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
void lesser_menu()
{
	printf("\t\t\t\t上海小吃\n");
	printf("\t\t\t\t1-----小绍兴白斩鸡\n");
	printf("\t\t\t\t2-----老大房鲜肉月饼\n");
	printf("\t\t\t\t3-----德兴馆焖蹄面\n");
	printf("\t\t\t\t4-----城隍庙五香豆\n");
	printf("\t\t\t\t5-----崇明糕\n");
	printf("\t\t\t\t6-----高桥松饼\n");
	printf("\t\t\t\t7-----南翔小笼\n");
	printf("\t\t\t\t8-----荠菜肉丝炒年糕\n");
	printf("\t\t\t\t9-----两面黄\n");
	printf("\t\t\t\t10----烂糊面\n");
}
int uname(char names)
{
	int i = 0;
	FILE *fp;
	fp = fopen("uname.txt", "r");
	if (fp == NULL) //打开文件出错。
	{
		printf("出错"); exit(0);
	}
	while (fscanf(fp, "%s", &str[i].name[i]) != EOF) //读取字符到数组，直到文件结尾(返回EOF)
		i++;
	fclose(fp);//关闭文件
	for (i = 0; i<20; i++)
	{
		if (names == str[i].name[i])
			break;
	}
	if (i == 19)
		if (str[19].name[19] != names)
			i++;
	return i;
}
int ukey(int keys, int j)
{
	int i = 0, flags = 0;
	FILE *fp;
	fp = fopen("ukey.txt", "r");
	if (fp == NULL) //打开文件出错。
	{
		printf("出错"); exit(0);
	}
	while (fscanf(fp, "%d", &str[i].key[i]) != EOF) //读取数据到数组，直到文件结尾(返回EOF)
		i++;
	for (i = 0; i<20; i++)
		if (str[j].key[j] == keys)
		{
			flags = 1;
			break;
		}
	return flags;
}
int main()
{
	char name;
	int n = 0, key, timer = 3, count = 3, flag, p, j;
	char op;
	main_menu();
	while (timer != 0) { Sleep(1000); timer--; }
	system("cls");
	printf("\t\t请输入用户名：");
	scanf("%s", &name);
	printf("\n");
	n = uname(name);
	if (n<20)
	{
		for (j = 0; j<3; j++)
		{
			printf("\t\t请输入密码：");
			scanf("%d", &key);
			flag = ukey(key, n);
			if (flag)
			{
				system("cls");
				lesser_menu();
				while (count != 0)
				{
					printf("输入你感兴趣的：");
					scanf("%d", p);
					if (p>0 && p<11)
						switch (p)
						{
						case 1:printf("\t\t小绍兴白斩鸡\n\t\t小绍兴的白斩鸡是众多外地游客来上海吃过后念念不忘的美味。经过六十多年的创业历史，小绍兴已经从当年一个小小的鸡粥摊子发展成为了饮食集团。虽说做法相同的白斩鸡虽说满大街都能吃到，但是说到起源最早味道最正宗的还是要来这里。。"); break;
						case 2:printf("\t\t老大房鲜肉月饼\n\t\t在上海，说起月饼，最先想起的就是鲜肉月饼了，而提到鲜肉月饼，就不得不提“老大房”了。他们家鲜肉月饼一盒十个，都是刚出锅的，四块钱一个，热气腾腾，外面酥酥的，里面肉馅软嫩多汁，酥酥的外皮感觉香脆，肉馅感觉肥而不腻。"); break;
						case 3:printf("\t\t德兴馆焖蹄面\n\t\t\t德兴馆最大众的焖蹄面，一直被上海人视为“上海第一面”。酥软脱骨的焖肉焐入面中，化而不失其形，浇头与汤面融为一体，咸中带甜，甜中蕴鲜，是苏州面在上海扎根变幻的百年典范。"); break;
						case 4:printf("\t\t城隍庙五香豆\n\t\t城隍庙五香豆是上海地区传统小吃。城隍庙五香豆皮薄肉松，盐霜均匀，咬嚼柔糯。吃到嘴里香喷喷、甜滋滋，别有风味"); break;
						case 5:printf("\t\t崇明糕\n\t\t崇明糕是上海崇明地区传统特色糕点之一，特色风味小吃。有松糕和硬糕两种。选料讲究，配比合理，甜度适中，果肉适量，蒸煮科学，清香松口，糯而不粘。"); break;
						case 6:printf("\t\t高桥松饼\n\t\t高桥松饼为上海市浦东新区高桥镇四大名点，因其入口酥松而得名。又因酥皮层次分明，每层薄如纸，别称千层饼。"); break;
						case 7:printf("\t\t南翔小笼\n\t\t南翔小笼的馅心是夹心腿肉作成肉酱，仅撒少许姜末和肉皮冻、盐、酱油、糖和水调制而成；皮是用不发酵的精面粉制作而成的。"); break;
						case 8:printf("\t\t荠菜肉丝炒年糕\n\t\t荠菜肉丝炒年糕是一道由年糕、荠菜、瘦猪肉等做成的美食。"); break;
						case 9:printf("\t\t两面黄\n\t\t两面黄是一种江苏省苏州市传统的面食名吃，曾被称为“面条中的皇帝”，价格不菲。解放后就很少供应，消失已有二三十年，近年来在苏州老字号餐饮界再次兴起"); break;
						case 10:printf("\t\t烂糊面\n\t\t上海烂糊面是上海人的叫法，通俗一点说--就是把面煮得烂烂的，带有一定的糊状，但却又要烂而不黏，糊而不焦，简单却非常“吃功夫”。考究点的烂糊面，里面有青菜，肉丝、虾仁，鸭肫干碎粒，茭白碎粒等不少辅料，味道鲜美，鲜的落眉毛。"); break;
						default: count--;
						}
					else
					{
						system("cls");
						main_menu();
					}
				}
			}
			else
			{
				system("cls");
				main_menu();
			}
		}
	}
	return 0;
}
