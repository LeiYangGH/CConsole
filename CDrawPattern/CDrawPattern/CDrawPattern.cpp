#include<graphics.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define PI 3.1415926
#define D 5
#define F 50



void jiaochayuan(int x, int y)
{

	setlinestyle(PS_SOLID, 4);
	setcolor(GREEN);
	circle(x, y, 20);
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
	for (i = 0; i < n; i++)//圆周上各个等分点的坐标 
	{
		x[i] = r*cos(i*t);
		y[i] = r*sin(i*t);
	}
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			line(x[i], y[i], x[j], y[j]);
		}
	}

}

void draw1(int color, int x, int y)
{
	double a, e;
	int x1, y1, x2, y2;
	setcolor(color); /* 设置前景色 */
	for (a = 0; a < 2 * PI; a += 2 * PI / 720)
	{
		/* 计算线段两个端点的横纵坐标 */
		e = D*(1 + sin(8 * a));
		x1 = (int)(x + 2 * e * cos(a));
		x2 = (int)(x + e * cos(a + PI / 5));
		y1 = (int)(y + 2 * e * sin(a));
		y2 = (int)(y + e * sin(a + PI / 5));
		line(x1, y1, x2, y2);
		//Sleep(5); /* 延迟函数，实现动画效果 */
	}
}

void draw7flowers(int x, int y)
{
	draw1(RED, x, y);
	draw1(RED, x - 40, 400); draw1(RED, x + 40, 400);
	draw1(RED, x - 20, y - 40); draw1(RED, x + 20, y - 40);
	draw1(RED, x - 20, y + 40); draw1(RED, x + 20, y + 40);
}

void lingxing(int x, int y)
{
	setlinestyle(PS_SOLID, 4);
	setcolor(BLACK);
	line(x - 20, y, x, y - 20); line(x, y - 20, x + 20, y);
	line(x - 20, y, x, y + 20); line(x, y + 20, x + 20, y);
}



int main()
{
	int i, x, y;
	int linediffy = 200;//上下两条线的间距
	int linedotdiffy = 5;//直线与虚线的间距
	int flowerhalfx = 75;//7朵画一半宽度
	initgraph(600, 600);
	setbkcolor(RGB(0, 0, 0));
	cleardevice();
	//jiaochayuan(300, 300);
	//tuan(400, 400);
	//draw7flowers(400, 400);
	//lingxing(300, 300);
	setlinestyle(PS_SOLID, 4);
	setcolor(RED);

	line(0, 300, 600, 300);
	line(0, 300 + linediffy, 600, 300 + linediffy);

	setlinestyle(PS_DASHDOT, 4);
	setcolor(RED);
	line(0, 300 + linedotdiffy, 600, 300 + linedotdiffy);
	line(0, 300 + linediffy - linedotdiffy, 600, 300 + linediffy - linedotdiffy);

	for (i = 0; i < 5; i++)
	{
		draw7flowers(20 + i * flowerhalfx * 2, 400);
	}

	for (i = 0; i < 5; i++)
	{
		jiaochayuan(20 - flowerhalfx + i * flowerhalfx * 2, 300 + 50);
		jiaochayuan(20 - flowerhalfx + i * flowerhalfx * 2, 300 + 150);
	}

	system("pause");
	closegraph();
	return 0;
}