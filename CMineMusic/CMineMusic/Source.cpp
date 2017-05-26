#include<stdio.h>                 
#include<time.h> 
#include<stdlib.h>
#include <iostream> 
#include <windows.h>
#pragma comment(lib, "winmm.lib")
//#include<bits/stdc++.h>
#define col_1 10	
#define row_1 10
#define col_2 20	
#define row_2 20
#define MINE_NUM_1 10
#define MINE_NUM_2 50




void fillblank_1();
int  open_1(int x, char y);
void open_neighbors_1(int x, char y);
void fix_helpless_1();
void flag_1(int x, char y);
int  flag_count_1();
bool is_win_1();
void neighbors_count_1();
void init_1(int num);
void print_1();
void fillblank_2();
int  open_2(int x, char y);
void open_neighbors_2(int x, char y);
void fix_helpless_2();
void flag_2(int x, char y);
int  flag_count_2();
bool is_win_2();
void neighbors_count_2();
void init_2(int num);
void print_2();
void neighbors_count_crazymode();
void init_crazymode(int num);



struct mine
{
	bool is_mine;
	bool is_crazymine;
	int status;
	int neighbors;
};
mine map_1[row_1 + 2][col_1 + 2];
mine map_2[row_2 + 2][col_2 + 2];


void main()
{
	//PlaySound(TEXT("w.wma"), NULL, SND_FILENAME);
	//PlaySound(TEXT("c:\\test\\t.wav"), 
	//	NULL, SND_FILENAME | SND_ASYNC);
	PlaySound(TEXT("ForTheWin.wav"), NULL, 
		SND_FILENAME | SND_ASYNC|SND_LOOP);

	printf("欢迎体验第九组出品的c语言扫雷小游戏\n请选择难度 请输入1或2或3\n级别 1：easy 2：hard 3：crazy mode\n");
	int m;
	scanf_s("%d", &m);
	switch (m)
	{
	case 1:
	{
		init_1(MINE_NUM_1);
		int  x;
		char y;
		void fillblank_1();
		print_1();
		while (1)
		{
			printf("\n请输入坐标，例如:a1\n如果要设置旗标，将列号字母换成大写：\n");
			scanf_s("%c", &y);
			scanf_s("%d", &x);
			system("cls");

			if (x <= 0 || x > col_1)
			{
				print_1();
				printf("坐标错误，请好好输入：\n");
				continue;
			}
			if (y >= 65 && y <= 64 + row_1)
				flag_1(x, y);
			else if (y >= 97 && y <= 96 + row_1)
				open_1(x, y);
			else
			{
				print_1();
				printf("坐标错误，请好好输入：\n");
				continue;
			}
			print_1();
			if (open_1(x, y) == -1)
			{
				printf("boom-shakalaka......game over\n");
				break;
			}
			if (is_win_1())
			{
				printf("hahaha(: congratulations you win!\n");
				break;
			}
		}
	}
	Sleep(1000);
	break;
	case 2:
	{
		init_2(MINE_NUM_2);
		int  x;
		char y;
		void fillblank_2();
		print_2();
		while (1)
		{
			printf("\n请输入坐标，例如:a1\n如果要设置旗标，将列号字母换成大写：\n");
			scanf_s("%c", &y);
			scanf_s("%d", &x);
			system("cls");

			if (x <= 0 || x > col_2)
			{
				print_2();
				printf("坐标错误，请好好输入：\n");
				continue;
			}
			if (y >= 65 && y <= 64 + row_2)
				flag_2(x, y);
			else if (y >= 97 && y <= 96 + row_2)
				open_2(x, y);
			else
			{
				print_2();
				printf("坐标错误，请好好输入：\n");
				continue;
			}
			print_2();
			if (open_2(x, y) == -1)
			{
				printf("boom-shakalaka......game over\n");
				break;
			}
			if (is_win_2())
			{
				printf("hahaha(: congratulations you win!\n");
				break;
			}
		}
	}
	Sleep(1000);
	break;
	case 3:
	{
		init_crazymode(MINE_NUM_1);
		int  x;
		char y;
		void fillblank_1();
		print_1();
		while (1)
		{
			printf("\n请输入坐标，例如:a1\n如果要设置旗标，将列号字母换成大写：\n");
			scanf_s("%c", &y);
			scanf_s("%d", &x);
			system("cls");

			if (x <= 0 || x > col_1)
			{
				print_1();
				printf("坐标错误，请好好输入：\n");
				continue;
			}
			if (y >= 65 && y <= 64 + row_1)
				flag_1(x, y);
			else if (y >= 97 && y <= 96 + row_1)
				open_1(x, y);
			else
			{
				print_1();
				printf("坐标错误，请好好输入：\n");
				continue;
			}
			print_1();
			if (open_1(x, y) == -1)
			{
				printf("boom-shakalaka......game over\n");
				break;
			}
			if (is_win_1())
			{
				printf("hahaha(: congratulations you win!\n");
				break;
			}
		}
	}
	Sleep(1000);
	}
}



