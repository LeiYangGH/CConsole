#include<string.h>
#include<stdlib.h>
#include <stdio.h>
#include <windows.h>
struct password               /*���ܷ����ṹ����*/
{
	char ps[10];                /*�����ַ���*/
	long wd;                   /*���ܵ��ֽ���*/
};
struct password password;
char s[100];
void set()                          //���ܷ������ú���
{
	printf("\n��������ַ���:");
	scanf("%s", password.ps);
	printf("\n��������ֽ���:");
	scanf("%ld", &password.wd);
	getchar();
	printf("\n");
	system("pause");             /*ϵͳ�����������������,ʹ��������*/
}

void Printtxt()             /*��ʾԭʼ�ļ��ͽ����ļ�����*/
{
	/*�Զ���ʽ���ļ�*/
	FILE  *source = fopen("ԭʼ�ļ�.txt", "rt");
	FILE  *result = fopen("�����ļ�.txt", "r");
	FILE  *recall = fopen("�����ļ�.txt", "rt");
	char c;     //��ʱ�ַ��洢����
	if (source == NULL)
	{
		printf("�޷��� ԭʼ�ļ�.txt \n");
		exit(0);
	}

	if (result == NULL)
	{
		printf("�޷��� �����ļ�.txt \n");
		exit(0);
	}

	if (recall == NULL)
	{
		printf("�޷��� �����ļ�.txt \n");
		exit(0);
	}
	c = fgetc(source);  //�ȴ�ԭʼ�ļ�����һ���ַ����������ļ���β�����ļ����ݷǿ�
	if (c == EOF)  //�ļ�����Ϊ�գ���������ַ�
	{
		printf("\n�����ַ���");
		printf("%s\n", s);
	}
	else      //�ļ��ǿգ����ԭʼ�ļ�
	{
		printf("\nԭʼ�ļ���");
		printf("%c", c);
		while ((c = fgetc(source)) != EOF)
			printf("%c", c);
	}
	printf("\n");
	printf("\n�����ļ���");
	while ((c = fgetc(result)) != EOF)   //�ļ��ǿգ���������ļ�
		printf("%c", c);
	printf("\n");

	printf("\n�����ļ���");
	while ((c = fgetc(recall)) != EOF)   //�ļ��ǿգ���������ļ�
		printf("%c", c);
	printf("\n");
	fclose(source);
	fclose(result);
	fclose(recall);
	printf("\n");
	system("pause");
}

