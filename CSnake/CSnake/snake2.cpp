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
#include <Windows.h>//����WinCon.h  
#include <stdio.h>  
#include <time.h>  
#include <stdlib.h>  
/*
***�궨��
*/
#define  MAP_WIDTH  25  
#define  MAP_HEIGHT 15  
#define H2D 17

#define  UP         1  
#define  DOWN       2  
#define  LEFT       3  
#define RIGHT       4  

/*
***�ṹ��
*/
typedef struct snake//�����һ���ڵ� 
{
	unsigned int x, y;
	struct snake *next;
}SNAKE;
/*
***ȫ�ֱ���
*/
unsigned int Score = 0, Score_Add = 10;
unsigned int Direction, Time_sleep = 1000;
unsigned int Direction2;
SNAKE *head, *food;//��ͷָ�룬ʳ��ָ�� 
SNAKE *head2, *food2;//��ͷָ�룬ʳ��ָ�� 
SNAKE *q;//�������ж��ߵ�ʱ���õ���ָ�� 
SNAKE *q2;//�������ж��ߵ�ʱ���õ���ָ�� 
unsigned char Game_status = 0;// ��Ϸ�������������ײ��ǽ����ҧ���Լ����������˳���Ϸ�� 
							  /*
							  ***��������
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

void Map_Create2(void);
void Snake_Init2(void);
void Game_Init2(void);
void Wall_Cross2(SNAKE *s);
void Snake_Move2(void);
unsigned char Bit_Self2(SNAKE *s);
/*
***������
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
* Description  : ���ù��λ��
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
* Description  : ������ͼ
* Parameter    : void
* Return       : void
***************************************************************/
void Map_Create(void)
{
	unsigned int i = 0;
	for (i = 0; i <= MAP_WIDTH; i++) // ���±߿� 
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

void Map_Create2(void)
{
	unsigned int i = 0;
	for (i = 0; i <= MAP_WIDTH; i++) // ���±߿� 
	{
		Pos_Set(2 * i, 0 + H2D);
		printf("+");
		Pos_Set(2 * i, MAP_HEIGHT + H2D);
		printf("+");
	}

	for (i = 0; i <= MAP_HEIGHT; i++)
	{
		Pos_Set(0, i + H2D);
		printf("+");
		Pos_Set(2 * MAP_WIDTH, i + H2D);
		printf("+");
	}
}

/****************************************************************
* Function Name: Snake_Init()
* Description  : �ߵĳ�ʼ��
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
		q->next = tail; //��һ�ڵ��nextָ��tail  
		q = q->next;//or q = tail //q�ƶ�ָ��tail          q�䵱ָ���� 
	}
	tail->next = NULL;
	q = head;//q ָ��ͷ 

	while (q != NULL)
	{
		Pos_Set(q->x, q->y);
		printf("*");
		q = q->next;
	}
}

void Snake_Init2(void)
{
	SNAKE *tail2;
	unsigned int i = 0;
	head2 = (SNAKE *)malloc(sizeof(SNAKE));
	head2->x = 12 * 2;
	head2->y = 12 + H2D;
	head2->next = NULL;
	q2 = head2;

	for (i = 1; i <= 1; i++)
	{
		tail2 = (SNAKE *)malloc(sizeof(SNAKE));
		tail2->x = 12 * 2 + 2 * i;
		tail2->y = 12 + H2D;
		q2->next = tail2; //��һ�ڵ��nextָ��tail2  
		q2 = q2->next;//or q2 = tail2 //q2�ƶ�ָ��tail2          q2�䵱ָ���� 
	}
	tail2->next = NULL;
	q2 = head2;//q2 ָ��ͷ 

	while (q2 != NULL)
	{
		Pos_Set(q2->x, q2->y);
		printf("*");
		q2 = q2->next;
	}
}
/****************************************************************
* Function Name: Food_Create()
* Description  : ����ʳ��
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
	printf("��");
	food = food_1;
}

void Food_Create2(void)
{
	SNAKE *food_2;
	srand((unsigned)time(NULL));
	food_2 = (SNAKE *)malloc(sizeof(SNAKE));
	food_2->x = 2 * (rand() % (MAP_WIDTH - 1) + 1);
	food_2->y = rand() % (MAP_HEIGHT - 1) + 1 + H2D;
	q2 = head2;

	while (q2 != NULL)
	{
		if (q2->x == food_2->x && q2->y == food_2->y)
		{
			food_2->x = 2 * (rand() % (MAP_WIDTH - 1) + 1);
			food_2->y = rand() % (MAP_HEIGHT - 1) + 1 + H2D;
			q2 = head2;
		}
		else
		{
			q2 = q2->next;
		}
	}

	Pos_Set(food_2->x, food_2->y);
	printf("��");
	food2 = food_2;
}
/****************************************************************
* Function Name: Wall_Cross
* Description  : �ж��Ƿ�ײǽ
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
void Wall_Cross2(SNAKE *s)
{

	if (s->x == 0 || s->x == MAP_WIDTH * 2 || s->y == 0 + H2D || s->y == MAP_HEIGHT + H2D)
	{
		Game_status = 1;
		Game_End();
	}
}
/****************************************************************
* Function Name: Bit_Self
* Description  : �ж����Ƿ�Ҫ���Լ�
* Parameter    : SNAKE *s
* Return       : 0 û��ҧ���Լ�
: 1 ҧ���Լ�
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
unsigned char Bit_Self2(SNAKE *s)
{
	q2 = head2;
	while (q2 != NULL)
	{
		if ((q2->x == s->x) && (q2->y == s->y))
		{
			return 1;
		}
		q2 = q2->next;
	}
	return 0;
}
/****************************************************************
* Function Name: Snake_Move()
* Description  : �ߵ��˶�:��UP ��DOWN ��LEFT��RIGHT
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
	Wall_Cross(head_next);//�Ƿ�ײǽ 
	if (Bit_Self(head_next) == 1)//�Ƿ�ҧ���Լ� 
	{
		Game_status = 2;
		Game_End();
	}
	if (head_next->x == food->x && head_next->y == food->y)//��ʳ�� 
	{

		head_next->next = head;
		head = head_next;
		q = head;
		while (q != NULL)//��������ͷ��ȫ���� 
		{
			Pos_Set(q->x, q->y);
			printf("*");
			q = q->next;
		}
		Score += Score_Add;
		Food_Create();
		//if (Time_sleep > 20)
		//{
		//	Time_sleep -= 20;
		//	Score_Add += 5;
		//}
	}
	else//û��ʳ�� 
	{
		head_next->next = head;
		head = head_next;
		q = head;
		while (q->next->next != NULL)//��������ͷ�����һ��β�Ͳ��� 
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


void Snake_Move2(void)
{
	SNAKE * head_next2;
	head_next2 = (SNAKE *)malloc(sizeof(SNAKE));

	if (Direction2 == UP)
	{
		head_next2->x = head2->x;
		head_next2->y = head2->y - 1;
	}
	else if (Direction2 == DOWN)
	{
		head_next2->x = head2->x;
		head_next2->y = head2->y + 1;
	}
	else if (Direction2 == LEFT)
	{
		head_next2->x = head2->x - 2;
		head_next2->y = head2->y;
	}
	else if (Direction2 == RIGHT)
	{
		head_next2->x = head2->x + 2;
		head_next2->y = head2->y;
	}
	//Wall_Cross2(head_next2);//�Ƿ�ײǽ 
	//if (Bit_Self2(head_next2) == 1)//�Ƿ�ҧ���Լ� 
	//{
	//	Game_status = 2;
	//	Game_End();
	//}
	if (head_next2->x == food2->x && head_next2->y == food2->y)//��ʳ�� 
	{

		head_next2->next = head2;
		head2 = head_next2;
		q2 = head2;
		while (q2 != NULL)//��������ͷ��ȫ���� 
		{
			Pos_Set(q2->x, q2->y);
			printf("*");
			q2 = q2->next;
		}
		Score += Score_Add;
		Food_Create2();
		//if (Time_sleep > 20)
		//{
		//	Time_sleep -= 20;
		//	Score_Add += 5;
		//}
	}
	else//û��ʳ�� 
	{
		head_next2->next = head2;
		head2 = head_next2;
		q2 = head2;
		while (q2->next->next != NULL)//��������ͷ�����һ��β�Ͳ��� 
		{
			Pos_Set(q2->x, q2->y);
			printf("*");
			q2 = q2->next;
		}
		Pos_Set(q2->next->x, q2->next->y);
		printf(" ");
		free(q2->next);
		q2->next = NULL;
	}
}
/****************************************************************
* Function Name: Game_Control
* Description  : ������Ϸ
* Parameter    : void
* Return       : void
***************************************************************/
void Game_Control(void)
{
	Pos_Set(64, 14);
	printf("ײǽ---->dead��ҧ���Լ�---->dead");
	Pos_Set(64, 15);
	printf("�á�����������������̰�����˶�����");
	Pos_Set(64, 16);
	printf("ESC:   �˳���Ϸ��SPACE:  ��ͣ��Ϸ");
	Direction = DOWN;
	while (1)
	{
		Pos_Set(64, 10);
		printf("�÷�: %d��", Score);
		Pos_Set(64, 11);
		printf("ÿ��ʳ��÷�: %d", Score_Add);

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
		//2--
		else if (GetAsyncKeyState('W') && (Direction2 != DOWN))
		{
			Direction2 = UP;
		}
		else if (GetAsyncKeyState('S') && (Direction2 != UP))
		{
			Direction2 = DOWN;
		}
		else if (GetAsyncKeyState('A') && (Direction2 != RIGHT))
		{
			Direction2 = LEFT;
		}
		else if (GetAsyncKeyState('D') && (Direction2 != LEFT))
		{
			Direction2 = RIGHT;
		}
		//--2
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
		Snake_Move2();
	}
}
/****************************************************************
* Function Name: Pause
* Description  : ��ͣ
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
* Description      : ��ʼ����
* Parameter         : void
* Return              :  void
***************************************************************/
void  WelcomeToGame(void)
{
	Pos_Set(40, 12);
	//system("title C���Գ�����Ϸ֮<̰����>");  
	Pos_Set(40, 25);
	printf("���ߣ�һֻ��è\n");
	system("pause");
	system("cls");
	Pos_Set(25, 13);
	printf("����Խ�����ٶ�Խ�졣\n");
	system("pause");
	system("cls");
}
/****************************************************************
* Function Name: Game_End
* Description      : ��Ϸ����
* Parameter         : void
* Return              :  void
***************************************************************/
void Game_End(void)
{
	system("cls");
	Pos_Set(24, 12);
	if (Game_status == 1)
	{
		printf("�Բ�����װ��ǽ�ˣ���Ϸ����������...\n");
	}
	else if (Game_status == 2)
	{
		printf("�Բ�����ҧ���Լ��ˣ���Ϸ����������...");
	}
	else if (Game_status == 3)
	{
		printf("��Ϸ����������...");
	}
	Pos_Set(24, 13);
	printf("���ĵ÷��ǣ�%d ��", Score);
	system("pause");
	exit(0);
}
/****************************************************************
* Function Name: Game_Init
* Description      : ��Ϸ��ʼ��
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
	Game_Init2();
}

void Game_Init2(void)
{
	Map_Create2();
	Snake_Init2();
	Food_Create2();
}

