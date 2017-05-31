#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#define EDGE 20 
#define HISTORY_FILE "history.txt" 

typedef struct history
{
	char p1[11];
	char p2[11];
	char win[2];
}history;

history allhistorys[50];
int allhistoryscount = 0;

void displayhistory(history stu)
{
	printf("%s%s\t%s%s\n", stu.p1, strcmp(stu.win, "1") == 0 ? "(win)" : "",
		stu.p2, strcmp(stu.win, "2") == 0 ? "(win)" : "");
}

void displayallhistorys()
{
	int i;
	printf("���10�ζ�ս\r\n", allhistoryscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allhistoryscount; i++)
	{
		displayhistory(allhistorys[i]);
	}
	printf("--------------------------------------------\r\n");
}

history gethistoryfromline(char *line)
{
	char *part;
	int index = 0;
	history stu;
	part = strtok(line, " \n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.p1, part);
			break;
		case 2:
			strcpy(stu.p2, part);
			break;
		case 3:
			strcpy(stu.win, part);
			break;

		default:
			break;
		}
		part = strtok(NULL, " \n");
	}
	return stu;
}

void readallhistorys()
{
	char line[200];
	FILE *fp = fopen(HISTORY_FILE, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", HISTORY_FILE);
	}
	else
	{
		allhistoryscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allhistorys[allhistoryscount++] = gethistoryfromline(line);
		}
		printf("\n�Ѷ����ļ�!", HISTORY_FILE);
	}
}

