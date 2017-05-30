

/*������һ����VC++�е���ͨ�����ýṹ������ʵ�ֵ���Ϣ������򣬵��Թ����У���TC�����еĳ�����Ҫ�����������޸ģ�
1. clrscr(); ��������VCʶ�𣬽����滻Ϊsystem("cls");  ͬʱ��Ҫ��ǰ������ #include <windows.h>
2. gotoxy();��������VCʶ���ڳ������������һ��VC��д���Զ��庯�� void gotoxy(int x,int y)��ͬʱ���亯���������ڳ���ǰ����Զ��庯����������
3. getch();��������VCʶ�𣬸�Ϊgetchar();
*/

/******ͷ�ļ���.h��***********/
#include "stdio.h"   /*I/O����*/
#include "stdlib.h" /*��׼�⺯��*/
#include "string.h"/*�ַ�������*/
#include "ctype.h" /*�ַ���������*/
#include <windows.h> 

#define M 50  /*���峣����ʾ��¼��*/
int addresscount;  /*�����¼����*/

typedef struct /*�������ݽṹ*/
{
	char name[20]; /*����*/
	char company[30];  /*��λ*/
	char telephone[10];  /*�绰*/
}address;
address alladdress[M];  /*����ṹ������*/

/*�����¼���β�Ϊ�ṹ�����飬����ֵ��������Ϊ���ͱ�ʾ��¼����*/
void  enter() {
	int i, n;
	system("cls"); /*����*/
	printf("\n�������¼��\n"); /*��ʾ��Ϣ*/
	scanf("%d", &n); /*�����¼��*/
	printf("�������¼\n"); /*��ʾ�����¼*/
	printf("����             ��λ                     �绰\n");
	printf("------------------------------------------------\n");
	for (i = 0; i < n; i++)
	{
		scanf("%s%s%s", alladdress[i].name, alladdress[i].company, alladdress[i].telephone);  /*�����¼*/
		printf("----------------------------------------------\n");
	}
	addresscount = n;  /*���ؼ�¼����*/
}

/*��ʾ��¼������Ϊ��¼����ͼ�¼����*/
void list()
{
	int i;
	system("cls");
	printf("\n\n******************��ϵ��******************\n");
	printf("����             ��λ                     �绰\n");
	printf("------------------------------------------------\n");
	for (i = 0; i < addresscount; i++)
		printf("%-20s%-30s%-10s\n", alladdress[i].name, alladdress[i].company, alladdress[i].telephone);
	if ((i + 1) % 10 == 0)   /*�ж�����Ƿ�ﵽ10����¼*/
	{
		printf("�����������...\n"); /*��ʾ��Ϣ*/
		getchar();  /*ѹ���������*/
	}
	printf("************************end*******************\n");
}


/*��ʾָ����һ����¼*/
void displayone(address addr)
{
	system("cls");
	printf("\n\n********************************************\n");
	printf("name                unit                      telephone\n");
	printf("------------------------------------------------\n");
	printf("%-20s%-30s%-10s\n", addr.name, addr.company, addr.telephone);
	printf("**********************end***********************\n");
}
/*���Һ���������name */
int find(char *name)
{
	int i;
	for (i = 0; i < addresscount; i++)/*�ӵ�һ����¼��ʼ��ֱ�����һ��*/
	{
		if (strcmp(name, alladdress[i].name) == 0)  /*��¼�е������ʹ��Ƚϵ������Ƿ����*/
			return i;   /*��ȣ��򷵻ظü�¼���±�ţ�������ǰ�����*/
	}
	return i;  /*����iֵ*/
}

/*���Ҽ�¼*/
void search(int length)
{
	char s[20];   /*��������������ַ���*/
	int i;   /*������ҵ��������*/
	system("cls");   /*����*/
	printf("please search name\n");
	scanf("%s", s); /*�������������*/
	i = find(s); /*����find�������õ�һ������*/
	if (i > length - 1)  /*�������iֵ����n-1��˵��û�ҵ�*/
		printf("not found\n");
	else
		displayone(alladdress[i]);  /*�ҵ���������ʾ������ʾ��¼*/
}

