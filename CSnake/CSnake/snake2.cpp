#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
typedef struct _StuFrame
{
<<<<<<< HEAD
	unsigned int x, y;
	struct snake *next;
}SNAKE;
/*
***全局变量
*/
unsigned int Score = 0, Score2 = 0, Score_Add = 10;
unsigned int Direction, Time_sleep = 300;
unsigned int Direction2;
SNAKE *head, *food;//蛇头指针，食物指针 
SNAKE *head2, *food2;//蛇头指针，食物指针 
SNAKE *q;//遍历和判断蛇的时候用到的指针 
SNAKE *q2;//遍历和判断蛇的时候用到的指针 
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

void Map_Create2(void);
void Snake_Init2(void);
void Game_Init2(void);
void Wall_Cross2(SNAKE *s);
void Snake_Move2(void);
unsigned char Bit_Self2(SNAKE *s);
/*
***主函数
*/
unsigned char main()
=======
	int nLeft;
	int nTop;
	int nHeight;
	int nWidth;
}StuFrame;

typedef struct _StuPoint
>>>>>>> a25de01365e604929d3ac5c9cdf24d572c14aed5
{
	int nX;
	int nY;
} StuPoint;

typedef enum _EN_DIRECTION  /** 方向 **/
{
	EN_UP,
	EN_DOWN,
	EN_LEFT,
	EN_RIGHT,
} EN_DIRECTION;

