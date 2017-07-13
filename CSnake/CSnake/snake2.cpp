/**
******************************************************************************
* @file       snaker.c
* @author     A Big Cat
* @version    V1.0
* @date       2017-2-26
* @brief      My FIRST GAME  application program based on C Langugage,
of course, I referred to other programs on the Internet.
******************************************************************************
**/

//#include "StdAfx.h"
#include <Windows.h>//包含WinCon.h  
#include <stdio.h>  
#include <time.h>  
#include <stdlib.h>  
/*
***宏定义
*/
#define  MAP_WIDTH  15  
#define  MAP_HEIGHT 15  
#define  UP         1  
#define  DOWN       2  
#define  LEFT       3  
#define RIGHT       4  

/*
***结构体
*/
typedef struct snake//蛇身的一个节点 
{
	unsigned int x, y;
	struct snake *next;
}SNAKE;
/*
***全局变量
*/
unsigned int Score = 0, Score_Add = 10;
unsigned int Direction, Time_sleep = 1000;
SNAKE *head, *food;//蛇头指针，食物指针 
SNAKE *q;//遍历和判断蛇的时候用到的指针 
unsigned char Game_status = 0;// 游戏结束的情况：：撞到墙；：咬到自己；：主动退出游戏。 
							  /*
							  ***函数声明
							  */
