
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#define EDGE 20//棋盘规格。
char name1[10], name2[10];//玩家姓名。
int block[EDGE][EDGE];//0代表棋盘位置为空,1代表1玩家的棋子,2代表2玩家的棋子。
int coord[2] = { EDGE / 2, EDGE / 2 };//选择的位置，初始默认在中间。
int player = 1;//1代表1玩家,2代表2玩家。

void board();//打印棋盘。
void init();//初始化,把block数组的所有值设置为0。
void up();//上移。
void down();//下移。
void left();//左移。
void right();//右移。
void press();//落子函数。
int set();//此位置是否已被占据。
int win();//是否五子连珠而胜利，1代表胜利,0代表还未胜利。
int cross(int, int);//是否超界。
void play();//控制下棋流程的函数。

int main()
{
	system("color E1");//系统颜色。
	printf("\n\n\n\n\n\n                             -----------------------------------------------------------\n");
	printf("                                   -----------------------------------------------      \n");
	printf("                                                     YOHO! GOBANG!                      \n\n");
	printf("                                                     A MASTERPIECE                      \n\n");
	printf("                                                       by Robin Li                       \n\n");
	printf("                                              Press 'i' to enjoy the game               \n\n");
	printf("                                                          :D                            \n\n");
	printf("                                   -----------------------------------------------      \n");
	printf("                             -----------------------------------------------------------\n");
	char ch1;
	while (1)
	{
		ch1 = getch();
		switch (ch1)
		{
		case 'i':
			char ch2;
			init();
			while (1)
			{
				board();
				if (player == 1)
					printf("\n             NO.1 press now.\n", player, name1);
				if (player == 2)
					printf("\n             NO.2 press now.\n", player, name2);
				ch2 = getch();
				switch (ch2)
				{
				case 'w':up();
					break;
				case 's':down();
					break;
				case 'a':left();
					break;
				case 'd':right();
					break;
				case 'q':press();
					break;
				}
			}
			break;
		default:
			printf("Invalid character...\nRewrite please.\n");
			break;
		}
	}
	return 0;
}
void board()//此函数中有清屏。
{
	int a, b;
	int n = 1;
	system("cls");
	printf("\n ════════════════════\n");
	for (a = 0; a < EDGE; a++)
	{
		printf("|");//边界。
		for (b = 0; b < EDGE; b++)
		{
			if (a == coord[0] && b == coord[1])
			{
				printf("⊕");//显示已选坐标的位置。
			}
			else
			{
				if (block[a][b] == 0)
				{
					printf("十");//棋盘盘面。
				}
				else if (block[a][b] == 1)
				{
					printf("●");//NO.1
				}
				else if (block[a][b] == 2)
				{
					printf("○");//NO.2
				}
			}
		}
		printf("|");
		printf("\n");
	}
	printf(" ════════════════════\n");
}
void init()//在这个函数中有清屏。
{
	int a, b;
	for (a = 0; a < EDGE; a++)
	{
		for (b = 0; b < EDGE; b++)
		{
			block[a][b] = 0;
		}
	}
	system("cls");
	printf("\n\n\n\n\n\n                                       Thank you for choosing my GOBANG.\n\n\n");
	printf("                                  ┌-----------┐ \n");
	printf("                             Use  │     W     │     to move and 'Q' to press.\n");
	printf("                                  │  A  S  D  │ \n");
	printf("                                  └-----------┘ \n\n");
	printf("                             Input the two players' name below before the chess.\n\n\n");
	printf("                                                     ");
	scanf("%s%s", &name1, &name2);

}
void right()
{
	if (coord[1] + 1 >= EDGE)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[1]++;
	}
	board();
}
void left()
{
	if (coord[1] - 1 < 0)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[1]--;
	}
	board();
}
void up()
{
	if (coord[0] - 1 < 0)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[0]--;
	}
	board();
}
void down()
{
	if (coord[0] + 1 >= EDGE)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[0]++;
	}
	board();
}
void press()
{
	char ch;
	if (!set())//判断是否已经有一个棋子
	{
		block[coord[0]][coord[1]] = player;//player是玩家标识.
	}
	else
	{
		printf("\nCannot press here, it's been taken up.\n");
		return; //return是为了不进行下面的语句,防止未成功下棋情况下 player标识被更换.
	}
	if (win())
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		if (player == 1)
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                  NO.1 wins\n");
		if (player == 2)
			printf("\n                                                  NO.2 wins\n");
		printf("                                     Press 'c' to continue, 'e' to exit\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		ch = getche();
		while (1)
		{
			switch (ch)
			{
			case 'e':
				exit(0);
			case 'c':
				init();//整个棋盘初始化。
				coord[0] = EDGE / 2;//将聚焦位置放到中心。
				coord[1] = EDGE / 2;
				return;
			default:
				printf("\nInvalid character. Try again.\n");
			}
		}
	}
	if (player == 1)//在一个玩家完成下棋操作以后,将player对调.
	{
		player = 2;
	}
	else
	{
		player = 1;
		return;
	}

}
int set()//0代表此处没有棋子,可以进行下棋操作,1代表不能.
{
	if (block[coord[0]][coord[1]] == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int win()//首先说明一下 这里的x代表block的第一个参数,y代表block的第二个参数,而x代表的棋盘上对应的竖直方向,y代表棋盘的横向方向.
{
	int a, x, y;//约定这四个为计数变量
	int heng = 1, shu = 1, zuoxie = 1, youxie = 1;//四个方向的棋子数量,之前犯了一个逻辑错误,把这里全部设成0了,其实应该是1,因为下的那个棋子本身就是一个.
	for (a = -1; a > -5; a--)//横向判断开始
	{
		x = coord[0], y = coord[1] + a;//x,y代表坐标,作用是传递给isOver判断是否超出边界
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			heng++;
		}
		else
		{
			break;
		}
	}

	for (a = 1; a < 5; a++)//横向第二阶段
	{
		x = coord[0], y = coord[1] + a;//x,y代表坐标,作用是传递给isOver判断是否超出边界
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			heng++;
		}
		else
		{
			break;
		}
	}

	for (a = -1; a > -5; a--)//竖向判断开始
	{
		x = coord[0] + a, y = coord[1];
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			shu++;
		}
		else
		{
			break;
		}
	}
	for (a = 1; a < 5; a++)//竖向二阶段
	{
		x = coord[0] + a, y = coord[1];
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			shu++;
		}
		else
		{
			break;
		}
	}
	for (a = -1; a > -5; a--)//左斜开始
	{
		x = coord[0] - a, y = coord[1] + a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			zuoxie++;
		}
		else
		{
			break;
		}
	}
	for (a = 1; a < 5; a++)//左斜二阶段
	{
		x = coord[0] - a, y = coord[1] + a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			zuoxie++;
		}
		else
		{
			break;
		}
	}
	for (a = -1; a > -5; a--)//右斜开始
	{
		x = coord[0] + a, y = coord[1] + a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			youxie++;
		}
		else
		{
			break;
		}
	}
	for (a = -1; a > -5; a--)//右斜二阶段
	{
		x = coord[0] - a, y = coord[1] - a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			youxie++;
		}
		else
		{
			break;
		}
	}
	if (heng >= 5 || shu >= 5 || zuoxie >= 5 || youxie >= 5)//四个方向上,有没有大于等于5的
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int cross(int x, int y)//传进来的x,y参数代表即将进行判断的block数组的坐标.返回值约定1代表超出边界,0代表还在边界内.
{
	if (x > EDGE - 1 || x<0 || y>EDGE - 1 || y < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
