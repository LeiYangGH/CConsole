#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int choose_order();
int choose_movie();
int choose_date();
void choose_time();
void sumFunc();
int time1();
int time2();
int time3();
int time4();
int time5();
int time6();
int time7();

int chosen_movie;
int chosen_date;
int chosen_time;


int main(void)
{
	while (1)
	{
		int order;
		order = choose_order();
		if (order == 1)
		{
			chosen_movie = choose_movie();
			chosen_date = choose_date();
		}
		else
		{
			chosen_date = choose_date();
			chosen_movie = choose_movie();
		}
		choose_time();
		printf("Completing the service.");
		sumFunc();
		fseek(stdin, 0, SEEK_END);
		printf("Press any key to select again...");
		system("pause");
	}
}

int choose_order()
{
	char choice;
	system("cls");
	printf("Please choose order:");
	printf("\n1. Movie");
	printf("\n2. Date");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

void choose_time()
{
	char choice;
	system("cls");
	switch (chosen_date)
	{
	case 1:
		time1();
		break;
	case 2:
		time2();
		break;
	case 3:
		time3();
		break;
	case 4:
		time4();
		break;
	case 5:
		time5();
		break;
	case 6:
		time6();
		break;
	case 7:
		time7();
		break;
	}
}

void sumFunc()
{
	int sum;
	sum = chosen_date + chosen_movie + chosen_time;
	printf("sum=%d\n", sum);
}


int choose_movie()
{
	char choice;
	system("cls");
	printf("\n\t*********** Movie Menu ************************");
	printf("\n\t*********** 1- ...................  ***********");
	printf("\n\t*********** 2- ........... ********************");
	printf("\n\t*********** 3- ............. ******************");
	printf("\n\t*********** 4- ................ ***************");
	printf("\n\t*********** 5- ..............******************");
	//printf("\n\t*********** 6- Exit ***************************");
	printf("\n\t**********************************************");
	printf("\n\tPlease choose the movie:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

int choose_date()
{
	char choice;
	system("cls");
	printf("\n\t********** Date menu *************************");
	printf("\n\t**********1. Monday***************************");
	printf("\n\t**********2. Tuesday**************************");
	printf("\n\t**********3. Wednesday************************");
	printf("\n\t**********4. Thursday*************************");
	printf("\n\t**********5. Friday***************************");
	printf("\n\t**********6. Saturday*************************");
	printf("\n\t**********7. Sunday***************************");
	printf("\n\tPlease choose the date:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

int time1()
{
	char choice;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 09:00 ~ 10:45*******");
	printf("\n\t******2. 11:00 ~ 12:45*******");
	printf("\n\t******3. 13:00 ~ 14:45*******");
	printf("\nPlease chouose the time:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

int time2()
{
	char choice;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 06:00 ~ 07:45*******");
	printf("\n\t******2. 08:00 ~ 09:45*******");
	printf("\n\t******3. 10:00 ~ 11:45*******");
	printf("\nPlease chouose the time:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

int time3()
{
	char choice;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 12:00 ~ 13:45*******");
	printf("\n\t******2. 14:00 ~ 15:45*******");
	printf("\n\t******3. 16:00 ~ 17:45*******");
	printf("\nPlease chouose the time:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

int time4()
{
	char choice;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 18:00 ~ 19:45*******");
	printf("\n\t******2. 20:00 ~ 21:45*******");
	printf("\n\t******3. 22:00 ~ 23:45*******");
	printf("\nPlease chouose the time:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

int time5()
{
	char choice;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 07:00 ~ 08:45*******");
	printf("\n\t******2. 11:30 ~ 13:15*******");
	printf("\n\t******3. 13:30 ~ 15:15*******");
	printf("\nPlease chouose the time:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}
int time6()
{
	char choice;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 08:30 ~ 10:15*******");
	printf("\n\t******2. 10:30 ~ 12:15*******");
	printf("\n\t******3. 12:30 ~ 14:15*******");
	printf("\nPlease chouose the time:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}

int time7()
{
	char choice;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 08:35 ~ 10:25*******");
	printf("\n\t******2. 11:30 ~ 15:15*******");
	printf("\n\t******3. 15:35 ~ 17:15*******");
	printf("\nPlease chouose the time:");
	choice = getch();
	fseek(stdin, 0, SEEK_END);
	return choice - '0';
}