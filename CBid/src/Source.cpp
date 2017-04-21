#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "windows.h" 
#define BID_FORMAT_STRING "%s\t%d\t%d\t%d\t%d\t%d\t%d\r\n"
typedef struct bid
{
	char name[20];
	int price;
	int design;
	int fame;
	int duration;
	int quality;
	int total;
}bid;

bid allbids[50];//����50��
int allbidscount = 0;//��¼��

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//��ʾͶ������Ϣ
void displaybid(bid b)
{
	printf("\r\n");
	printf(BID_FORMAT_STRING,
		b.name,
		b.price, b.design, b.fame, b.duration, b.quality,
		b.total);
}

//�鿴����Ͷ������Ϣ
void viewallbids()
{
	int i;
	printf("����%dλͶ������Ϣ����\r\n", allbidscount);
	printf("--------------------------------------------\r\n");
	printf("Ͷ����\t����\tʩ��\t�ۺ�\t����\t����\t�ܷ�\r\n");
	for (i = 0; i < allbidscount; i++)
	{
		displaybid(allbids[i]);
	}
	printf("--------------------------------------------\r\n");
}

int calculatetotal(bid b)
{
	//��ѡ���㷨����Ȩƽ��
	/*int result = b.price * 60
		+ b.design * 10
		+ b.fame * 20
		+ b.duration * 5
		+ b.quality * 5;
	return (int)result / 100.0f;*/
	return b.price + b.design + b.fame + b.duration + b.quality;
}

void addbid(char name[20],
	int price, int design, int fame, int duration, int quality)
{
	bid b;
	strcpy(b.name, name);
	b.price = price;
	b.design = design;
	b.fame = fame;
	b.duration = duration;
	b.quality = quality;
	b.price = price;
	b.total = calculatetotal(b);
	allbids[allbidscount++] = b;
}

//����ʾ��Ͷ������Ϣ
void createsamplebids()
{
	printf("����ʾ��Ͷ������Ϣ...");
	addbid("����", 59, 9, 19, 4, 4);
	addbid("����", 58, 2, 5, 4, 1);
	addbid("����", 55, 3, 15, 1, 1);
	addbid("�ƹ��", 30, 5, 14, 1, 3);
	addbid("���", 23, 5, 17, 3, 5);
	addbid("��ǿ��", 45, 8, 5, 2, 2);
	addbid("����", 54, 4, 9, 2, 3);
	addbid("����", 25, 4, 11, 1, 1);
	addbid("�����", 56, 6, 18, 5, 5);
	printf("ʾ��Ͷ������Ϣ�Ѵ�����");
}


//������Ϣ
void inputstring(char str[], int maxlenth, char* purpose)
{
	int len = -1;
	char input[50] = "";
	while (len<1 || len > maxlenth)
	{
		printf("������%s��%d���ַ����ڣ����ܴ�Tab��س���:", purpose, maxlenth);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("���� %s Ϊ %s \r\n", purpose, str);
}

int inputint(int max, char* purpose)
{
	int len = -1;
	char input[50] = "";
	int score = 0;
	while (score <= 0 || score > max)
	{
		printf("������%s���������ֵ������%d:", purpose, max);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
		score = toint(input);
	}
	printf("����� %s Ϊ %d \r\n\r\n", purpose, score);
	return score;
}



//����name��Ͷ����
void findpatientbyid(char *name)
{
	int i;
	int found = 0;
	for (i = 0; i < allbidscount; i++)
	{
		bid b = allbids[i];
		if (strcmp(b.name, name) == 0)
		{
			found = 1;
			printf("���ҵ�Ͷ������Ϣ����\r\n");
			printf("--------------------------------------------\r\n");
			displaybid(b);
			break;
		}
	}
	if (found == 0)
		printf("û�ҵ�Ͷ����:%s!\r\n", name);
}

void promptaddbid()
{
	char name[20] = "";
	inputstring(name, 20, "Ͷ��������");
	addbid(name,
		inputint(60, "����"),
		inputint(10, "ʩ����֯���"),
		inputint(20, "Ͷ�굥λ�ۺϳɼ�"),
		inputint(5, "����"),
		inputint(5, "����")
	);
	printf("��ɵ�%d��Ͷ������Ϣ¼��!\r\n", allbidscount);
}

void promptfindbyname()
{
	char name[20] = "";
	inputstring(name, 20, "Ҫ���ҵ�Ͷ��������");
	findpatientbyid(name);
}

int iscountequal(int expected)
{
	if (allbidscount == expected)
		return 1;
	else
	{
		printf("������%d��Ͷ�ֻ꣬��Ͷ����Ϊ%dʱ����ִ�д˲�����\r\n", allbidscount, expected);
		return 0;
	}
}

int findworstid()
{
	int i;
	int worsttotal = 10000;
	int worstid;
	for (i = 0; i < allbidscount; i++)
	{
		bid b = allbids[i];
		if (b.total < worsttotal)
		{
			worsttotal = b.total;
			worstid = i;
		}
	}
	printf("��ͷ֣�%s\t ����:%d\r\n", allbids[worstid].name, allbids[worstid].total);
	return worstid;
}



void deleteworst()
{
	int i;
	int besttotal = 0;
	if (iscountequal(10))
	{
		int worstid = findworstid();
		if (worstid < allbidscount - 1)
			for (i = worstid; i < allbidscount - 1; i++)
				allbids[i] = allbids[i + 1];
		allbidscount--;
		printf("ɾ����ͷ�Ͷ������ϣ�ʣ��%d��Ͷ���ߡ�\r\n", allbidscount);
	}

}

void displaybest()
{
	int i;
	int besttotal = 0;
	bid best;
	if (iscountequal(9))
	{
		for (i = 0; i < allbidscount; i++)
		{
			bid b = allbids[i];
			if (b.total > besttotal)
			{
				besttotal = b.total;
				best = b;
			}
		}
		printf("�б��ߣ�%s\t ����:%d\r\n", best.name, best.total);
	}

}


int main()
{
	int choice = -1;

	//�������������ʾ������
	createsamplebids();

	while (choice != 0)
	{
		system("CLS");
		printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
		printf("\n\t------------------------------");
		printf("\n\n\t 1. ����Ͷ������Ϣ");
		printf("\n\t 2. ��ʾȫ��Ͷ������Ϣ");
		printf("\n\t 3. ����Ͷ�������Ʋ���");
		printf("\n\t 4. ɾ����ͷ�");
		printf("\n\t 5. ��ʾ�б���");
		printf("\n\t 0. �˳�");
		printf("\n\n ��ѡ��: ");
		scanf("%1[012345]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			promptaddbid();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			viewallbids();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptfindbyname();
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			deleteworst();
			break;
		case '5':
			printf("\n\n��ѡ���� 4\n");
			displaybest();
			break;

		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}

	system("pause");
	return 0;
}