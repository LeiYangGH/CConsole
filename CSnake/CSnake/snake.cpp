#include "game.h"

//主函数
int main()
{
	GameInit();

	while (1)
	{
		while (!kbhit())
		{
			cleardevice();
			if (food.isEat == 0)
			{
				FoodCoor();
			}
			FoodDraw();
			SnakeMove();
			FoodEat();
			SnakeBreak();
			Sleep(100);
		}
		SnakeChange();
	}

	getchar();			 //卡屏
	closegraph();
	return 0;
}

//初始化
void GameInit()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  //初始化图形界面(窗口)
	srand((unsigned int)time(NULL));
	mciSendString(L"open ./甩葱歌.mp3 alias backmusic", 0, 0, 0);
	mciSendString(L"play backmusic repeat", 0, 0, 0);

	//初始化一条小蛇
	rectangle(0, 0, SNAKESIZE, SNAKESIZE); //蛇样子

	snake.ch = down;		//方向
	snake.n = 3;			//节数
	snake.sCor[0].x = 0;	//第一节蛇的坐标
	snake.sCor[0].y = 20;

	snake.sCor[1].x = 0;	//第一节蛇的坐标
	snake.sCor[1].y = 10;

	snake.sCor[2].x = 0;	//第一节蛇的坐标
	snake.sCor[2].y = 0;

	food.isEat = 0;			//被吃掉 
}

//让蛇移动
void SnakeMove()
{
	//不断交换相邻节的坐标
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.sCor[i].x = snake.sCor[i - 1].x;
		snake.sCor[i].y = snake.sCor[i - 1].y;
	}
	switch (snake.ch)
	{
	case up:
		snake.sCor[0].y -= SNAKESIZE;
		break;
	case down:
		snake.sCor[0].y += SNAKESIZE;
		break;
	case left:
		snake.sCor[0].x -= SNAKESIZE;
		break;
	case right:
		snake.sCor[0].x += SNAKESIZE;
		break;
	}
	SnakeDraw();
}

//蛇的绘制	//把n节蛇给我画出来  1-100
void SnakeDraw()
{
	for (int i = 0; i < snake.n; i++)
	{
		rectangle(snake.sCor[i].x, snake.sCor[i].y,
			snake.sCor[i].x + SNAKESIZE, snake.sCor[i].y + SNAKESIZE);
	}
}

//大学生 8个月
void SnakeChange()
{
	char move;			//VIP
	move = getch();
	switch (move)
	{
	case up:
		if (snake.ch != down)
			snake.ch = up;
		break;

	case down:
		if (snake.ch != up)
			snake.ch = down;
		break;

	case left:
		if (snake.ch != right)
			snake.ch = left;
		break;

	case right:
		if (snake.ch != left)
			snake.ch = right;
		break;
	}
}

//画食物
void FoodDraw()
{
	roundrect(food.fCor.x, food.fCor.y,
		food.fCor.x + SNAKESIZE, food.fCor.y + SNAKESIZE, 10, 10);
}

//得到食物的坐标
void FoodCoor()
{
	food.fCor.x = rand() % (WINDOW_WIDTH / SNAKESIZE)*SNAKESIZE;//0-63  *10 0 10 20 30 40 50 60 620 630
	food.fCor.y = rand() % (WINDOW_HEIGHT / SNAKESIZE)*SNAKESIZE;//0-479

	food.isEat = 1;
}

void FoodEat()
{
	if (snake.sCor[0].x == food.fCor.x&&snake.sCor[0].y == food.fCor.y)
	{
		snake.n++;
		food.isEat = 0;
	}
}

//撞墙很简单 snake.sCor[0].x  snake.sCor[0].y 
//撞到自己 for去遍历数组  判定蛇头的坐标有没有跟神的身上某一节蛇的重合
void SnakeBreak()
{
	//撞墙很简单 snake.sCor[0].x  snake.sCor[0].y  
	if (snake.sCor[0].x < 0 || snake.sCor[0].x>630 ||
		snake.sCor[0].y < 0 || snake.sCor[0].y>470)
	{
		closegraph();
		exit(0);
	}

	//装自己
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.sCor[0].x == snake.sCor[i].x&&
			snake.sCor[0].y == snake.sCor[i].y)
		{
			closegraph();
			exit(0);
		}
	}
}