void fillblank_1()
{
	int i, j;
	for (i = 0; i < row_1 + 1; i++)
		for (j = 0; j < col_1 + 1; j++)
			if (i<1 || i > col_1 || j <1 || j >row_1)
				map_1[i][j].status = 1;
}

int open_1(int x, char y)
{
	y -= 96;
	if (x<1 || x>row_1 || y<1 || y>col_1)
		return 0;
	if (map_1[x][y].status != 0)
		return 0;
	else if (map_1[x][y].is_mine == true)
		return -1;
	else if (map_1[x][y].neighbors == 0)
	{
		map_1[x][y].status = 1;
		open_neighbors_1(x, y + 96);
	}
	else
		map_1[x][y].status = 1;
	return 1;
}

void fix_helpless_1()
{
	int i, j;
	for (i = 1; i < row_1; i++)
		for (j = 1; j < col_1; j++)
			if (map_1[i][j].neighbors == 0 && map_1[i][j].status == 1)
			{
				map_1[i - 1][j - 1].status = 1;
				map_1[i - 1][j].status = 1;
				map_1[i - 1][j + 1].status = 1;
				map_1[i][j - 1].status = 1;
				map_1[i][j + 1].status = 1;
				map_1[i + 1][j - 1].status = 1;
				map_1[i + 1][j].status = 1;
				map_1[i + 1][j + 1].status = 1;
			}
}

void open_neighbors_1(int x, char y)
{
	y -= 96;
	if (y + 1 < col_1 + 1)
		open_1(x, y + 1 + 96);
	if (x - 1 > 0)
		open_1(x - 1, y + 96);
	if (y - 1 > 0)
		open_1(x, y - 1 + 96);
	if (x + 1 < row_1 + 1)
		open_1(x + 1, y + 96);
}

void flag_1(int x, char y)
{
	y -= 64;
	if (map_1[x][y].status == 2)
		map_1[x][y].status = 0;
	else if (map_1[x][y].status == 0)
		map_1[x][y].status = 2;
}

int flag_count_1()
{
	int num = 0;
	int i, j;
	for (i = 1; i < row_1 + 1; i++)
		for (j = 1; j < col_1 + 1; j++)
			if (map_1[i][j].status == 2)
				num++;
	return MINE_NUM_1 - num;
}

bool is_win_1()
{
	int num = row_1 + col_1;
	int i, j;
	for (i = 1; i < row_1 + 1; i++)
		for (j = 1; j < col_1 + 1; j++)
			if (map_1[i][j].status == 0 && map_1[i][j].is_mine == false || map_1[i][j].status == 2 && map_1[i][j].is_mine == false)
				return false;
	return true;
}

void neighbors_count_1()
{
	int i, j;
	for (i = 1; i < row_1 + 1; i++)
		for (j = 1; j < col_1 + 1; j++)
		{
			map_1[i][j].neighbors = map_1[i - 1][j - 1].is_mine + map_1[i - 1][j].is_mine + map_1[i - 1][j + 1].is_mine + map_1[i][j - 1].is_mine + map_1[i][j + 1].is_mine + map_1[i + 1][j - 1].is_mine + map_1[i + 1][j].is_mine + map_1[i + 1][j + 1].is_mine;
		}
}

