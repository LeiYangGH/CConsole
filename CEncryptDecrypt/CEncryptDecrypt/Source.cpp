#include<string.h>
#include<stdlib.h>
#include <stdio.h>
#include <windows.h>
struct password               /*加密方法结构变量*/
{
	char ps[10];                /*加密字符串*/
	long wd;                   /*加密的字节数*/
};
struct password password;
char s[100];
void set()                          //加密方法设置函数
{
	printf("\n输入加密字符串:");
	scanf("%s", password.ps);
	printf("\n输入加密字节数:");
	scanf("%ld", &password.wd);
	getchar();
	printf("\n");
	system("pause");             /*系统函数，按任意键继续,使界面整洁*/
}

void Printtxt()             /*显示原始文件和解密文件函数*/
{
	/*以读方式打开文件*/
	FILE  *source = fopen("原始文件.txt", "rt");
	FILE  *result = fopen("加密文件.txt", "r");
	FILE  *recall = fopen("解密文件.txt", "rt");
	char c;     //临时字符存储变量
	if (source == NULL)
	{
		printf("无法打开 原始文件.txt \n");
		exit(0);
	}

	if (result == NULL)
	{
		printf("无法打开 加密文件.txt \n");
		exit(0);
	}

	if (recall == NULL)
	{
		printf("无法打开 解密文件.txt \n");
		exit(0);
	}
	c = fgetc(source);  //先从原始文件读出一个字符，若不是文件结尾，则文件内容非空
	if (c == EOF)  //文件内容为空，输出加密字符
	{
		printf("\n加密字符：");
		printf("%s\n", s);
	}
	else      //文件非空，输出原始文件
	{
		printf("\n原始文件：");
		printf("%c", c);
		while ((c = fgetc(source)) != EOF)
			printf("%c", c);
	}
	printf("\n");
	printf("\n加密文件：");
	while ((c = fgetc(result)) != EOF)   //文件非空，输出加密文件
		printf("%c", c);
	printf("\n");

	printf("\n解密文件：");
	while ((c = fgetc(recall)) != EOF)   //文件非空，输出解密文件
		printf("%c", c);
	printf("\n");
	fclose(source);
	fclose(result);
	fclose(recall);
	printf("\n");
	system("pause");
}

