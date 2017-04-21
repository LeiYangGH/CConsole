#include<stdio.h>
#include<stdlib.h>

void choose();
void Movie_select();
void Date_select();
void time1();
void time2();
void time3();
void time4();
void time5();
void time6();
void sumFunc();

int main(void)
{
	while(1)
	{
		choose();
		break;
 }
	int choic;
	printf("\nPlease choose the movie:");
	printf("1.....");
	printf("2.....");
	printf("3.....");
	printf("4.....");
	printf("5.....");
	scanf("%d",&choic);
	switch(choic)
	{
		case '1':Date_select(); break;
	case '2':Date_select(); break;
	case '3':Date_select(); break;
	case '4':Date_select(); break;
	case '5':Date_select(); break;
	}
	
	
 }
 
void choose()
{
	char choic;
	system("cls");
	printf("Please choose what you want:");
	printf("\n1. Movie");
	printf("\n2. Date");
	choic = getch();
	switch(choic)
	{
		case '1': Movie_select(); break;
		case '2': Date_select(); break;
		default:choose();
	 } 
}

void Movie_select()
{
	char choic;
	system("cls");
	printf("\n\t*********** Movie Menu ************************");
	printf("\n\t*********** 1- ...................  ***********");
	printf("\n\t*********** 2- ........... ********************");
	printf("\n\t*********** 3- ............. ******************");
	printf("\n\t*********** 4- ................ ***************");
	printf("\n\t*********** 5- ..............******************"); 
	printf("\n\t*********** 6- Exit ***************************");
	printf("\n\t**********************************************");
	printf("\n\tPlease choose the movie:");
	//choic = getch();
	scanf("%c",&choic);
	switch (choic)
	{
	case '1':Date_select(); break;
	case '2':Date_select(); break;
	case '3':Date_select(); break;
	case '4':Date_select(); break;
	case '5':Date_select(); break;
	case '6':exit(0);
	//default:Movie_select();
	}
}

void Date_select()
{
	char choic;
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
	choic = getch();
	switch (choic)
	{
	case '1':time1(); break;
	case '2':time2(); break;
	case '3':time3(); break;
	case '4':time4(); break;
	case '5':time5(); break;
	case '6':time6(); break;
	case '7':time3(); break;
	}
}

void time1()
{
	char choic;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 09:00 ~ 10:45*******");
	printf("\n\t******2. 11:00 ~ 12:45*******");
	printf("\n\t******3. 13:00 ~ 14:45*******");
	printf("\nPlease chouose the time:");
	choic = getch();
	switch(choic)
	{
	case '1':printf("Completing the service."); break;
	case '2':printf("Completing the service."); break;
	case '3':printf("Completing the service."); break;
	}
	
}

void time2()
{
	char choic;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 06:00 ~ 07:45*******");
	printf("\n\t******2. 08:00 ~ 09:45*******");
	printf("\n\t******3. 10:00 ~ 11:45*******");
	printf("\nPlease chouose the time:");
	choic = getch();
	switch(choic)
	{
	case '1':printf("Completing the service."); break;
	case '2':printf("Completing the service."); break;
	case '3':printf("Completing the service."); break;
	}
}

void time3()
{
	char choic;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 12:00 ~ 13:45*******");
	printf("\n\t******2. 14:00 ~ 15:45*******");
	printf("\n\t******3. 16:00 ~ 17:45*******");
	printf("\nPlease chouose the time:");
	choic = getch();
	switch(choic)
	{
	case '1':printf("Completing the service."); break;
	case '2':printf("Completing the service."); break;
	case '3':printf("Completing the service."); break;
	}
}

void time4()
{
	char choic;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 18:00 ~ 19:45*******");
	printf("\n\t******2. 20:00 ~ 21:45*******");
	printf("\n\t******3. 22:00 ~ 23:45*******");
	printf("\nPlease chouose the time:");
	choic = getch();
	switch(choic)
	{
	case '1':printf("Completing the service."); break;
	case '2':printf("Completing the service."); break;
	case '3':printf("Completing the service."); break;
	}
}

void time5()
{
	char choic;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 07:00 ~ 08:45*******");
	printf("\n\t******2. 11:30 ~ 13:15*******");
	printf("\n\t******3. 13:30 ~ 15:15*******");
	printf("\nPlease chouose the time:");
	choic = getch();
	switch(choic)
	{
	case '1':printf("Completing the service."); break;
	case '2':printf("Completing the service."); break;
	case '3':printf("Completing the service."); break;
	}
}
void time6()
{
	char choic;
	system("cls");
	printf("\t*********Time Select***********");
	printf("\n\t******1. 08:30 ~ 10:15*******");
	printf("\n\t******2. 10:30 ~ 12:15*******");
	printf("\n\t******3. 12:30 ~ 14:15*******");
	printf("\nPlease chouose the time:");
	choic = getch();
	switch(choic)
	{
	case '1':printf("Completing the service."); break;
	case '2':printf("Completing the service."); break;
	case '3':printf("Completing the service."); break;
	}
}