typedef struct _StuSnake
{
	char strDirectKey[4];
	StuFrame frame;     /** 边框属性 **/

	StuPoint snake[200];
	int nSnakeLen;

	EN_DIRECTION enDirection; /**方向 **/

	BOOL bContinue;

	StuPoint foodPoint;
	BOOL bFoodValid;

	StuPoint bombPoint;/** 炸弹 **/
	BOOL bBombValid;

	StuPoint wallPoint[100];/** 障碍物 **/
	int nWallCount;

	int score;
} StuSnake;
StuSnake g_snake[10];//snake
int g_nSnakeLen = 0; //number
void changeCursor(int nX, int nY)
{
	COORD dwCursorPosition;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == hOutput)
	{
		printf("GetStdHandle error!\n");
		//return -1;
	}
	dwCursorPosition.X = nX;
	dwCursorPosition.Y = nY;
	if (!SetConsoleCursorPosition(hOutput, dwCursorPosition))
	{
		printf("SetConsoleCursorPosition error!\n");
		//return -1;
	}
}
BOOL drawFrame(int nXStart, int nYStart, int nRow, int nCol)
{
	int nColIndex = 0;
	int nRowIndex = 0;

	changeCursor(nXStart * 2, nYStart);
	for (nColIndex = 1; nColIndex <= nCol; nColIndex++)
	{
		printf("★");
	}

	for (nRowIndex = 1; nRowIndex <= nRow - 2; nRowIndex++)
	{
		changeCursor(nXStart * 2, nYStart + nRowIndex); printf("★");
		changeCursor((nXStart + nCol - 1) * 2, nYStart + nRowIndex); printf("★");
	}
	changeCursor(nXStart * 2, nYStart + nRow - 1);
	for (nColIndex = 1; nColIndex <= nCol; nColIndex++)
	{
		printf("★");
	}
	return TRUE;
};
BOOL init_snake(StuSnake * pSnake,
	int nLeft, int nTop,
	int nWidth, int nHeight,
	char cUp, char cDown,
	char cLeft, char cRight)
{
	(*pSnake).frame.nLeft = nLeft;
	(*pSnake).frame.nTop = nTop;
	(*pSnake).frame.nHeight = nHeight;
	(*pSnake).frame.nWidth = nWidth;

	drawFrame(nLeft, nTop, nHeight, nWidth);

	(*pSnake).nSnakeLen = 3;
	(*pSnake).snake[0].nX = ((*pSnake).frame.nLeft + 2) + 0 * 2;
	(*pSnake).snake[0].nY = (*pSnake).frame.nTop + (*pSnake).frame.nHeight / 2;
	(*pSnake).snake[1].nX = ((*pSnake).frame.nLeft + 2) + 1 * 2;
	(*pSnake).snake[1].nY = (*pSnake).frame.nTop + (*pSnake).frame.nHeight / 2;
	(*pSnake).snake[2].nX = ((*pSnake).frame.nLeft + 2) + 2 * 2;
	(*pSnake).snake[2].nY = (*pSnake).frame.nTop + (*pSnake).frame.nHeight / 2;

	(*pSnake).bContinue = TRUE;
	(*pSnake).enDirection = EN_RIGHT;

	(*pSnake).strDirectKey[EN_UP] = cUp;
	(*pSnake).strDirectKey[EN_DOWN] = cDown;
	(*pSnake).strDirectKey[EN_LEFT] = cLeft;
	(*pSnake).strDirectKey[EN_RIGHT] = cRight;

	(*pSnake).foodPoint.nX = 0;
	(*pSnake).foodPoint.nY = 0;
	(*pSnake).bFoodValid = FALSE;

	(*pSnake).bombPoint.nX = 0;
	(*pSnake).bombPoint.nY = 0;
	(*pSnake).bBombValid = FALSE;

	(*pSnake).nWallCount = 0;
	(*pSnake).score = 0;

	return TRUE;
}
void showWaiting()
{
	printf("载入中.");
	Sleep(300);
	printf("..");
	Sleep(200);
	printf("..");
	Sleep(200);
	printf("...");
	Sleep(100);
	printf("..");
}
int chooseAmountMan()
{
	int tempt, nTime;
	int ny = 5, nx = 5, length = 10, height = 10;
	drawFrame(nx, ny, height, length);
	changeCursor(nx * 2, ny - 3);
	printf("★贪吃蛇双人对战版★");
	changeCursor(nx * 2, ny - 1);
	printf("★    人数选择    ★");
	changeCursor(nx * 2 + length / 3, ny + 3);
	printf("1 单人模式");
	changeCursor(nx * 2 + length / 3, ny + 4);
	printf("2 双人对战");
	changeCursor(nx * 2, ny + height);
	printf("输入序号：");
	scanf("%d", &tempt);
	showWaiting();
	system("cls");
	return tempt;
}
/*******************************************/
BOOL initSnakeManager()
{
	int amountMan;
	amountMan = chooseAmountMan();//选择小蛇数量

	switch (amountMan)
	{
	case 1:
		init_snake(&g_snake[0], 1, 3, 18, 18, 'w', 's', 'a', 'd');  /** 小蛇n,nx,ny,width,height，操作 **/
		g_nSnakeLen = 1;
		break;
	case 2:
		init_snake(&g_snake[0], 1, 3, 18, 18, 'w', 's', 'a', 'd');  /** 小蛇n,nx,ny,width,height，操作 **/
		init_snake(&g_snake[1], 20, 3, 18, 18, '8', '2', '4', '6');
		g_nSnakeLen = 2;
		break;
	default:
		changeCursor(1, 3);
		printf("输入错误!默认单人!");
		showWaiting();
		Sleep(3000);
		init_snake(&g_snake[0], 1, 3, 18, 18, 'w', 's', 'a', 'd');  /** 小蛇n,nx,ny,width,height，操作 **/
		g_nSnakeLen = 1;
		break;
	}
	//init_snake(&g_snake[2], 1, 23, 18, 18, 'i', 'k', 'j', 'l');

	return TRUE;
}
int GetSnakeNumber()
{
	return g_nSnakeLen;
}
StuSnake GetSnake(int nIndex)
{
	StuSnake snake;
	if (nIndex < 0 || nIndex >= g_nSnakeLen)
		return snake;

	return g_snake[nIndex];
}
BOOL UpdateSnake(StuSnake snake, int nIndex)
{
	if (nIndex < 0 || nIndex >= g_nSnakeLen)
		return FALSE;

	g_snake[nIndex] = snake;
	return TRUE;
}


