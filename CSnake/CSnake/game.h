#pragma once
#include <stdio.h>		//��׼���������ͷ�ļ�
#include <time.h>		//time
#include <stdlib.h>		//stdlib.h
#include <graphics.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")

#define WINDOW_WIDTH	640  //���ڵĿ�
#define WINDOW_HEIGHT	480  //���ڵĸ�
#define MAXNUM			100  //�ߵ�������
#define SNAKESIZE       10	 //�ߵĴ�С


//��һ��ʲô��������ȥ��ʾ�����Ԫ��
//�Զ���Ľṹ������   ��ǰ�ж��ٽ�  �ߵķ���  �ߵ�����

//�ߵķ���
typedef enum Ch { up = 72, down = 80, left = 75, right = 77 }CH;

typedef struct Coor
{
	int x;
	int y;
}COOR;

typedef struct Snake
{
	COOR sCor[MAXNUM];	//�ߵ�����(����100��)
	int n;				//��ǰ�Ľ���
	CH ch;				//�ߵķ���
}SNAKE;

//ʳ����ʲô����?
typedef struct Food
{
	Coor fCor;
	int isEat;
}FOOD;


SNAKE snake;			//���߶������
FOOD  food;

void GameInit();
void SnakeMove();
void SnakeDraw();
void SnakeChange();
void FoodDraw();
void FoodCoor();
void FoodEat();
void SnakeBreak(); 
#pragma once