void writeallhistorys()
{
	int i;
	history stu;
	FILE *fp = fopen(HISTORY_FILE, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", HISTORY_FILE);
		getchar();
		exit(1);
	}
	for (i = allhistoryscount <= 10 ? 0 : allhistoryscount - 10; i < allhistoryscount; i++)
	{
		stu = allhistorys[i];
		fprintf(fp, "%s %s %s\n", stu.p1, stu.p2, stu.win);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void addhistory(char p1[11], char p2[11], char win[2])
{
	history stu;
	strcpy(stu.p1, p1);
	strcpy(stu.p2, p2);
	strcpy(stu.win, win);
	allhistorys[allhistoryscount++] = stu;
}

char name1[10], name2[10];//���������
int block[EDGE][EDGE];//0��������λ��Ϊ��,1����1��ҵ�����,2����2��ҵ����ӡ�
int coord[2] = { EDGE / 2, EDGE / 2 };//ѡ���λ�ã���ʼĬ�����м䡣
int player = 1;//1����1���,2����2��ҡ�

void board();//��ӡ���̡�
void init();//��ʼ��,��block���������ֵ����Ϊ0��
void up();//���ơ�
void down();//���ơ�
void left();//���ơ�
void right();//���ơ�
void press();//���Ӻ�����
int set();//��λ���Ƿ��ѱ�ռ�ݡ�
int win();//�Ƿ����������ʤ����1����ʤ��,0����δʤ����
int cross(int, int);//�Ƿ񳬽硣
void play();//�����������̵ĺ�����

int main()
{
	system("color E1");//ϵͳ��ɫ��
	printf("\n\n\n\n\n\n                             -----------------------------------------------------------\n");
	printf("                                   -----------------------------------------------      \n");
	printf("                                                     YOHO! GOBANG!                      \n\n");
	printf("                                                     A MASTERPIECE                      \n\n");
	printf("                                                       by Robin Li                       \n\n");
	printf("                                              Press 'i' to enjoy the game               \n\n");
	printf("                                                          :D                            \n\n");
	printf("                                   -----------------------------------------------      \n");
	printf("                             -----------------------------------------------------------\n");
	char ch1;
	while (1)
	{
		ch1 = getch();
		switch (ch1)
		{
		case 'i':
			char ch2;
			init();
			while (1)
			{
				board();
				if (player == 1)
					printf("\n             NO.1 press now.\n", player, name1);
				if (player == 2)
					printf("\n             NO.2 press now.\n", player, name2);
				ch2 = getch();
				switch (ch2)
				{
				case 'w':up();
					break;
				case 's':down();
					break;
				case 'a':left();
					break;
				case 'd':right();
					break;
				case 'q':press();
					break;
				}
			}
			break;
		default:
			printf("Invalid character...\nRewrite please.\n");
			break;
		}
	}
	return 0;
}
void board()//�˺�������������
{
	int a, b;
	int n = 1;
	system("cls");
	printf("\n �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	for (a = 0; a < EDGE; a++)
	{
		printf("|");//�߽硣
		for (b = 0; b < EDGE; b++)
		{
			if (a == coord[0] && b == coord[1])
			{
				printf("��");//��ʾ��ѡ�����λ�á�
			}
			else
			{
				if (block[a][b] == 0)
				{
					printf("ʮ");//�������档
				}
				else if (block[a][b] == 1)
				{
					printf("��");//NO.1
				}
				else if (block[a][b] == 2)
				{
					printf("��");//NO.2
				}
			}
		}
		printf("|");
		printf("\n");
	}
	printf(" �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}


void init()//�������������������
{
	int a, b;
	for (a = 0; a < EDGE; a++)
	{
		for (b = 0; b < EDGE; b++)
		{
			block[a][b] = 0;
		}
	}
	system("cls");
	printf("\n\n\n\n\n\n                                       Thank you for choosing my GOBANG.\n\n\n");
	printf("                                  ��-----------�� \n");
	printf("                             Use  ��     W     ��     to move and 'Q' to press.\n");
	printf("                                  ��  A  S  D  �� \n");
	printf("                                  ��-----------�� \n\n");
	readallhistorys();
	displayallhistorys();
	printf("                             Input the two players' name below before the chess.\n\n\n");
	printf("                                                     ");
	scanf("%s%s", &name1, &name2);
	//addhistory(name1, name2, "1");
	//writeallhistorys();

}
void right()
{
	if (coord[1] + 1 >= EDGE)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[1]++;
	}
	board();
}
void left()
{
	if (coord[1] - 1 < 0)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[1]--;
	}
	board();
}
void up()
{
	if (coord[0] - 1 < 0)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[0]--;
	}
	board();
}
void down()
{
	if (coord[0] + 1 >= EDGE)
	{
		printf("\nCannot move on account of edge achievement.\n");
		return;
	}
	else
	{
		coord[0]++;
	}
	board();
}
void press()
{
	char ch;
	if (!set())//�ж��Ƿ��Ѿ���һ������
	{
		block[coord[0]][coord[1]] = player;//player����ұ�ʶ.
	}
	else
	{
		printf("\nCannot press here, it's been taken up.\n");
		return; //return��Ϊ�˲�������������,��ֹδ�ɹ���������� player��ʶ������.
	}
	if (win())
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		if (player == 1)
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                  NO.1 wins\n");
		if (player == 2)
			printf("\n                                                  NO.2 wins\n");
		printf("                                     Press 'c' to continue, 'e' to exit\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		ch = getche();
		while (1)
		{
			switch (ch)
			{
			case 'e':
				exit(0);
			case 'c':
				init();//�������̳�ʼ����
				coord[0] = EDGE / 2;//���۽�λ�÷ŵ����ġ�
				coord[1] = EDGE / 2;
				return;
			default:
				printf("\nInvalid character. Try again.\n");
			}
		}
	}
	if (player == 1)//��һ����������������Ժ�,��player�Ե�.
	{
		player = 2;
	}
	else
	{
		player = 1;
		return;
	}

}
int set()//0����˴�û������,���Խ����������,1������.
{
	if (block[coord[0]][coord[1]] == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int win()//����˵��һ�� �����x����block�ĵ�һ������,y����block�ĵڶ�������,��x����������϶�Ӧ����ֱ����,y�������̵ĺ�����.
{
	int a, x, y;//Լ�����ĸ�Ϊ��������
	int heng = 1, shu = 1, zuoxie = 1, youxie = 1;//�ĸ��������������,֮ǰ����һ���߼�����,������ȫ�����0��,��ʵӦ����1,��Ϊ�µ��Ǹ����ӱ������һ��.
	for (a = -1; a > -5; a--)//�����жϿ�ʼ
	{
		x = coord[0], y = coord[1] + a;//x,y��������,�����Ǵ��ݸ�isOver�ж��Ƿ񳬳��߽�
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			heng++;
		}
		else
		{
			break;
		}
	}

	for (a = 1; a < 5; a++)//����ڶ��׶�
	{
		x = coord[0], y = coord[1] + a;//x,y��������,�����Ǵ��ݸ�isOver�ж��Ƿ񳬳��߽�
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			heng++;
		}
		else
		{
			break;
		}
	}

	for (a = -1; a > -5; a--)//�����жϿ�ʼ
	{
		x = coord[0] + a, y = coord[1];
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			shu++;
		}
		else
		{
			break;
		}
	}
	for (a = 1; a < 5; a++)//������׶�
	{
		x = coord[0] + a, y = coord[1];
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			shu++;
		}
		else
		{
			break;
		}
	}
	for (a = -1; a > -5; a--)//��б��ʼ
	{
		x = coord[0] - a, y = coord[1] + a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			zuoxie++;
		}
		else
		{
			break;
		}
	}
	for (a = 1; a < 5; a++)//��б���׶�
	{
		x = coord[0] - a, y = coord[1] + a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			zuoxie++;
		}
		else
		{
			break;
		}
	}
	for (a = -1; a > -5; a--)//��б��ʼ
	{
		x = coord[0] + a, y = coord[1] + a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			youxie++;
		}
		else
		{
			break;
		}
	}
	for (a = -1; a > -5; a--)//��б���׶�
	{
		x = coord[0] - a, y = coord[1] - a;
		if (cross(x, y))
		{
			break;
		}
		if (block[x][y] == player)
		{
			youxie++;
		}
		else
		{
			break;
		}
	}
	if (heng >= 5 || shu >= 5 || zuoxie >= 5 || youxie >= 5)//�ĸ�������,��û�д��ڵ���5��
	{
		addhistory(name1, name2, player == 1 ? "1" : "2");
		writeallhistorys();
		return 1;

	}
	else
	{
		return 0;
	}
}
int cross(int x, int y)//��������x,y���������������жϵ�block���������.����ֵԼ��1�������߽�,0�����ڱ߽���.
{
	if (x > EDGE - 1 || x<0 || y>EDGE - 1 || y < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
