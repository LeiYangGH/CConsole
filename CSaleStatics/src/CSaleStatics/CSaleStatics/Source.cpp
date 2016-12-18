#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<iostream>
#include <stdio.h>
#include <string.h>
#define SALESMAN_COUNT 3
#define GOODS_TYPES 5

int amount[SALESMAN_COUNT][GOODS_TYPES] =
{
	{33,32,56,45,33},
	{77,33,68,45,23},
	{43,55,43,67,65}
};


typedef struct salesman
{
	int id;
	int tatal;
}salesman;

typedef struct good
{
	char id;
	int price;
	int tatal;
}good;

salesman sales[SALESMAN_COUNT];
good goods[GOODS_TYPES];

void initsales()
{
	sales[0].id = 1;
	sales[1].id = 2;
	sales[2].id = 3;
}

void initgoods()
{
	goods[0].id = 'A';
	goods[0].price = 12;

	goods[1].id = 'B';
	goods[1].price = 16;

	goods[2].id = 'C';
	goods[2].price = 10;

	goods[3].id = 'D';
	goods[3].price = 14;

	goods[4].id = 'E';
	goods[4].price = 15;
}

void printtalbe()
{
	int i, j;
	printf("-----------所有数据-----------\n");

	for (i = 0; i < SALESMAN_COUNT; i++)
	{
		printf("销售员%d\t\t", sales[i].id);
		for (j = 0; j < GOODS_TYPES; j++)
		{
			printf("%d\t", amount[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	initsales();
	initgoods();
	printtalbe();
	system("pause");
	return 0;
}