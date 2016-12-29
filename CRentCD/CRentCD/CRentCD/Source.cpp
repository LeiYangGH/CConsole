#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define DEV 1
#define MAX_COUNT 20
#define MAX_STRLEN 20
#define FORMAT_CD "%d\t%s\n"
#define MEMBERS_CD cd.no, cd.name
#define LINE  "\n------------------------\n"


typedef struct vcd
{
	int no;
	char name[20];
	struct vcd *next;
}cd;
typedef struct rentcd
{
	int no;
	char name[20];
	int date;
	struct rentcd *next;
}rentcd;
typedef struct customer
{
	char name[20];
	int vip;
	struct customer *next;
}customer;

vcd allvcds[MAX_COUNT];
int allvcdscount = 0;

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

void displayvcd(vcd cd)
{
	printf(FORMAT_CD, MEMBERS_CD);
}
void displayallvcds()
{
	int i;
	printf("����CD�������\r\n");
	printf("���\t����\r\n");
	printf(LINE);
	for (i = 0; i < allvcdscount; i++)
	{
		displayvcd(allvcds[i]);
	}
	printf(LINE);
}
void findcdbyno(int  no, vcd **cd)  //�������ֲ���CD
{
	//int i;
	//int found = 0;
	//for (i = 0; i < allvcdscount; i++)
	//{
	//	if (allvcds[i].no == no)
	//	{
	//		*cd = &allvcds[i];
	//		found = 1;
	//		break;
	//	}
	//}
	//if (!found)
	//{
	//	printf("û�ҵ������Ϊ%d��CD\r\n", no);
	//	*cd = NULL;
	//}
}
void addvcd(int no, char *name)
{
	vcd cd;
	cd.no = no;
	strcpy(cd.name, name);
	allvcds[allvcdscount++] = cd;
}

void inputvcds()
{
	int i, score;
	int no;
	char name[MAX_STRLEN] = "";
	while (1)
	{
		printf("\n\n������CD���(������0����):");
		scanf("%d", &no);
		if (no == 0)
		{
			printf("\n���ѽ������룡");
			break;
		}
		printf("\n������CD����:");
		scanf("%s", name);
		addvcd(no, name);
		printf("\nCD%s��Ϣ��ӳɹ�!\n", name);
	}
}

//int deletevcdbyno(vcd *L, char * no)
//{
//	vcd *p1 = L, *p2;
//	if (L == NULL)
//	{
//		printf("\nCD����Ϊ��!\n");
//		return 0;
//	}
//	while (!streq(p1->no, no) && p1->next != NULL)
//	{
//		p2 = p1;
//		p1 = p1->next;
//	}
//	if (streq(p1->no, no))
//	{
//		if (p1 == L)
//			L = p1->next;
//		else
//		{
//			p2->next = p1->next;
//			free(p1);
//			printf("��ɾ��ѧ��Ϊ%s��CD�ĳɼ���\r\n", no);
//			return 1;
//		}
//	}
//	else
//	{
//		printf("û�ҵ�ѧ��Ϊ%s��CD!\r\n", no);
//		return 0;
//	}
//}
//
//void findvcdbyname(char *name, vcd **stu)
//{
//	int found = 0;
//	vcd *p = stuhead;
//
//	while (p != NULL)
//	{
//		if (streq(p->name, name))
//		{
//			*stu = p;
//			return;
//		}
//		p = p->next;
//	}
//	if (!found)
//	{
//		printf("û�ҵ�����Ϊ%s��CD\r\n", name);
//		*stu = NULL;
//	}
//}

