#include<graphics.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define PI 3.1415926


void jiaochayuan(int x, int y)
{

	setlinestyle(PS_SOLID, 4);
	setcolor(BLACK);
	circle(x, y, 50);
	setorigin(x, y);
	line(-(int)(50 * cos(PI / 4)), -(int)(50 * sin(PI / 4)), (int)(50 * cos(PI / 4)), (int)(50 * sin(PI / 4)));
	line(-(int)(50 * cos(PI / 4)), (int)(50 * sin(PI / 4)), (int)(50 * cos(PI / 4)), -(int)(50 * sin(PI / 4)));
	setorigin(0, 0);
}

/* 画出花朵的函数 */
/* x和y为花心的坐标 */
void tuan(int a, int b)
{
	int n = 15, i, j, r = 110, x[50], y[50];
	float t;
	setorigin(a, b);//重置原点坐标
	setcolor(RED);
	t = 3.14 * 2 / n;
	for (i = 0; i<n; i++)//圆周上各个等分点的坐标 
	{
		x[i] = r*cos(i*t);
		y[i] = r*sin(i*t);
	}
	for (i = 0; i<n - 1; i++)
	{
		for (j = i + 1; j<n; j++)
		{
			line(x[i], y[i], x[j], y[j]);
		}
	}

}


int main()
{
	initgraph(600, 600);
	setbkcolor(RGB(255, 153, 51));
	cleardevice();
	//jiaochayuan(300, 300);
	tuan(400, 400);
	system("pause");
	closegraph();
	return 0;
}