void init_1(int num)
{
	int i, j;
	for (i = 1; i < row_1; i++)
		for (j = 1; j < col_1; j++)
		{
			map_1[i][j].is_mine = 0;
			map_1[i][j].status = 0;
			map_1[i][j].neighbors = 0;
		}

	srand((unsigned)time(NULL));
	i = num;
	int temp;

	while (i > 0)
	{
		temp = rand() % (row_1*col_1);
		if (map_1[temp / row_1 + 1][temp % col_1 + 1].is_mine == false)
		{
			map_1[temp / row_1 + 1][temp % col_1 + 1].is_mine = true;
			i--;
		}
	}
	neighbors_count_1();
}



void print_1()
{
	fix_helpless_1();
	int i, j;
	printf("“@”表示未打开，“F”表示已插旗，数字表示周围8块中的地雷总数。\n");
	printf("当前剩余雷数：%d\n", flag_count_1());
	printf("   ");
	for (i = 0; i < col_1; i++)
		printf(" %c ", i + 97);
	printf("\n");
	for (i = 1; i<col_1 + 1; i++)
	{
		printf("%2d ", i);
		for (j = 1; j < row_1 + 1; j++)
		{
			if (map_1[i][j].status == 1 && map_1[i][j].neighbors != 0)
				printf(" %d ", map_1[i][j].neighbors);
			else if (map_1[i][j].status == 1 && map_1[i][j].neighbors == 0)
				printf("   ");
			else if (map_1[i][j].status == 2)
				printf(" F ");
			else
				printf(" @ ");
		}
		printf("\n");
	}
}





void fillblank_2()
{
	int i, j;
	for (i = 0; i < row_2 + 1; i++)
		for (j = 0; j < col_2 + 1; j++)
			if (i<1 || i > col_2 || j <1 || j >row_2)
				map_2[i][j].status = 1;
}

int open_2(int x, char y)
{
	y -= 96;
	if (x<1 || x>row_2 || y<1 || y>col_2)
		return 0;
	if (map_2[x][y].status != 0)
		return 0;
	else if (map_2[x][y].is_mine == true)
		return -1;
	else if (map_2[x][y].neighbors == 0)
	{
		map_2[x][y].status = 1;
		open_neighbors_2(x, y + 96);
	}
	else
		map_2[x][y].status = 1;
	return 1;
}

void fix_helpless_2()
{
	int i, j;
	for (i = 1; i < row_2; i++)
		for (j = 1; j < col_2; j++)
			if (map_2[i][j].neighbors == 0 && map_2[i][j].status == 1)
			{
				map_2[i - 1][j - 1].status = 1;
				map_2[i - 1][j].status = 1;
				map_2[i - 1][j + 1].status = 1;
				map_2[i][j - 1].status = 1;
				map_2[i][j + 1].status = 1;
				map_2[i + 1][j - 1].status = 1;
				map_2[i + 1][j].status = 1;
				map_2[i + 1][j + 1].status = 1;
			}
}

void open_neighbors_2(int x, char y)
{
	y -= 96;
	if (y + 1 < col_1 + 1)
		open_2(x, y + 1 + 96);
	if (x - 1 > 0)
		open_2(x - 1, y + 96);
	if (y - 1 > 0)
		open_2(x, y - 1 + 96);
	if (x + 1 < row_1 + 1)
		open_2(x + 1, y + 96);
}

void flag_2(int x, char y)
{
	y -= 64;
	if (map_2[x][y].status == 2)
		map_2[x][y].status = 0;
	else if (map_2[x][y].status == 0)
		map_2[x][y].status = 2;
}

int flag_count_2()
{
	int num = 0;
	int i, j;
	for (i = 1; i < row_2 + 1; i++)
		for (j = 1; j < col_2 + 1; j++)
			if (map_2[i][j].status == 2)
				num++;
	return MINE_NUM_2 - num;
}

bool is_win_2()
{
	int num = row_2 + col_2;
	int i, j;
	for (i = 1; i < row_2 + 1; i++)
		for (j = 1; j < col_2 + 1; j++)
			if (map_2[i][j].status == 0 && map_2[i][j].is_mine == false || map_2[i][j].status == 2 && map_2[i][j].is_mine == false)
				return false;
	return true;
}