//int selectonecd(vcd *stu, int couno)
//{
//	cd *cd;
//
//	if (stu->selcouscnt >= 5)
//	{
//		printf("ѡ�β��ܳ���5��\r\n");
//		return 0;
//	}
//	findcdbyno(couno, &cd);
//	if (cd != NULL)
//	{
//		if (cd->stucnt < cd->no)
//		{
//			stu->selcds[stu->selcouscnt] = couno;
//			stu->totalpoints += cd->points;
//			stu->selcouscnt++;
//			cd->stucnt++;
//			printf("ѡ�γɹ���\r\n");
//			return 1;
//		}
//		else
//		{
//			printf("CD%s�Ѿ�ѡ����\r\n", cd->name);
//			return 0;
//		}
//	}
//}
//
//void selectcds(vcd *stu)
//{
//	int no;
//	if (stu == NULL)
//	{
//		printf("��������������ѡ�Σ�\n");
//		return;
//	}
//	do
//	{
//		printf("������Ҫѡ���CD�ţ�1��7����0����ѡ��");
//		scanf("%d", &no);
//		fseek(stdin, 0, SEEK_END);
//		if (no == 0)
//		{
//			if (stu->selcouscnt >= 3)
//			{
//				printf("�����˳���CDѡ��\n");
//				break;
//			}
//			else
//			{
//				printf("����ѡ������3��CD��\n");
//			}
//		}
//		selectonecd(stu, no);
//	} while (stu->selcouscnt <= 5);
//	printf("ѡ�ν�����\n");
//}


int main()
{
	int choice = -1;
	//inputvcds();
	//displayallvcds();
#if DEV
	addvcd(1, "cd1");
	addvcd(2, "cd2");
	addvcd(3, "cd3");
	//vcd *stu;
	//strcpy(curstuname, "ly");
	displayallvcds();

	//findvcdbyname(curstuname, &curstu);
	//selectonecd(curstu, 1);
	//selectonecd(curstu, 2);
	//selectonecd(curstu, 3);
	//selectonecd(curstu, 4);
	//selectonecd(curstu, 5);
	//selectonecd(curstu, 6);
	//findvcdbyname("sm", &stu);
	//selectonecd(stu, 1);
	//selectonecd(stu, 2);
	//selectonecd(stu, 5);
	//displayallstuselcds();
	//sortanddisplayallvcds();
#else
	while (choice != 0)
	{
		printf("\n\t CDѡ��");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ¼��CD��Ϣ");
		//printf("\n\t 2. �鿴����CD");
		printf("\n\t 3. �鿴����CD");
		//printf("\n\t 4. CD��¼����¼�����ѡ�Σ�");
		//printf("\n\t 5. ��ǰCDѡ��");
		//printf("\n\t 6. �鿴����CDѡ��");
		//printf("\n\t 7. CD��ѧ���ܻ����������");
		//printf("\n\t 8. ��������CD�ɼ�");
		//printf("\n\t 9. һ�ź����Ź��β������CD");
		printf("\n\n  ��ѡ��: ");
		choice = getche();
		switch (choice)
		{
		case '0':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			inputvcds();
			break;
			//case '2':
			//	printf("\n\n��ѡ���� 2\n");
			//	displayallcds();
			//	break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			displayallvcds();
			break;
			//case '4':
			//	printf("\n\n��ѡ���� 4\n");
			//	printf("�����������������س�����:");
			//	scanf("%s", curstuname);
			//	findvcdbyname(curstuname, &curstu);
			//	printf("��ǰCD������%s\n", curstuname);
			//	break;
			//case '5':
			//	printf("\n\n��ѡ���� 5\n");
			//	selectcds(curstu);
			//	break;
			//case '6':
			//	printf("\n\n��ѡ���� 6\n");
			//	displayallstuselcds();
			//	break;
			//case '7':
			//	printf("\n\n��ѡ���� 7\n");
			//	sortanddisplayallvcds();
			//	break;
			//case '8':
			//	printf("\n\n��ѡ���� 8\n");
			//	inputallstuscores();
			//	break;
			//case '9':
			//	printf("\n\n��ѡ���� 9\n");
			//	listallnamesbelow60forcou(1);
			//	listallnamesbelow60forcou(3);
			//	break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
}
	fseek(stdin, 0, SEEK_END);
#endif
	system("pause");
	return 0;
}