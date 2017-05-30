

/*下面是一个在VC++中调试通过的用结构体数组实现的信息管理程序，调试过程中，对TC下运行的程序主要进行了如下修改：
1. clrscr(); 函数不被VC识别，将其替换为system("cls");  同时需要在前面增加 #include <windows.h>
2. gotoxy();函数不被VC识别，在程序最后增加了一个VC下写的自定义函数 void gotoxy(int x,int y)，同时将其函数声明放在程序前面的自定义函数声明部分
3. getch();函数不被VC识别，改为getchar();
*/

/******头文件（.h）***********/
#include "stdio.h"   /*I/O函数*/
#include "stdlib.h" /*标准库函数*/
#include "string.h"/*字符串函数*/
#include "ctype.h" /*字符操作函数*/
#include <windows.h> 

#define M 50  /*定义常数表示记录数*/
int addresscount;  /*保存记录长度*/

typedef struct /*定义数据结构*/
{
	char name[20]; /*姓名*/
	char company[30];  /*单位*/
	char telephone[10];  /*电话*/
}address;
address alladdress[M];  /*定义结构体数组*/

/*输入记录，形参为结构体数组，函数值返回类型为整型表示记录长度*/
void  enter() {
	int i, n;
	system("cls"); /*清屏*/
	printf("\n请输入记录数\n"); /*提示信息*/
	scanf("%d", &n); /*输入记录数*/
	printf("请输入记录\n"); /*提示输入记录*/
	printf("姓名             单位                     电话\n");
	printf("------------------------------------------------\n");
	for (i = 0; i < n; i++)
	{
		scanf("%s%s%s", alladdress[i].name, alladdress[i].company, alladdress[i].telephone);  /*输入记录*/
		printf("----------------------------------------------\n");
	}
	addresscount = n;  /*返回记录条数*/
}

/*显示记录，参数为记录数组和记录条数*/
void list()
{
	int i;
	system("cls");
	printf("\n\n******************联系人******************\n");
	printf("姓名             单位                     电话\n");
	printf("------------------------------------------------\n");
	for (i = 0; i < addresscount; i++)
		printf("%-20s%-30s%-10s\n", alladdress[i].name, alladdress[i].company, alladdress[i].telephone);
	if ((i + 1) % 10 == 0)   /*判断输出是否达到10条记录*/
	{
		printf("按任意键继续...\n"); /*提示信息*/
		getchar();  /*压任意键继续*/
	}
	printf("************************end*******************\n");
}


/*显示指定的一条记录*/
void displayone(address addr)
{
	system("cls");
	printf("\n\n********************************************\n");
	printf("name                unit                      telephone\n");
	printf("------------------------------------------------\n");
	printf("%-20s%-30s%-10s\n", addr.name, addr.company, addr.telephone);
	printf("**********************end***********************\n");
}
/*查找函数，姓名name */
int find(char *name)
{
	int i;
	for (i = 0; i < addresscount; i++)/*从第一条记录开始，直到最后一条*/
	{
		if (strcmp(name, alladdress[i].name) == 0)  /*记录中的姓名和待比较的姓名是否相等*/
			return i;   /*相等，则返回该记录的下标号，程序提前结结束*/
	}
	return i;  /*返回i值*/
}

/*查找记录*/
void search(int length)
{
	char s[20];   /*保存待查找姓名字符串*/
	int i;   /*保存查找到结点的序号*/
	system("cls");   /*清屏*/
	printf("please search name\n");
	scanf("%s", s); /*输入待查找姓名*/
	i = find(s); /*调用find函数，得到一个整数*/
	if (i > length - 1)  /*如果整数i值大于n-1，说明没找到*/
		printf("not found\n");
	else
		displayone(alladdress[i]);  /*找到，调用显示函数显示记录*/
}