void Pos_Set(unsigned int x, unsigned int y);
void Map_Create(void);
void Snake_Init(void);
void Pause(void);
void Game_Control(void);
void Game_Init(void);
void Game_End(void);
void Wall_Cross(SNAKE *s);
void Snake_Move(void);
unsigned char Bit_Self(SNAKE *s);
void Debug(void);
/*
***主函数
*/
unsigned char main()
{
	Game_Init();
	Game_Control();
	//Game_End();  
	return 0;
}
/****************************************************************
* Function Name: Pos_Set
* Description  : 设置光标位置
* Parameter    : unsigned int x, unsigned int y
* Return       : void
***************************************************************/
void Pos_Set(unsigned int x, unsigned int y)
{
	COORD pos;
	HANDLE houtput;
	pos.X = x;
	pos.Y = y;
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(houtput, pos);
}
/****************************************************************
* Function Name: Map_Create
* Description  : 创建地图
* Parameter    : void
* Return       : void
***************************************************************/
void Map_Create(void)
{
	unsigned int i = 0;
	for (i = 0; i <= MAP_WIDTH; i++) // 上下边框 
	{
		Pos_Set(2 * i, 0);
		printf("+");
		Pos_Set(2 * i, MAP_HEIGHT);
		printf("+");
	}

	for (i = 0; i <= MAP_HEIGHT; i++)
	{
		Pos_Set(0, i);
		printf("+");
		Pos_Set(2 * MAP_WIDTH, i);
		printf("+");
	}
}
/****************************************************************
* Function Name: Snake_Init()
* Description  : 蛇的初始化
* Parameter    : void
* Return       : void
***************************************************************/
void Snake_Init(void)
{
	SNAKE *tail;
	unsigned int i = 0;
	head = (SNAKE *)malloc(sizeof(SNAKE));
	head->x = 12 * 2;
	head->y = 12;
	head->next = NULL;
	q = head;

	for (i = 1; i <= 1; i++)
	{
		tail = (SNAKE *)malloc(sizeof(SNAKE));
		tail->x = 12 * 2 + 2 * i;
		tail->y = 12;
		q->next = tail; //上一节点的next指向tail  
		q = q->next;//or q = tail //q移动指向tail          q充当指挥者 
	}
	tail->next = NULL;
	q = head;//q 指向头 

	while (q != NULL)
	{
		Pos_Set(q->x, q->y);
		printf("*");
		q = q->next;
	}
}
/****************************************************************
* Function Name: Food_Create()
* Description  : 创造食物
* Parameter    : void
* Return       : void
***************************************************************/
void Food_Create(void)
{
	SNAKE *food_1;
	srand((unsigned)time(NULL));
	food_1 = (SNAKE *)malloc(sizeof(SNAKE));
	food_1->x = 2 * (rand() % (MAP_WIDTH - 1) + 1);
	food_1->y = rand() % (MAP_HEIGHT - 1) + 1;
	q = head;

	while (q != NULL)
	{
		if (q->x == food_1->x && q->y == food_1->y)
		{
			food_1->x = 2 * (rand() % (MAP_WIDTH - 1) + 1);
			food_1->y = rand() % (MAP_HEIGHT - 1) + 1;
			q = head;
		}
		else
		{
			q = q->next;
		}
	}

	Pos_Set(food_1->x, food_1->y);
	printf("★");
	food = food_1;
}
/****************************************************************
* Function Name: Wall_Cross
* Description  : 判断是否撞墙
* Parameter    : SNAKE *s
* Return       :  void
***************************************************************/
void Wall_Cross(SNAKE *s)
{

	if (s->x == 0 || s->x == MAP_WIDTH * 2 || s->y == 0 || s->y == MAP_HEIGHT)
	{
		Game_status = 1;
		Game_End();
	}
}
/****************************************************************
* Function Name: Bit_Self
* Description  : 判断蛇是否要到自己
* Parameter    : SNAKE *s
* Return       : 0 没有咬到自己
: 1 咬到自己
***************************************************************/
unsigned char Bit_Self(SNAKE *s)
{
	q = head;
	while (q != NULL)
	{
		if ((q->x == s->x) && (q->y == s->y))
		{
			return 1;
		}
		q = q->next;
	}
	return 0;
}
/****************************************************************
* Function Name: Snake_Move()
* Description  : 蛇的运动:上UP 下DOWN 左LEFT右RIGHT
* Parameter    : void
* Return       : void
***************************************************************/
void Snake_Move(void)
{
	SNAKE * head_next;
	head_next = (SNAKE *)malloc(sizeof(SNAKE));

	if (Direction == UP)
	{
		head_next->x = head->x;
		head_next->y = head->y - 1;
	}
	else if (Direction == DOWN)
	{
		head_next->x = head->x;
		head_next->y = head->y + 1;
	}
	else if (Direction == LEFT)
	{
		head_next->x = head->x - 2;
		head_next->y = head->y;
	}
	else if (Direction == RIGHT)
	{
		head_next->x = head->x + 2;
		head_next->y = head->y;
	}
	Wall_Cross(head_next);//是否撞墙 
	if (Bit_Self(head_next) == 1)//是否咬到自己 
	{
		Game_status = 2;
		Game_End();
	}
	if (head_next->x == food->x && head_next->y == food->y)//有食物 
	{

		head_next->next = head;
		head = head_next;
		q = head;
		while (q != NULL)//加上新蛇头，全都画 
		{
			Pos_Set(q->x, q->y);
			printf("*");
			q = q->next;
		}
		Score += Score_Add;
		Food_Create();
		if (Time_sleep > 20)
		{
			Time_sleep -= 20;
			Score_Add += 5;
		}
	}
	else//没有食物 
	{
		head_next->next = head;
		head = head_next;
		q = head;
		while (q->next->next != NULL)//加上新蛇头，最后一个尾巴不画 
		{
			Pos_Set(q->x, q->y);
			printf("*");
			q = q->next;
		}
		Pos_Set(q->next->x, q->next->y);
		printf(" ");
		free(q->next);
		q->next = NULL;
	}
}
/****************************************************************
* Function Name: Game_Control
* Description  : 控制游戏
* Parameter    : void
* Return       : void
***************************************************************/
void Game_Control(void)
{
	Pos_Set(64, 14);
	printf("撞墙---->dead、咬到自己---->dead");
	Pos_Set(64, 15);
	printf("用↑、↓、←、→控制贪吃蛇运动方向");
	Pos_Set(64, 16);
	printf("ESC:   退出游戏，SPACE:  暂停游戏");
	Direction = DOWN;
	while (1)
	{
		Pos_Set(64, 10);
		printf("得分: %d分", Score);
		Pos_Set(64, 11);
		printf("每个食物得分: %d", Score_Add);

		if (GetAsyncKeyState(VK_UP) && (Direction != DOWN))
		{
			Direction = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN) && (Direction != UP))
		{
			Direction = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT) && (Direction != RIGHT))
		{
			Direction = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && (Direction != LEFT))
		{
			Direction = RIGHT;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			Pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			Game_status = 3;
		}
		Sleep(Time_sleep);
		Snake_Move();
	}
}
/****************************************************************
* Function Name: Pause
* Description  : 暂停
* Parameter    : void
* Return       : void
***************************************************************/
void Pause(void)
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}
/****************************************************************
* Function Name: WelcomeToGame
* Description      : 开始界面
* Parameter         : void
* Return              :  void
***************************************************************/
void  WelcomeToGame(void)
{
	Pos_Set(40, 12);
	//system("title C语言程序游戏之<贪吃蛇>");  
	Pos_Set(40, 25);
	printf("作者：一只大猫\n");
	system("pause");
	system("cls");
	Pos_Set(25, 13);
	printf("蛇身越长，速度越快。\n");
	system("pause");
	system("cls");
}
/****************************************************************
* Function Name: Game_End
* Description      : 游戏结束
* Parameter         : void
* Return              :  void
***************************************************************/
void Game_End(void)
{
	system("cls");
	Pos_Set(24, 12);
	if (Game_status == 1)
	{
		printf("对不起。您装到墙了，游戏结束，北北...\n");
	}
	else if (Game_status == 2)
	{
		printf("对不起。您咬到自己了，游戏结束，北北...");
	}
	else if (Game_status == 3)
	{
		printf("游戏结束，北北...");
	}
	Pos_Set(24, 13);
	printf("您的得分是：%d 分", Score);
	system("pause");
	exit(0);
}
/****************************************************************
* Function Name: Game_Init
* Description      : 游戏初始化
* Parameter         : void
* Return              :  void
***************************************************************/
void Game_Init(void)
{
	system("mode  con  cols=100  lines=100");
	WelcomeToGame();
	Map_Create();
	Snake_Init();
	Food_Create();
}