void neighbors_count_2()
{
	int i, j;
	for (i = 1; i < row_2 + 1; i++)
		for (j = 1; j < col_2 + 1; j++)
		{
			map_2[i][j].neighbors = map_2[i - 1][j - 1].is_mine + map_2[i - 1][j].is_mine + map_2[i - 1][j + 1].is_mine + map_2[i][j - 1].is_mine + map_2[i][j + 1].is_mine + map_2[i + 1][j - 1].is_mine + map_2[i + 1][j].is_mine + map_2[i + 1][j + 1].is_mine;
		}
}

void init_2(int num)
{
	int i, j;
	for (i = 1; i < row_1; i++)
		for (j = 1; j < col_1; j++)
		{
			map_2[i][j].is_mine = 0;
			map_2[i][j].status = 0;
			map_2[i][j].neighbors = 0;
		}

	srand((unsigned)time(NULL));
	i = num;
	int temp;

	while (i > 0)
	{
		temp = rand() % (row_2*col_2);
		if (map_2[temp / row_2 + 1][temp % col_2 + 1].is_mine == false)
		{
			map_2[temp / row_2 + 1][temp % col_2 + 1].is_mine = true;
			i--;
		}
	}
	neighbors_count_2();
}



void print_2()
{
	fix_helpless_2();
	int i, j;
	printf("“@”表示未打开，“F”表示已插旗，数字表示周围8块中的地雷总数。\n");
	printf("当前剩余雷数：%d\n", flag_count_2());
	printf("   ");
	for (i = 0; i < col_2; i++)
		printf(" %c ", i + 97);
	printf("\n");
	for (i = 1; i<col_2 + 1; i++)
	{
		printf("%2d ", i);
		for (j = 1; j < row_2 + 1; j++)
		{
			if (map_2[i][j].status == 1 && map_2[i][j].neighbors != 0)
				printf(" %d ", map_2[i][j].neighbors);
			else if (map_2[i][j].status == 1 && map_2[i][j].neighbors == 0)
				printf("   ");
			else if (map_2[i][j].status == 2)
				printf(" F ");
			else
				printf(" @ ");
		}
		printf("\n");
	}
}


void neighbors_count_crazymode()
{
	int i, j;
	for (i = 1; i < row_1 + 1; i++)
		for (j = 1; j < col_1 + 1; j++)
		{
			map_1[i][j].neighbors = map_1[i - 1][j - 1].is_mine + map_1[i - 1][j].is_mine + map_1[i - 1][j + 1].is_mine +
				map_1[i][j - 1].is_mine + map_1[i][j + 1].is_mine + map_1[i + 1][j - 1].is_mine + map_1[i + 1][j].is_mine +
				map_1[i + 1][j + 1].is_mine + 2 * (map_1[i - 1][j - 1].is_crazymine + map_1[i - 1][j].is_crazymine + map_1[i - 1][j + 1].is_crazymine +
					map_1[i][j - 1].is_crazymine + map_1[i][j + 1].is_crazymine + map_1[i + 1][j - 1].is_crazymine + map_1[i + 1][j].is_crazymine +
					map_1[i + 1][j + 1].is_crazymine);
		}
}




void init_crazymode(int num)
{
	int i, j;
	for (i = 1; i < row_1; i++)
		for (j = 1; j < col_1; j++)
		{
			map_2[i][j].is_mine = 0;
			map_2[i][j].status = 0;
			map_2[i][j].neighbors = 0;
		}

	srand((unsigned)time(NULL));
	i = num;
	j = num / 10;
	int temp;

	while (j > 0)
	{
		temp = rand() % (row_1*col_1);
		if (map_1[temp / row_1 + 1][temp % col_1 + 1].is_mine == false || map_1[temp / row_1 + 1][temp % col_1 + 1].is_crazymine == false)
		{

			map_1[temp / row_1 + 1][temp % col_1 + 1].is_crazymine = true;
			j--;

		}
	}

	while (i > 0)
	{
		temp = rand() % (row_1*col_1);
		if (map_1[temp / row_1 + 1][temp % col_1 + 1].is_mine == false || map_1[temp / row_1 + 1][temp % col_1 + 1].is_crazymine == false)
		{

			map_1[temp / row_1 + 1][temp % col_1 + 1].is_mine = true;
			i--;

		}
	}
	neighbors_count_crazymode();
}

