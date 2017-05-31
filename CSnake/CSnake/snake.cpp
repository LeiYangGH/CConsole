#include "game.h"

//������
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

	getchar();			 //����
	closegraph();
	return 0;
}

//��ʼ��
void GameInit()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  //��ʼ��ͼ�ν���(����)
	srand((unsigned int)time(NULL));
	mciSendString(L"open ./˦�и�.mp3 alias backmusic", 0, 0, 0);
	mciSendString(L"play backmusic repeat", 0, 0, 0);

	//��ʼ��һ��С��
	rectangle(0, 0, SNAKESIZE, SNAKESIZE); //������

	snake.ch = down;		//����
	snake.n = 3;			//����
	snake.sCor[0].x = 0;	//��һ���ߵ�����
	snake.sCor[0].y = 20;

	snake.sCor[1].x = 0;	//��һ���ߵ�����
	snake.sCor[1].y = 10;

	snake.sCor[2].x = 0;	//��һ���ߵ�����
	snake.sCor[2].y = 0;

	food.isEat = 0;			//���Ե� 
}

//�����ƶ�
void SnakeMove()
{
	//���Ͻ������ڽڵ�����
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

//�ߵĻ���	//��n���߸��һ�����  1-100
void SnakeDraw()
{
	for (int i = 0; i < snake.n; i++)
	{
		rectangle(snake.sCor[i].x, snake.sCor[i].y,
			snake.sCor[i].x + SNAKESIZE, snake.sCor[i].y + SNAKESIZE);
	}
}

//��ѧ�� 8����
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

//��ʳ��
void FoodDraw()
{
	roundrect(food.fCor.x, food.fCor.y,
		food.fCor.x + SNAKESIZE, food.fCor.y + SNAKESIZE, 10, 10);
}

//�õ�ʳ�������
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

//ײǽ�ܼ� snake.sCor[0].x  snake.sCor[0].y 
//ײ���Լ� forȥ��������  �ж���ͷ��������û�и��������ĳһ���ߵ��غ�
void SnakeBreak()
{
	//ײǽ�ܼ� snake.sCor[0].x  snake.sCor[0].y  
	if (snake.sCor[0].x < 0 || snake.sCor[0].x>630 ||
		snake.sCor[0].y < 0 || snake.sCor[0].y>470)
	{
		closegraph();
		exit(0);
	}

	//װ�Լ�
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
