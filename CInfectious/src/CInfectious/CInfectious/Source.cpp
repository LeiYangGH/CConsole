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
	{ 33,32,56,45,33 },
	{ 77,33,68,45,23 },
	{ 43,55,43,67,65 }
};


typedef struct salesman
{
	int id;
	int total;
}salesman;

typedef struct good
{
	char id;
	int price;
	int total;
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

void calcbysales()
{
	int i, j;
	printf("-----------每个销售人员的销售额-----------\n");

	for (i = 0; i < SALESMAN_COUNT; i++)
	{
		sales[i].total = 0;
		printf("销售员%d\t\t", sales[i].id);
		for (j = 0; j < GOODS_TYPES; j++)
			sales[i].total += amount[i][j] * goods[j].price;
		printf("%d\n", sales[i].total);
	}
}

void calcbygoods()
{
	int i, j;
	printf("-----------每个商品的销售额-----------\n");

	for (j = 0; j < GOODS_TYPES; j++)
	{
		goods[j].total = 0;
		printf("货物%c\t\t", goods[j].id);
		for (i = 0; i < SALESMAN_COUNT; i++)
			goods[j].total += amount[i][j] * goods[j].price;
		printf("%d\n", goods[j].total);
	}

}

void getbestsalesman()
{
	int i, j, t = 0;
	printf("-----------销售额最多的销售人员-----------\n");

	for (i = 0; i < SALESMAN_COUNT; i++)
	{
		if (sales[i].total > t)
		{
			j = i;
			t = sales[i].total;
		}
	}
	printf("销售员%d\n", sales[j].id);
}

void getbestgoods()
{
	int i, j, t = 0;
	printf("-----------销售额最多的销售人员-----------\n");
	for (j = 0; j < GOODS_TYPES; j++)
	{
		if (goods[j].total > t)
		{
			i = j;
			t = goods[i].total;
		}
	}
	printf("商品%c\n", goods[i].id);
}

int main()
{
	initsales();
	initgoods();
	printtalbe();
	calcbysales();
	calcbygoods();
	getbestsalesman();
	getbestgoods();
	system("pause");
	return 0;
}