/*ɾ������������Ϊ��¼����ͼ�¼����*/
void deleteaddress()
{
	char s[20];  /*Ҫɾ����¼������*/
	int ch = 0;
	int i, j;
	printf("please deleted name\n"); /*��ʾ��Ϣ*/
	scanf("%s", s);/*��������*/
	i = find(s); /*����find����*/
	if (i > addresscount - 1)  /*���i>n-1����������ĳ���*/
		printf("no found not deleted\n"); /*��ʾû�ҵ�Ҫɾ���ļ�¼*/
	else
	{
		displayone(alladdress[i]); /*�������������ʾ������¼��Ϣ*/
		printf("Are you sure delete it(1/0)\n");  /*ȷ���Ƿ�Ҫɾ��*/
		scanf("%d", &ch);  /*����һ������0��1*/
		if (ch == 1)  /*���ȷ��ɾ������Ϊ1*/
		{
			for (j = i + 1; j < addresscount; j++)  /*ɾ���ü�¼��ʵ�ʺ�����¼ǰ��*/
			{
				strcpy(alladdress[j - 1].name, alladdress[j].name); /*����һ����¼������������ǰһ��*/
				strcpy(alladdress[j - 1].company, alladdress[j].company); /*����һ����¼�ĵ�λ������ǰһ��*/
				strcpy(alladdress[j - 1].telephone, alladdress[j].telephone); /*����һ����¼�ĵ绰������ǰһ��*/
			}
			addresscount--;  /*��¼����1*/
		}
	}
}
/*�����¼����������Ϊ�ṹ������ͼ�¼��*/
void insert()/*���뺯��������Ϊ�ṹ������ͼ�¼��*/
{
	address temp;  /*�²����¼��Ϣ*/
	int i, j;
	char s[20]; /*ȷ���������ĸ���¼֮ǰ*/
	printf("please input record\n");
	printf("************************************************\n");
	printf("name                unit                      telephone\n");
	printf("--------------------------------------------------\n");
	scanf("%s%s%s", temp.name, temp.company, temp.telephone); /*���������Ϣ*/
	printf("------------------------------------------------\n");
	printf("please input locate name \n");
	scanf("%s", s); /*�������λ�õ�����*/
	i = find(s);  /*����find��ȷ������λ��*/
	for (j = addresscount - 1; j >= i; j--)   /*�����һ����㿪ʼ����ƶ�һ��*/
	{
		strcpy(alladdress[j + 1].name, alladdress[j].name); /*��ǰ��¼��������������һ��*/
		strcpy(alladdress[j + 1].company, alladdress[j].company); /*��ǰ��¼�ĵ�λ��������һ��*/
		strcpy(alladdress[j + 1].telephone, alladdress[j].telephone); /*��ǰ��¼�ĵ绰��������һ��*/
	}
	strcpy(alladdress[i].name, temp.name); /*���²����¼��������������i��λ��*/
	strcpy(alladdress[i].company, temp.company); /*���²����¼�ĵ�λ��������i��λ��*/
	strcpy(alladdress[i].telephone, temp.telephone); /*���²����¼�ĵ绰��������i��λ��*/
	addresscount++;   /*��¼����1*/
}
/*���溯��������Ϊ�ṹ������ͼ�¼��*/
void save()
{
	int i;
	FILE *fp;  /*ָ���ļ���ָ��*/
	if ((fp = fopen("record.txt", "wb")) == NULL)  /*���ļ������жϴ��Ƿ�����*/
	{
		printf("�򲻿��ļ�\n");/*û��*/
		exit(1);  /*�˳�*/
	}
	printf("\n�����ļ�����\n"); /*�����ʾ��Ϣ*/
	fprintf(fp, "%d", addresscount);  /*����¼��д���ļ�*/
	fprintf(fp, "\r\n");  /*�����з���д���ļ�*/
	for (i = 0; i < addresscount; i++)
	{
		fprintf(fp, "%-20s%-30s%-10s", alladdress[i].name, alladdress[i].company, alladdress[i].telephone);/*��ʽд���¼*/
		fprintf(fp, "\r\n"); /*�����з���д���ļ�*/
	}
	fclose(fp);/*�ر��ļ�*/
	printf("����ɹ�\n"); /*��ʾ����ɹ�*/
}
/*���뺯��������Ϊ�ṹ������*/
int read()
{
	int i, n;
	FILE *fp; /*ָ���ļ���ָ��*/
	if ((fp = fopen("record.txt", "rb")) == NULL)/*���ļ�*/
	{
		printf("�򲻿��ļ�\n");  /*���ܴ�*/
		exit(1);  /*�˳�*/
	}
	fscanf(fp, "%d", &n); /*�����¼��*/
	for (i = 0; i < n; i++)
		fscanf(fp, "%20s%30s%10s", alladdress[i].name, alladdress[i].company, alladdress[i].telephone); /*����ʽ�����¼*/
	fclose(fp);  /*�ر��ļ�*/
	printf("�ɹ���ȡ�ļ�!!!\n"); /*��ʾ����ɹ�*/
	return n; /*���ؼ�¼��*/
}
/*�������ʾ��¼����*/
void display()
{
	int id, n;
	FILE *fp; /*ָ���ļ���ָ��*/
	if ((fp = fopen("record.txt", "rb")) == NULL) /*���ļ�*/
	{
		printf("can not open file\n"); /*���ܴ��ļ�*/
		exit(1);  /*�˳�*/
	}
	printf("���������...\n"); /*��ʾ��Ϣ*/
	scanf("%d", &id);  /*�������*/
	fscanf(fp, "%d", &n); /*���ļ������¼��*/
	if (id >= 0 && id < n) /*�ж�����Ƿ��ڼ�¼��Χ��*/
	{
		fseek(fp, (id - 1) * sizeof(address), 1); /*�ƶ��ļ�ָ�뵽�ü�¼λ��*/
		displayone(alladdress[id]); /*�������������ʾ�ü�¼*/
		printf("\r\n");
	}
	else
		printf("û�����Ϊ %d �ļ�¼!!!\n ", id); /*�����Ų�������ʾ��Ϣ*/
	fclose(fp);  /*�ر��ļ�*/
}
/*������������Ϊ�ṹ������ͼ�¼��*/
void sort()
{
	int i, j, flag;
	address temp; /*��ʱ����������������*/
	for (i = 0; i < addresscount; i++)
	{
		flag = 0;  /*���־�ж��Ƿ���������*/
		for (j = 0; j < addresscount - 1; j++)
			if ((strcmp(alladdress[j].name, alladdress[j + 1].name)) > 0) /*�Ƚϴ�С*/
			{
				flag = 1;
				strcpy(temp.name, alladdress[j].name);  /*������¼*/
				strcpy(temp.company, alladdress[j].company);
				strcpy(temp.telephone, alladdress[j].telephone);
				strcpy(alladdress[j].name, alladdress[j + 1].name);
				strcpy(alladdress[j].company, alladdress[j + 1].company);
				strcpy(alladdress[j].telephone, alladdress[j + 1].telephone);
				strcpy(alladdress[j + 1].name, temp.name);
				strcpy(alladdress[j + 1].company, temp.company);
				strcpy(alladdress[j + 1].telephone, temp.telephone);
			}
		if (flag == 0)break;  /*�����־Ϊ0��˵��û�з���������ѭ������*/
	}
	printf("����ɹ�!!!\n"); /*��ʾ����ɹ�*/
}
/*���ٲ��ң�����Ϊ�ṹ������ͼ�¼��*/
void binarysearch()
{
	char s[20];
	int l, r, m;
	printf("\nȷ���ڲ���֮ǰ����¼�Ƿ�������!\n"); /*��ʾȷ���ڲ���֮ǰ����¼�Ƿ�������*/
	printf("�����������������\n"); /*��ʾ����*/
	scanf("%s", s); /*��������ҵ�����*/
	l = 0; r = addresscount - 1;  /*������߽����ұ߽�ĳ�ֵ*/
	while (l <= r) /*����߽�<=�ұ߽�ʱ*/
	{
		m = (l + r) / 2; /*�����м�λ��*/
		if (strcmp(alladdress[m].name, s) == 0) /*���м��������ֶ����Ƚ����Ƿ����*/
		{
			displayone(alladdress[m]); /*�����ȣ������print������ʾ��¼��Ϣ*/
			return; /*����*/
		}
		if (strcmp(alladdress[m].name, s) < 0)  /*����м���С*/
			l = m + 1;  /*�޸���߽�*/
		else
			r = m - 1; /*�����м�����޸��ұ߽�*/
	}
	if (l > r)   /*�����߽�����ұ߽�ʱ*/
		printf("û�ҵ�\n"); /*��ʾû�ҵ�*/
}
/*�����ļ�*/
void copy()
{
	char outfile[20]; /*Ŀ���ļ���*/
	int i, n;
	address temp[M];  /*������ʱ����*/
	FILE *sfp, *tfp; /*����ָ���ļ���ָ��*/
	system("cls");/*����*/
	if ((sfp = fopen("record.txt", "rb")) == NULL) /*�򿪼�¼�ļ�*/
	{
		printf("���ܴ��ļ���Ϣ\n"); /*��ʾ���ܴ��ļ���Ϣ*/
		exit(1); /*�˳�*/
	}
	printf("�����ļ��������� c:\\f1\\te.txt:\n"); /*��ʾ��Ϣ*/
	scanf("%s", outfile); /*����Ŀ���ļ���*/
	if ((tfp = fopen(outfile, "wb")) == NULL) /*��Ŀ���ļ�*/
	{
		printf("���ܴ��ļ���Ϣ\n"); /*��ʾ���ܴ��ļ���Ϣ*/
		exit(1); /*�˳�*/
	}
	fscanf(sfp, "%d", &n); /*�����ļ���¼��*/
	fprintf(tfp, "%d", n);/*д��Ŀ���ļ���*/
	fprintf(tfp, "\r\n"); /*д�뻻�з�*/
	for (i = 0; i < n; i++)
	{
		fscanf(sfp, "%20s%30s%10s\n", temp[i].name, temp[i].company,
			temp[i].telephone); /*�����¼*/
		fprintf(tfp, "%-20s%-30s%-10s\n", temp[i].name,
			temp[i].company, temp[i].telephone); /*д���¼*/
		fprintf(tfp, "\r\n"); /*д�뻻�з�*/
	}
	fclose(sfp); /*�ر�Դ�ļ�*/
	fclose(tfp); /*�ر�Ŀ���ļ�*/
	printf("���Ƴɹ�!!!\n"); /*��ʾ���Ƴɹ�*/
}
void gotoxy(int x, int y) //cursor an gewuenschte position auf dem bildschirm setzen 
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; //variablendklaration 
	HANDLE hConsoleOut;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	csbiInfo.dwCursorPosition.X = x; //cursorposition X koordinate festlegen 
	csbiInfo.dwCursorPosition.Y = y; //cursorposition Y koordinate festlegen 
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition); //den cursor an die festgelegte koordinate setzen 
}