/*删除函数，参数为记录数组和记录条数*/
void deleteaddress()
{
	char s[20];  /*要删除记录的姓名*/
	int ch = 0;
	int i, j;
	printf("please deleted name\n"); /*提示信息*/
	scanf("%s", s);/*输入姓名*/
	i = find(s); /*调用find函数*/
	if (i > addresscount - 1)  /*如果i>n-1超过了数组的长度*/
		printf("no found not deleted\n"); /*显示没找到要删除的记录*/
	else
	{
		displayone(alladdress[i]); /*调用输出函数显示该条记录信息*/
		printf("Are you sure delete it(1/0)\n");  /*确认是否要删除*/
		scanf("%d", &ch);  /*输入一个整数0或1*/
		if (ch == 1)  /*如果确认删除整数为1*/
		{
			for (j = i + 1; j < addresscount; j++)  /*删除该记录，实际后续记录前移*/
			{
				strcpy(alladdress[j - 1].name, alladdress[j].name); /*将后一条记录的姓名拷贝到前一条*/
				strcpy(alladdress[j - 1].company, alladdress[j].company); /*将后一条记录的单位拷贝到前一条*/
				strcpy(alladdress[j - 1].telephone, alladdress[j].telephone); /*将后一条记录的电话拷贝到前一条*/
			}
			addresscount--;  /*记录数减1*/
		}
	}
}
/*插入记录函数，参数为结构体数组和记录数*/
void insert()/*插入函数，参数为结构体数组和记录数*/
{
	address temp;  /*新插入记录信息*/
	int i, j;
	char s[20]; /*确定插入在哪个记录之前*/
	printf("please input record\n");
	printf("************************************************\n");
	printf("name                unit                      telephone\n");
	printf("--------------------------------------------------\n");
	scanf("%s%s%s", temp.name, temp.company, temp.telephone); /*输入插入信息*/
	printf("------------------------------------------------\n");
	printf("please input locate name \n");
	scanf("%s", s); /*输入插入位置的姓名*/
	i = find(s);  /*调用find，确定插入位置*/
	for (j = addresscount - 1; j >= i; j--)   /*从最后一个结点开始向后移动一条*/
	{
		strcpy(alladdress[j + 1].name, alladdress[j].name); /*当前记录的姓名拷贝到后一条*/
		strcpy(alladdress[j + 1].company, alladdress[j].company); /*当前记录的单位拷贝到后一条*/
		strcpy(alladdress[j + 1].telephone, alladdress[j].telephone); /*当前记录的电话拷贝到后一条*/
	}
	strcpy(alladdress[i].name, temp.name); /*将新插入记录的姓名拷贝到第i个位置*/
	strcpy(alladdress[i].company, temp.company); /*将新插入记录的单位拷贝到第i个位置*/
	strcpy(alladdress[i].telephone, temp.telephone); /*将新插入记录的电话拷贝到第i个位置*/
	addresscount++;   /*记录数加1*/
}
/*保存函数，参数为结构体数组和记录数*/
void save()
{
	int i;
	FILE *fp;  /*指向文件的指针*/
	if ((fp = fopen("record.txt", "wb")) == NULL)  /*打开文件，并判断打开是否正常*/
	{
		printf("打不开文件\n");/*没打开*/
		exit(1);  /*退出*/
	}
	printf("\n保存文件。。\n"); /*输出提示信息*/
	fprintf(fp, "%d", addresscount);  /*将记录数写入文件*/
	fprintf(fp, "\r\n");  /*将换行符号写入文件*/
	for (i = 0; i < addresscount; i++)
	{
		fprintf(fp, "%-20s%-30s%-10s", alladdress[i].name, alladdress[i].company, alladdress[i].telephone);/*格式写入记录*/
		fprintf(fp, "\r\n"); /*将换行符号写入文件*/
	}
	fclose(fp);/*关闭文件*/
	printf("保存成功\n"); /*显示保存成功*/
}
/*读入函数，参数为结构体数组*/
int read()
{
	int i, n;
	FILE *fp; /*指向文件的指针*/
	if ((fp = fopen("record.txt", "rb")) == NULL)/*打开文件*/
	{
		printf("打不开文件\n");  /*不能打开*/
		exit(1);  /*退出*/
	}
	fscanf(fp, "%d", &n); /*读入记录数*/
	for (i = 0; i < n; i++)
		fscanf(fp, "%20s%30s%10s", alladdress[i].name, alladdress[i].company, alladdress[i].telephone); /*按格式读入记录*/
	fclose(fp);  /*关闭文件*/
	printf("成功读取文件!!!\n"); /*显示保存成功*/
	return n; /*返回记录数*/
}
/*按序号显示记录函数*/
void display()
{
	int id, n;
	FILE *fp; /*指向文件的指针*/
	if ((fp = fopen("record.txt", "rb")) == NULL) /*打开文件*/
	{
		printf("can not open file\n"); /*不能打开文件*/
		exit(1);  /*退出*/
	}
	printf("请输入序号...\n"); /*显示信息*/
	scanf("%d", &id);  /*输入序号*/
	fscanf(fp, "%d", &n); /*从文件读入记录数*/
	if (id >= 0 && id < n) /*判断序号是否在记录范围内*/
	{
		fseek(fp, (id - 1) * sizeof(address), 1); /*移动文件指针到该记录位置*/
		displayone(alladdress[id]); /*调用输出函数显示该记录*/
		printf("\r\n");
	}
	else
		printf("没有序号为 %d 的记录!!!\n ", id); /*如果序号不合理显示信息*/
	fclose(fp);  /*关闭文件*/
}
/*排序函数，参数为结构体数组和记录数*/
void sort()
{
	int i, j, flag;
	address temp; /*临时变量做交换数据用*/
	for (i = 0; i < addresscount; i++)
	{
		flag = 0;  /*设标志判断是否发生过交换*/
		for (j = 0; j < addresscount - 1; j++)
			if ((strcmp(alladdress[j].name, alladdress[j + 1].name)) > 0) /*比较大小*/
			{
				flag = 1;
				strcpy(temp.name, alladdress[j].name);  /*交换记录*/
				strcpy(temp.company, alladdress[j].company);
				strcpy(temp.telephone, alladdress[j].telephone);
				strcpy(alladdress[j].name, alladdress[j + 1].name);
				strcpy(alladdress[j].company, alladdress[j + 1].company);
				strcpy(alladdress[j].telephone, alladdress[j + 1].telephone);
				strcpy(alladdress[j + 1].name, temp.name);
				strcpy(alladdress[j + 1].company, temp.company);
				strcpy(alladdress[j + 1].telephone, temp.telephone);
			}
		if (flag == 0)break;  /*如果标志为0，说明没有发生过交换循环结束*/
	}
	printf("排序成功!!!\n"); /*显示排序成功*/
}
/*快速查找，参数为结构体数组和记录数*/
void binarysearch()
{
	char s[20];
	int l, r, m;
	printf("\n确认在查找之前，记录是否已排序!\n"); /*提示确认在查找之前，记录是否已排序*/
	printf("输入用来排序的名称\n"); /*提示输入*/
	scanf("%s", s); /*输入待查找的姓名*/
	l = 0; r = addresscount - 1;  /*设置左边界与右边界的初值*/
	while (l <= r) /*当左边界<=右边界时*/
	{
		m = (l + r) / 2; /*计算中间位置*/
		if (strcmp(alladdress[m].name, s) == 0) /*与中间结点姓名字段做比较判是否相等*/
		{
			displayone(alladdress[m]); /*如果相等，则调用print函数显示记录信息*/
			return; /*返回*/
		}
		if (strcmp(alladdress[m].name, s) < 0)  /*如果中间结点小*/
			l = m + 1;  /*修改左边界*/
		else
			r = m - 1; /*否则，中间结点大，修改右边界*/
	}
	if (l > r)   /*如果左边界大于右边界时*/
		printf("没找到\n"); /*显示没找到*/
}
/*复制文件*/
void copy()
{
	char outfile[20]; /*目标文件名*/
	int i, n;
	address temp[M];  /*定义临时变量*/
	FILE *sfp, *tfp; /*定义指向文件的指针*/
	system("cls");/*清屏*/
	if ((sfp = fopen("record.txt", "rb")) == NULL) /*打开记录文件*/
	{
		printf("不能打开文件信息\n"); /*显示不能打开文件信息*/
		exit(1); /*退出*/
	}
	printf("输入文件名，比如 c:\\f1\\te.txt:\n"); /*提示信息*/
	scanf("%s", outfile); /*输入目标文件名*/
	if ((tfp = fopen(outfile, "wb")) == NULL) /*打开目标文件*/
	{
		printf("不能打开文件信息\n"); /*显示不能打开文件信息*/
		exit(1); /*退出*/
	}
	fscanf(sfp, "%d", &n); /*读出文件记录数*/
	fprintf(tfp, "%d", n);/*写入目标文件数*/
	fprintf(tfp, "\r\n"); /*写入换行符*/
	for (i = 0; i < n; i++)
	{
		fscanf(sfp, "%20s%30s%10s\n", temp[i].name, temp[i].company,
			temp[i].telephone); /*读入记录*/
		fprintf(tfp, "%-20s%-30s%-10s\n", temp[i].name,
			temp[i].company, temp[i].telephone); /*写入记录*/
		fprintf(tfp, "\r\n"); /*写入换行符*/
	}
	fclose(sfp); /*关闭源文件*/
	fclose(tfp); /*关闭目标文件*/
	printf("复制成功!!!\n"); /*显示复制成功*/
}
void gotoxy(int x, int y) //cursor an gewuenschte position auf dem bildschirm setzen 
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; //variablendklaration 
	HANDLE hConsoleOut;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	csbiInfo.dwCursorPosition.X = x; //cursorposition X koordinate festlegen 
	csbiInfo.dwCursorPosition.Y = y; //cursorposition Y koordinate festlegen 
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition); //den cursor an die festgelegte koordinate setzen 
}