int chooseLevel()
{
	int tempt, nTime;
	int ny = 5, nx = 20, length = 10, height = 10;
	drawFrame(nx, ny, height, length);
	changeCursor(nx * 2, ny - 3);
	printf("★贪吃蛇双人对战版★");
	changeCursor(nx * 2, ny - 1);
	printf("★    难度选择    ★");
	changeCursor(nx * 2 + length / 3, ny + 3);
	printf("1 初级");
	changeCursor(nx * 2 + length / 3, ny + 4);
	printf("2 正常");
	changeCursor(nx * 2 + length / 3, ny + 5);
	printf("3 高级");
	changeCursor(nx * 2 + length / 3, ny + 6);
	printf("4 大神");
	changeCursor(nx * 2 + length / 3, ny + 7);
	printf("5 无解模式");

	changeCursor(nx * 2, ny + height);
	printf("等级：");
	scanf("%d", &tempt);
	changeCursor(nx * 2, ny + height + 1);
	switch (tempt)
	{
	case 1:
		nTime = 1000;
		break;
	case 2:
		nTime = 500;
		break;
	case 3:
		nTime = 200;
		break;
	case 4:
		nTime = 80;
		break;
	case 5:
		nTime = 20;
		break;
	default:
		printf("输入错误!将采用正常等级");
		nTime = 500;
		break;
	}
	//system("cls");
	return nTime;
}


