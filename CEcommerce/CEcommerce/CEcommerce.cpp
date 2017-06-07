#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct ware
{
	char identity[20];
	char name[20];
	float price;
	char address[20];
	int quantity;
	int warnquantity;
}commodity;

typedef struct user
{
	char name[20];
	char password[20];
	int isadmin;
	float money;
	ware wants[10];
	ware bought[100];
}user;

user allusers[10];
int alluserscount = 0;

char currentusername[20] = "";

int isusernameexists(char name[20])
{

}

int ispassowrdcomplicated(char password[20])
{

}

void registeruser(char name[20], char password[20])
{

}

void login()
{

}

void logout()
{

}

void displayallwares()
{
}

void readallstudents()
{
}

int getstudentidexbyno(char identity[20])
{

}

void writeallstudents()
{
}

void editstudent(char identity[20])
{
}

void addstudent(char identity[20], char name[], float price, char address, int quantity, int warnquantity)
{
}

void removestudent(char identity[20])
{
}

void searcbyname(char *name)
{
}

void warnlack(char identity[20])
{

}

void addwant(user *usr, char identity[20])
{

}


int main()
{
	system("pause");
	return 0;
}