void encode()                        /*加密函数*/
{
	int m, n = strlen(password.ps), i, flag = 1;     //m存储加密字符长度 ,n存储加密字符串长度 ,i 为临时变量
	char N = 0, w = 0;
	char c = 0, C = 0;   //临时字符存储变量
	FILE  *result = fopen("加密文件.txt", "wt");
	FILE  *source = fopen("原始文件.txt", "wt");
	if (result == NULL)
	{
		printf("无法打开 加密文件.txt \n");
		exit(0);
	}

	if (source == NULL)
	{
		printf("无法打开 原始文件.txt \n");
		flag = 0;
	}

	flag = 0;
	int b;
	printf("\n请选择加密对象:\n");
	printf("\n1.加密字符串\n");
	printf("\n2.加密文件\n");
	scanf("%d", &b);
	if (b == 1) { flag = 0; }
	else {
		FILE  *fp;
		char filename[30];
		printf("请输入文件名:(包括文件后缀名)\n");
		scanf("%s", filename);
		if ((fp = fopen(filename, "r")) != NULL) {
			printf("文件打开成功! \n");
			flag = 1;
			while (!feof(fp)) {
				char n;
				n = fgetc(fp);
				fputc(n, source);
			}
			printf("文件复制成功!\n");
		}
		else {
			printf("文件打开失败!\n");
			exit(0);
		}
		fclose(source);
	}

	if (flag == 0)      //判断文件是否为空，为空的话，对输入字符加密
	{
		printf("请输入要加密的字符串：\n");
		scanf("%s", s);
		m = strlen(s);
		fprintf(source, "%s", s);
		int a = 0;
		for (i = 0; i<m; i++)
		{
			if (a<password.wd)
			{
				N = s[i] + password.ps[a%n] - 48;
				if (N>122)
				{
					N = N % 122;          /*模运算*/
				}
				fputc(N, result);
				a++;
			}
			else
				fputc(s[i], result);
		}
	}
	else                //文件非空，对文件加密      
	{
		fopen("原始文件.txt", "r");
		C = fgetc(source);
		w = C + password.ps[0 % n] - 48;
		fputc(w, result);
		int a = 1;
		for (i = 0; (c = fgetc(source)) != EOF; i++)
		{
			if (a<password.wd)
			{
				N = c + password.ps[a%n] - 48;
				if (N>122)
				{
					N = N % 122;              /*模运算*/
				}
				fputc(N, result);
				a++;
			}
			else {
				fputc(c, result);
			}
		}
	}
	printf("\n加密成功!\n");
	fclose(result);
	fclose(source);
	printf("\n");
	system("pause");
}
void decode()                    /*解密函数*/
{
	FILE * recall = fopen("解密文件.txt", "wt");
	FILE * result = fopen("加密文件.txt", "rt");
	char c, N;
	int n = strlen(password.ps), i;  //n存储加密字符串长度,i为临时变量
	if (result == NULL)
	{
		printf("无法打开 加密文件.txt \n");
		exit(0);
	}
	if (recall == NULL)
	{
		printf("无法打开 加密文件.txt \n");
		exit(0);
	}
	int a = 0;
	for (i = 0; (c = fgetc(result)) != EOF; i++)  //对加密文件进行译码
	{

		if (a<password.wd)
		{
			N = c - (password.ps[a%n] - 48);
			if (N<0)
			{
				N = (N + 122) % 122;            /*模运算*/
				fputc(N, recall);
			}
			else
			{
				if (N == 0)
					fputc('z', recall); //将解密结果输出至recall文件
				else
					fputc(N, recall);
			}
			a++;
		}
		else {
			fputc(c, recall);
		}
	}
	printf("\n解密成功!\n");
	fclose(result);
	fclose(recall);
	printf("\n");
	system("pause");
}
void cmptxt()              /*比较解密文件和原始文件的一致性，一致输出原字符，不一致输'_'*/ {

	FILE  *source = fopen("原始文件.txt", "rt");

	FILE  *recall = fopen("解密文件.txt", "rt");
	char c, d;     //临时字符存储变量

	if (source == NULL)
	{
		printf("不存在 原始文件.txt 文件\n");
		exit(0);
	}
	if (recall == NULL)
	{
		printf("不存在 解密文件.txt 文件\n");
		exit(0);
	}//先从原始文件读出一个字符，若不是文件结尾，则文件内容非空
	c = fgetc(source);
	d = fgetc(recall);
	if (c == EOF)
	{
		printf("读文件错误!!\n");
		exit(0);
	}

	if (d == EOF)
	{
		printf("读文件错误!!\n");
		exit(0);
	}

	printf("文件比较:");

	while ((c = fgetc(source)) != EOF && (d = fgetc(recall)) != EOF)  //文件非空调用判断
	{
		if (c == d) //比较，输出字符
		{
			printf("%c", c);
		}
		else printf("文件比较不一致!");
		break;
	}

	printf("\n");


	fclose(source);

	fclose(recall);
	printf("\n");
	system("pause");
}
void menu() //菜单函数
{
	printf("文件加解密：\n");
	printf("                       \n");
	printf("1.设置加密方法        \n");
	printf("                       \n");
	printf("2.加密          \n");
	printf("                       \n");
	printf("3.解密          \n");
	printf("                       \n");
	printf("4.显示各文件          \n");
	printf("                       \n");
	printf("5.退出             \n");
	printf("                       \n");
	printf("请选择:");
}
void creat() //创建文件
{
	FILE *f1 = fopen("原始文件.txt", "wt");
	FILE *f2 = fopen("加密文件.txt", "wt");
	FILE *f3 = fopen("解密文件.txt", "wt");
	fclose(f1);
	fclose(f2);
	fclose(f3);
}
int main() //主函数，进行选择
{
	int a = 0;
	menu();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	system("color 3E");
	while (a != 5)
	{
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			creat();
			set();
			system("cls");
			menu();
			break;
		case 2:
			encode();
			system("cls");
			menu();
			break;
		case 3:
			decode();
			system("cls");
			menu();
			break;
		case 4:
			Printtxt();
			system("cls");
			menu();
			break;
		case 5:
			printf("\n 结束 !\n\n");
			break;
		default:
			printf("\n 请再次输入! \n");
			scanf("%d", &a);
			system("cls");
			menu();
			break;
		}
	}
}