int menu_select()
{
	char s[80];
	int c;
	gotoxy(1, 25);/*将光标定为在第25行，第1列*/
	printf("压任意键继续......\n");/*提示压任意键继续*/
	getchar(); /*读入任意字符*/
	system("cls"); /*清屏*/
	gotoxy(1, 1);
	printf("********************MENU*********************\n\n");
	printf("		0. 输入记录\n");
	printf("		1. 显示文件内容\n");
	printf("		2. 通过姓名查找记录\n");
	printf("		3. 删除记录\n");
	printf("		4. 添加记录\n");
	printf("		5. 保存文件\n");
	printf("		6. 打开文件\n");
	printf("		7. 排序并输出\n");
	printf("	        8. 排序并保存新文件\n");
	printf("	        9. 快速查找\n");
	printf("		10. 复制到新文件\n");
	printf("	        11. 退出\n");
	printf("***********************************************\n");
	do {
		printf("\n	 请选择功能(0~11):"); /*提示输入选项*/
		scanf("%s", s); /*输入选择项*/
		c = atoi(s); /*将输入的字符串转化为整型数*/
	} while (c < 0 || c>11); /*选择项不在0~11之间重输*/
	return c; /*返回选择项，主程序根据该数调用相应的函数*/
}

/******主函数开始*******/
void main()
{
	system("cls");  /*清屏*/
	for (;;)/*无限循环*/
	{
		switch (menu_select())   /*调用主菜单函数，返回值整数作开关语句的条件*/
		{
		case 0: enter(); break;/*输入记录*/
		case 1:list(); break; /*显示全部记录*/
		case 2:search(addresscount); break; /*查找记录*/
		case 3:deleteaddress(); break; /*删除记录*/
		case 4:insert();  break;   /*插入记录*/
		case 5:save(); break; /*保存文件*/
		case 6:addresscount = read(); break; /*读文件*/
		case 7:display(); break;  /*按序号显示记录*/
		case 8:sort(); break; /*按姓名排序*/
		case 9:binarysearch(); break; /*快速查找记录*/
		case 10:copy(); break; /*复制文件*/
		case 11:exit(0); /*如返回值为11则程序结束*/
		}
	}
}