void Hint()//签名
{
	changeCursor(4, 0);
	printf("玩家 1: w s a d(上/下/左/右)");
	changeCursor(4, 1);
	printf("玩家 2: 8 2 4 6(上/下/左/右)");
	printf("\t\t\t★★梁先生★★");
	changeCursor(28, 2);
	printf("★贪吃蛇双人对战版★");
}
BOOL init()
{
	srand((unsigned)time(NULL));
	initSnakeManager();
	Hint();
	return TRUE;
}
BOOL isContinue()
{
	int nCount = GetSnakeNumber();
	StuSnake snake;
	int nStopCount = 0;
	int nSnakeIndex = 0;

	for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
	{
		snake = GetSnake(nSnakeIndex);
		if (!snake.bContinue)
			nStopCount++;
	}
	if (nCount == nStopCount)
		return FALSE;
	else
		return TRUE;
}
BOOL clean()
{
	int nSnakeIndex = 0;
	int nIndex = 0;
	StuSnake snake;

	for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
	{
		snake = GetSnake(nSnakeIndex);
		if (snake.bContinue)
		{
			for (nIndex = 0; nIndex < snake.nSnakeLen; nIndex++)
			{
				changeCursor(snake.snake[nIndex].nX * 2, snake.snake[nIndex].nY);
				printf("  ");
			}
			changeCursor(snake.foodPoint.nX * 2, snake.foodPoint.nY);
			printf("  ");
			changeCursor(snake.bombPoint.nX * 2, snake.bombPoint.nY);
			printf("  ");
		}
	}
	return TRUE;
}
BOOL input()
{
	int nSnakeIndex = 0;
	char c = '0';
	char strInput[1024] = { 0 };
	StuSnake snake;
	int nIndex = 0;
	int nCount = 0;
	int nStrIndex = 0;
	while (kbhit()) /** 提取缓冲区数据 kbhit判断有无输入**/
	{
		strInput[nCount] = getch();
		nCount++;
	}
	for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
	{
		snake = GetSnake(nSnakeIndex);
		char cReult = 0;
		for (nStrIndex = 0; nStrIndex<nCount; nStrIndex++)
		{
			if (strInput[nStrIndex] == snake.strDirectKey[EN_UP]
				|| strInput[nStrIndex] == snake.strDirectKey[EN_DOWN]
				|| strInput[nStrIndex] == snake.strDirectKey[EN_LEFT]
				|| strInput[nStrIndex] == snake.strDirectKey[EN_RIGHT] || strInput[nStrIndex] == 0x1b)
				cReult = strInput[nStrIndex];
		}
		if (cReult == snake.strDirectKey[EN_UP])
		{
			if (EN_UP == snake.enDirection
				|| EN_DOWN == snake.enDirection)
				break;
			snake.enDirection = EN_UP;
		}
<<<<<<< HEAD
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
=======
		else if (cReult == snake.strDirectKey[EN_DOWN])
		{
			if (EN_UP == snake.enDirection
				|| EN_DOWN == snake.enDirection)
				break;
			snake.enDirection = EN_DOWN;
		}
		else if (cReult == snake.strDirectKey[EN_LEFT])
>>>>>>> a25de01365e604929d3ac5c9cdf24d572c14aed5
		{
			if (EN_LEFT == snake.enDirection
				|| EN_RIGHT == snake.enDirection)
				break;
			snake.enDirection = EN_LEFT;
		}
		else if (cReult == snake.strDirectKey[EN_RIGHT])
		{
			if (EN_LEFT == snake.enDirection
				|| EN_RIGHT == snake.enDirection)
				break;
			snake.enDirection = EN_RIGHT;
		};
		if (cReult == 0x1b)
		{
			snake.bContinue = FALSE;
		};

		if (!UpdateSnake(snake, nSnakeIndex))
			exit(0);
	}
	return TRUE;
}
void createWallForOther(int nIndex)
{
<<<<<<< HEAD
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
	Wall_Cross2(head_next2);//是否撞墙 
	if (Bit_Self2(head_next2) == 1)//是否咬到自己 
	{
		Game_status = 2;
		Game_End();
	}
	if (head_next2->x == food2->x && head_next2->y == food2->y)//有食物 
=======
	int nSnakeIndex = 0;
	StuPoint point;
	StuSnake snake;
	for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
>>>>>>> a25de01365e604929d3ac5c9cdf24d572c14aed5
	{
		if (nSnakeIndex == nIndex)/** 对敌方产生障碍**/
			continue;

<<<<<<< HEAD
		head_next2->next = head2;
		head2 = head_next2;
		q2 = head2;
		while (q2 != NULL)//加上新蛇头，全都画 
		{
			Pos_Set(q2->x, q2->y);
			printf("*");
			q2 = q2->next;
		}
		Score2 += Score_Add;
		Food_Create2();
		if (Time_sleep > 20)
		{
			Time_sleep -= 20;
			Score_Add += 5;
		}
	}
	else//没有食物 
	{
		head_next2->next = head2;
		head2 = head_next2;
		q2 = head2;
		while (q2->next->next != NULL)//加上新蛇头，最后一个尾巴不画 
		{
			Pos_Set(q2->x, q2->y);
			printf("*");
			q2 = q2->next;
		}
		Pos_Set(q2->next->x, q2->next->y);
		printf(" ");
		free(q2->next);
		q2->next = NULL;
=======
		snake = GetSnake(nSnakeIndex);
		point.nX = snake.frame.nLeft + 1 + rand() % (snake.frame.nWidth - 2);
		point.nY = snake.frame.nTop + 1 + rand() % (snake.frame.nHeight - 2);
		snake.wallPoint[snake.nWallCount] = point;
		snake.nWallCount++;
		if (!UpdateSnake(snake, nSnakeIndex))
			exit(0);
>>>>>>> a25de01365e604929d3ac5c9cdf24d572c14aed5
	}
}
BOOL step()
{
<<<<<<< HEAD
	Pos_Set(64, 14);
	printf("撞墙---->dead、咬到自己---->dead");
	Pos_Set(64, 15);
	printf("用↑、↓、←、→控制贪吃蛇运动方向");
	Pos_Set(64, 16);
	printf("ESC:   退出游戏，SPACE:  暂停游戏");
	Direction = DOWN;
	Direction2 = DOWN;
	while (1)
	{
		Pos_Set(64, 10);
		printf("选手1得分: %d分", Score);
		Pos_Set(64, 10 + H2D);
		printf("选手2得分: %d分", Score2);
		Pos_Set(64, 11);
		printf("每个食物得分: %d", Score_Add);
		if (0)
		{
		}
		else if (GetAsyncKeyState(VK_UP) && (Direction != DOWN))
		{
			Direction = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN) && (Direction != UP))
=======
	int nIndex = 0;
	int nSnakeIndex = 0;
	int nSnakeBodyIndex = 0;
	int nWallIndex = 0;
	StuSnake snake;
	StuPoint point;
	for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
	{
		snake = GetSnake(nSnakeIndex);

		point.nX = snake.snake[snake.nSnakeLen - 1].nX;
		point.nY = snake.snake[snake.nSnakeLen - 1].nY;
		switch (snake.enDirection)
>>>>>>> a25de01365e604929d3ac5c9cdf24d572c14aed5
		{
		case EN_UP:
			point.nY -= 1;
			break;
		case EN_DOWN:
			point.nY += 1;
			break;
		case EN_LEFT:
			point.nX -= 1;
			break;
		case EN_RIGHT:
			point.nX += 1;
			break;
		}
		/** eat food **/
		if (snake.bFoodValid&& point.nY == snake.foodPoint.nY && point.nX == snake.foodPoint.nX)
		{
			snake.snake[snake.nSnakeLen].nX = snake.foodPoint.nX;
			snake.snake[snake.nSnakeLen].nY = snake.foodPoint.nY;
			snake.nSnakeLen++;
			snake.score++;
			snake.bFoodValid = FALSE;
		}
		else
		{
			for (nIndex = 0; nIndex < snake.nSnakeLen - 1; nIndex++)
			{
				snake.snake[nIndex].nX = snake.snake[nIndex + 1].nX;
				snake.snake[nIndex].nY = snake.snake[nIndex + 1].nY;
			}
			snake.snake[snake.nSnakeLen - 1].nX = point.nX;
			snake.snake[snake.nSnakeLen - 1].nY = point.nY;
		}

		/** eat bomb **/
		if (snake.bBombValid && point.nY == snake.bombPoint.nY&& point.nX == snake.bombPoint.nX)
		{
			createWallForOther(nSnakeIndex);
			snake.score--;
			snake.bBombValid = FALSE;
		}
		/** create food **/
		if (!snake.bFoodValid)
		{
			snake.foodPoint.nX = snake.frame.nLeft + 1 + rand() % (snake.frame.nWidth - 2);
			snake.foodPoint.nY = snake.frame.nTop + 1 + rand() % (snake.frame.nHeight - 2);
			snake.bFoodValid = TRUE; /** 有食物 **/
		}
		/** create bomb **/
		if (!snake.bBombValid)
		{
			snake.bombPoint.nX = snake.frame.nLeft + 1 + rand() % (snake.frame.nWidth - 2);
			snake.bombPoint.nY = snake.frame.nTop + 1 + rand() % (snake.frame.nHeight - 2);
			snake.bBombValid = TRUE;
		}
		/** 超出边界 返回FALSE touch frame **/
		if (snake.snake[snake.nSnakeLen - 1].nY >= snake.frame.nTop + snake.frame.nHeight - 1
			|| snake.snake[snake.nSnakeLen - 1].nY <= snake.frame.nTop
			|| snake.snake[snake.nSnakeLen - 1].nX >= snake.frame.nLeft + snake.frame.nWidth - 1
			|| snake.snake[snake.nSnakeLen - 1].nX <= snake.frame.nLeft)
		{
			snake.bContinue = FALSE;
			//return FALSE;
		}
		/** self **/
		for (nSnakeBodyIndex = 0; nSnakeBodyIndex < snake.nSnakeLen - 1; nSnakeBodyIndex++)
		{
			if (snake.snake[snake.nSnakeLen - 1].nY == snake.snake[nSnakeBodyIndex].nY
				&& snake.snake[snake.nSnakeLen - 1].nX == snake.snake[nSnakeBodyIndex].nX)
				snake.bContinue = FALSE;
		}
		for (nWallIndex = 0; nWallIndex < snake.nWallCount; nWallIndex++)
		{
			if (point.nY == snake.wallPoint[nWallIndex].nY
				&& point.nX == snake.wallPoint[nWallIndex].nX)
			{
				snake.bContinue = FALSE;
			}
		}
		if (!UpdateSnake(snake, nSnakeIndex))
			exit(0);
	}
	return TRUE;
}

