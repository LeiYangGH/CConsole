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

int main()
{
	initgraph(600, 600);
	setbkcolor(RGB(255, 153, 51));
	cleardevice();
	jiaochayuan(300, 300);
	system("pause");
	closegraph();
	return 0;
}