int menu_select()
{
	char s[80];
	int c;
	gotoxy(1, 25);/*����궨Ϊ�ڵ�25�У���1��*/
	printf("ѹ���������......\n");/*��ʾѹ���������*/
	getchar(); /*���������ַ�*/
	system("cls"); /*����*/
	gotoxy(1, 1);
	printf("********************MENU*********************\n\n");
	printf("		0. �����¼\n");
	printf("		1. ��ʾ�ļ�����\n");
	printf("		2. ͨ���������Ҽ�¼\n");
	printf("		3. ɾ����¼\n");
	printf("		4. ��Ӽ�¼\n");
	printf("		5. �����ļ�\n");
	printf("		6. ���ļ�\n");
	printf("		7. �������\n");
	printf("	        8. ���򲢱������ļ�\n");
	printf("	        9. ���ٲ���\n");
	printf("		10. ���Ƶ����ļ�\n");
	printf("	        11. �˳�\n");
	printf("***********************************************\n");
	do {
		printf("\n	 ��ѡ����(0~11):"); /*��ʾ����ѡ��*/
		scanf("%s", s); /*����ѡ����*/
		c = atoi(s); /*��������ַ���ת��Ϊ������*/
	} while (c < 0 || c>11); /*ѡ�����0~11֮������*/
	return c; /*����ѡ�����������ݸ���������Ӧ�ĺ���*/
}

/******��������ʼ*******/
void main()
{
	system("cls");  /*����*/
	for (;;)/*����ѭ��*/
	{
		switch (menu_select())   /*�������˵�����������ֵ������������������*/
		{
		case 0: enter(); break;/*�����¼*/
		case 1:list(); break; /*��ʾȫ����¼*/
		case 2:search(addresscount); break; /*���Ҽ�¼*/
		case 3:deleteaddress(); break; /*ɾ����¼*/
		case 4:insert();  break;   /*�����¼*/
		case 5:save(); break; /*�����ļ�*/
		case 6:addresscount = read(); break; /*���ļ�*/
		case 7:display(); break;  /*�������ʾ��¼*/
		case 8:sort(); break; /*����������*/
		case 9:binarysearch(); break; /*���ٲ��Ҽ�¼*/
		case 10:copy(); break; /*�����ļ�*/
		case 11:exit(0); /*�緵��ֵΪ11��������*/
		}
	}
}