BOOL draw()
{
	int nIndex = 0;
	int nSnakeIndex = 0;
	int nWallIndex = 0;
	StuSnake snake;

	for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
	{
		snake = GetSnake(nSnakeIndex);  /** 小蛇 n **/
		if (snake.bContinue)//判断小蛇是否健在
		{
			for (nIndex = 0; nIndex < snake.nSnakeLen; nIndex++)
			{
				changeCursor(snake.snake[nIndex].nX * 2, snake.snake[nIndex].nY);
				printf("■");
			}
			if (snake.bFoodValid)
			{
				changeCursor(snake.foodPoint.nX * 2, snake.foodPoint.nY);
				printf("●");
			}
			if (snake.bBombValid)
			{
				changeCursor(snake.bombPoint.nX * 2, snake.bombPoint.nY);
				printf("++");
				//snake.bFoodValid = FALSE;
			}

			for (nWallIndex = 0; nWallIndex < snake.nWallCount; nWallIndex++)
			{
				changeCursor(snake.wallPoint[nWallIndex].nX * 2, snake.wallPoint[nWallIndex].nY);
				printf("★");
			}
			changeCursor(snake.frame.nLeft * 2, snake.frame.nTop + snake.frame.nHeight);
			printf("                    ");
			changeCursor(snake.frame.nLeft * 2, snake.frame.nTop + snake.frame.nHeight);
			printf("分数:\t%d", snake.score);
			if (!UpdateSnake(snake, nSnakeIndex))
				exit(0);
		}
		else
		{
			changeCursor((snake.frame.nLeft + 1) * 2 + 1 * 2, snake.frame.nTop + snake.frame.nHeight / 2 - 2);
			printf("\t\tOver!!!\n");
		}
	}
	return TRUE;
}
void showWinner()
{
	int nSnakeIndex, nScore, i;
	StuSnake snake;
	i = GetSnakeNumber();
	if (i == 1)
		return;
	else
	{
		snake = GetSnake(0);
		nScore = snake.score;
		for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
		{
			snake = GetSnake(nSnakeIndex);
			if (nScore<snake.score)
				nScore = snake.score;
		}

		for (nSnakeIndex = 0; nSnakeIndex < GetSnakeNumber(); nSnakeIndex++)
		{
			snake = GetSnake(nSnakeIndex);
			if (nScore == snake.score)
			{
				changeCursor((snake.frame.nLeft + 1) * 2 + 1 * 2, snake.frame.nTop + snake.frame.nHeight / 2);
				printf("\t恭喜,你是赢家!");
			}
			else
			{
				changeCursor((snake.frame.nLeft + 1) * 2 + 1 * 2, snake.frame.nTop + snake.frame.nHeight / 2);
				printf("\tYou are a Loser!");
			}
		}
	}

}

int main(int argc, char** argv)
{
	int N;
	N = chooseLevel();
	init();
	while (isContinue())
	{
		clean();
		input();
		if (step()) /** 改变小蛇位置 等**/
			draw();
		Sleep(N);
	};
	showWinner();
	getch();
	printf("\n\n\n\n\n\n\n\n\n\n");
	return 0;
};
