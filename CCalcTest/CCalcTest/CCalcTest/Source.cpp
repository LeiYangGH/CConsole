#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#define QESTIONS_COUNT 3

int repeatscore[3] = { 10,7,5 };

int random(int min, int max)
{
	return rand() % (max - min) + min;
}

int testone(int qid)
{
	int a, b, r, answer = 0, repeat = -2;
	char o;
	a = random(15, 25);
	b = random(1, 15);
	o = a % 2;
	printf("-----Test %d----\n\n", qid + 1);
	printf("%d %c %d =\n", a, o ? '+' : '-', b);
	r = o ? a + b : a - b;
	while (++repeat < 2 && answer != r)
	{
		printf("Input your answer:");
		scanf("%d", &answer);
	}
	if (answer == r)
		return repeatscore[repeat];
	else
		return 0;
}

void showresult(int score)
{
	if (score >= 90)
		printf("SMART!\n");
	else if (score >= 80 && score < 90)
		printf("GOOD\n");
	else if (score >= 70 && score < 80)
		printf("OK\n");
	else if (score >= 60 && score < 70)
		printf("PASS\n");
	else if (score < 60)
		printf("TRY AGAIN!\n");
}

int main()
{
	int t, m, first, score = 0;
	srand(time(NULL));
	for (t = 0; t < QESTIONS_COUNT; t++)
	{
		score += testone(t);
	}
	printf("---------\n");
	printf("%d\n", score);
	showresult(score);
	system("pause");
	return 0;
}