#pragma once
#include <stdio.h>		//标准的输入输出头文件
#include <time.h>		//time
#include <stdlib.h>		//stdlib.h
#include <graphics.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")

#define WINDOW_WIDTH	640  //窗口的宽
#define WINDOW_HEIGHT	480  //窗口的高
#define MAXNUM			100  //蛇的最大节数
#define SNAKESIZE       10	 //蛇的大小


//用一个什么样的数据去表示蛇这个元素
//自定义的结构体类型   当前有多少节  蛇的方向  蛇的坐标

//蛇的方向
typedef enum Ch { up = 72, down = 80, left = 75, right = 77 }CH;

typedef struct Coor
{
	int x;
	int y;
}COOR;

typedef struct Snake
{
	COOR sCor[MAXNUM];	//蛇的坐标(包含100节)
	int n;				//当前的节数
	CH ch;				//蛇的方向
}SNAKE;

//食物有什么属性?
typedef struct Food
{
	Coor fCor;
	int isEat;
}FOOD;


SNAKE snake;			//把蛇定义出来
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