void encode()                        /*���ܺ���*/
{
	int m, n = strlen(password.ps), i, flag = 1;     //m�洢�����ַ����� ,n�洢�����ַ������� ,i Ϊ��ʱ����
	char N = 0, w = 0;
	char c = 0, C = 0;   //��ʱ�ַ��洢����
	FILE  *result = fopen("�����ļ�.txt", "wt");
	FILE  *source = fopen("ԭʼ�ļ�.txt", "wt");
	if (result == NULL)
	{
		printf("�޷��� �����ļ�.txt \n");
		exit(0);
	}

	if (source == NULL)
	{
		printf("�޷��� ԭʼ�ļ�.txt \n");
		flag = 0;
	}

	flag = 0;
	int b;
	printf("\n��ѡ����ܶ���:\n");
	printf("\n1.�����ַ���\n");
	printf("\n2.�����ļ�\n");
	scanf("%d", &b);
	if (b == 1) { flag = 0; }
	else {
		FILE  *fp;
		char filename[30];
		printf("�������ļ���:(�����ļ���׺��)\n");
		scanf("%s", filename);
		if ((fp = fopen(filename, "r")) != NULL) {
			printf("�ļ��򿪳ɹ�! \n");
			flag = 1;
			while (!feof(fp)) {
				char n;
				n = fgetc(fp);
				fputc(n, source);
			}
			printf("�ļ����Ƴɹ�!\n");
		}
		else {
			printf("�ļ���ʧ��!\n");
			exit(0);
		}
		fclose(source);
	}

	if (flag == 0)      //�ж��ļ��Ƿ�Ϊ�գ�Ϊ�յĻ����������ַ�����
	{
		printf("������Ҫ���ܵ��ַ�����\n");
		scanf("%s", s);
		m = strlen(s);
		fprintf(source, "%s", s);
		int a = 0;
		for (i = 0; i<m; i++)
		{
			if (a<password.wd)
			{
				N = s[i] + password.ps[a%n] - 48;
				if (N>122)
				{
					N = N % 122;          /*ģ����*/
				}
				fputc(N, result);
				a++;
			}
			else
				fputc(s[i], result);
		}
	}
	else                //�ļ��ǿգ����ļ�����      
	{
		fopen("ԭʼ�ļ�.txt", "r");
		C = fgetc(source);
		w = C + password.ps[0 % n] - 48;
		fputc(w, result);
		int a = 1;
		for (i = 0; (c = fgetc(source)) != EOF; i++)
		{
			if (a<password.wd)
			{
				N = c + password.ps[a%n] - 48;
				if (N>122)
				{
					N = N % 122;              /*ģ����*/
				}
				fputc(N, result);
				a++;
			}
			else {
				fputc(c, result);
			}
		}
	}
	printf("\n���ܳɹ�!\n");
	fclose(result);
	fclose(source);
	printf("\n");
	system("pause");
}
void decode()                    /*���ܺ���*/
{
	FILE * recall = fopen("�����ļ�.txt", "wt");
	FILE * result = fopen("�����ļ�.txt", "rt");
	char c, N;
	int n = strlen(password.ps), i;  //n�洢�����ַ�������,iΪ��ʱ����
	if (result == NULL)
	{
		printf("�޷��� �����ļ�.txt \n");
		exit(0);
	}
	if (recall == NULL)
	{
		printf("�޷��� �����ļ�.txt \n");
		exit(0);
	}
	int a = 0;
	for (i = 0; (c = fgetc(result)) != EOF; i++)  //�Լ����ļ���������
	{

		if (a<password.wd)
		{
			N = c - (password.ps[a%n] - 48);
			if (N<0)
			{
				N = (N + 122) % 122;            /*ģ����*/
				fputc(N, recall);
			}
			else
			{
				if (N == 0)
					fputc('z', recall); //�����ܽ�������recall�ļ�
				else
					fputc(N, recall);
			}
			a++;
		}
		else {
			fputc(c, recall);
		}
	}
	printf("\n���ܳɹ�!\n");
	fclose(result);
	fclose(recall);
	printf("\n");
	system("pause");
}
void cmptxt()              /*�ȽϽ����ļ���ԭʼ�ļ���һ���ԣ�һ�����ԭ�ַ�����һ����'_'*/ {

	FILE  *source = fopen("ԭʼ�ļ�.txt", "rt");

	FILE  *recall = fopen("�����ļ�.txt", "rt");
	char c, d;     //��ʱ�ַ��洢����

	if (source == NULL)
	{
		printf("������ ԭʼ�ļ�.txt �ļ�\n");
		exit(0);
	}
	if (recall == NULL)
	{
		printf("������ �����ļ�.txt �ļ�\n");
		exit(0);
	}//�ȴ�ԭʼ�ļ�����һ���ַ����������ļ���β�����ļ����ݷǿ�
	c = fgetc(source);
	d = fgetc(recall);
	if (c == EOF)
	{
		printf("���ļ�����!!\n");
		exit(0);
	}

	if (d == EOF)
	{
		printf("���ļ�����!!\n");
		exit(0);
	}

	printf("�ļ��Ƚ�:");

	while ((c = fgetc(source)) != EOF && (d = fgetc(recall)) != EOF)  //�ļ��ǿյ����ж�
	{
		if (c == d) //�Ƚϣ�����ַ�
		{
			printf("%c", c);
		}
		else printf("�ļ��Ƚϲ�һ��!");
		break;
	}

	printf("\n");


	fclose(source);

	fclose(recall);
	printf("\n");
	system("pause");
}
void menu() //�˵�����
{
	printf("�ļ��ӽ��ܣ�\n");
	printf("                       \n");
	printf("1.���ü��ܷ���        \n");
	printf("                       \n");
	printf("2.����          \n");
	printf("                       \n");
	printf("3.����          \n");
	printf("                       \n");
	printf("4.��ʾ���ļ�          \n");
	printf("                       \n");
	printf("5.�˳�             \n");
	printf("                       \n");
	printf("��ѡ��:");
}
void creat() //�����ļ�
{
	FILE *f1 = fopen("ԭʼ�ļ�.txt", "wt");
	FILE *f2 = fopen("�����ļ�.txt", "wt");
	FILE *f3 = fopen("�����ļ�.txt", "wt");
	fclose(f1);
	fclose(f2);
	fclose(f3);
}
int main() //������������ѡ��
{
	int a = 0;
	menu();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	system("color 3E");
	while (a != 5)
	{
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			creat();
			set();
			system("cls");
			menu();
			break;
		case 2:
			encode();
			system("cls");
			menu();
			break;
		case 3:
			decode();
			system("cls");
			menu();
			break;
		case 4:
			Printtxt();
			system("cls");
			menu();
			break;
		case 5:
			printf("\n ���� !\n\n");
			break;
		default:
			printf("\n ���ٴ�����! \n");
			scanf("%d", &a);
			system("cls");
			menu();
			break;
		}
	}
}




