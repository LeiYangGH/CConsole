//C���Կγ���ƣ���c�������һ��������ϵͳ������д����Ҫ��:
//������Ϣ��������֤�š��������Ա����䡢ѧ����סַ���绰�ȣ�����֤�Ų��ظ�����
//�����һ��������ϵͳ����ϵͳ�������¹��ܣ�
//1. ������Ϣ¼�빦��(������Ϣ���ļ����棬�����ڵ�����ֱ�Ӳ��Ҳ��򿪸��ļ���
//	2��������Ϣ�������
//	3������������
//	4�������������ѯ
//	5��������Ϣɾ��
//	6��������Ϣ�޸�

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_per "per.txt"
#define MAX_STRLEN 20
typedef struct person
{
	char id[20];
	char name[20];
	char sex[10];
	int age;
	char scholar[30];
	char address[50];
	char telephone[20];

}person;

person allpersons[100];
int allpersonscount = 0;

float averagechinese, averageage, averagescholar;

//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}


//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}


void displayperson(person per)
{
	printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\n", per.id, per.name, per.sex, per.age, per.scholar, per.address, per.telephone);
}

void displayallpersons()
{
	int i;
	printf("����%dλ������Ϣ����\r\n", allpersonscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allpersonscount; i++)
	{
		displayperson(allpersons[i]);
	}
	printf("--------------------------------------------\r\n");
}

//��һ���ı����벢����\t���Ų�֣���ϳ�һ��person
person getpersonfromline(char *line)
{
	char *part;
	int index = 0;
	person per;
	part = strtok(line, " \t\n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(per.id, part);
			break;
		case 2:
			strcpy(per.name, part);
			break;
		case 3:
			strcpy(per.sex, part);
			break;
		case 4:
			per.age = toint(part);
			break;
		case 5:
			strcpy(per.scholar, part);
			break;
		case 6:
			strcpy(per.address, part);
			break;
		case 7:
			strcpy(per.telephone, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \t\n");
	}
	return per;
}

void readallpersons()
{
	char line[200];
	FILE *fp = fopen(FILE_per, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_per);
	}
	else
	{
		allpersonscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allpersons[allpersonscount++] = getpersonfromline(line);
		}
		printf("\n�Ѷ����ļ�!", FILE_per);
	}
}

//qsort�ǿ�������Ҫ������д��������total����
int cmpfunc(const void * a, const void * b)
{
	return ((person*)a)->age - ((person*)b)->age;
}
void sortpersonsbyage()
{
	qsort(allpersons, allpersonscount, sizeof(person), cmpfunc);
}

void sortpersonsbytotalanddisplay()
{
	int i;
	sortpersonsbyage();
	printf("��ÿ�������������������\r\n");
	displayallpersons();
}

//���ݱ�Ų�����������
int getpersonidexbyno(char no[50])
{
	int i;
	for (i = 0; i < allpersonscount; i++)
	{
		if (streq(allpersons[i].id, no))
			return i;
	}
	return -1;//û�ҵ�
}

void writeallpersons()
{
	int i;
	person per;
	FILE *fp = fopen(FILE_per, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_per);
		getchar();
		exit(1);
	}
	for (i = 0; i < allpersonscount; i++)
	{
		per = allpersons[i];
		fprintf(fp, "%s\t%s\t%s\t%d\t%d\t%d\n", per.id, per.name, per.sex, per.age, per.scholar, per.age);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}

void editperson(char no[50])
{
	int i;
	char pwd[20] = "";
	i = getpersonidexbyno(no);
	if (i >= 0)
	{
		printf("\n���������ġ���ѧ��Ӣ��ɼ������������ո����\n");
		scanf("%d%d%d", &allpersons[i].age, &allpersons[i].age, &allpersons[i].scholar);
		writeallpersons();
		printf("�޸���ϡ�\r\n");
	}
	else
	{
		printf("û�ҵ���Ӧѧ�ŵľ���\r\n");
	}
}

void prompteditperson()
{
	char no[50];
	printf("������Ҫ�޸ĵ�ѧ��:");
	scanf("%s", &no);
	editperson(no);
}

void addperson(char id[], char name[], char sex[], int age, char scholar[], char address[], char telephone[])
{
	person per;
	strcpy(per.id, id);
	strcpy(per.name, name);
	strcpy(per.sex, sex);
	per.age = age;
	strcpy(per.scholar, scholar);
	strcpy(per.address, address);
	strcpy(per.telephone, telephone);
	allpersons[allpersonscount++] = per;
	writeallpersons();
}

void promptaddperson()
{
	char id[20];
	char name[20];
	char sex[10];
	int age;
	char scholar[30];
	char address[50];
	char telephone[20];
	printf("\n������֤�����ظ���:\n");
	scanf("%s", id);
	//dup
	printf("\n�������������Ա𣨶��ǲ����ո���ַ�����������(������)���ո����\n");
	scanf("%s%s%d", name, sex, &age);
	printf("\n������ѧ����סַ���绰�����ǲ����ո���ַ�����������̣����ո����\n");
	scanf("%s%s%s", scholar, address, telephone);
	addperson(id, name, sex, age, scholar, address, telephone);
	printf("��ɵ�%dλ����¼��!\r\n", allpersonscount);
}


void removeperson(char no[20])
{
	int i;
	int index;
	index = getpersonidexbyno(no);
	if (index >= 0)
	{
		for (i = index; i < allpersonscount - 1; i++)
			allpersons[i] = allpersons[i + 1];
		allpersonscount--;
		writeallpersons();
		printf("ɾ����ϣ�ʣ��%d����\r\n", allpersonscount);
	}
	else
	{
		printf("û�ҵ���Ӧѧ�ŵľ���\r\n");
	}

}

void promptremoveperson()
{
	char no[20];
	printf("������Ҫɾ����ѧ��:");
	scanf("%s", no);
	removeperson(no);
}

//��������
void searcbyname(char *name)
{
	int i;
	for (i = 0; i < allpersonscount; i++)
		if (strcmp(name, allpersons[i].name) == 0)
		{
			displayperson(allpersons[i]);
			return;
		}
	printf("û�ҵ���Ӧ�������Ϣ��\r\n");
}
//�û����벢��������
void promptsearchbyname()
{
	char name[20];
	printf("����������:");
	scanf("%s", name);
	searcbyname(name);
}

int main()
{
	char choice = -1;
#if 1//�����ã�if���ɾ��
	readallpersons();
	//addperson("05", "n5", "20170605", 41, 92, 93);
	//addperson("06", "n6", "20170606", 46, 96, 96);

	//editperson("01");
	////printf("\n%d\n", allpersonscount);
	///*promptaddperson();
	//writeallpersons();*/
	///*prompteditperson();
	//writeallpersons();*/
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallpersons();
	//promptsearchbyname();
	//sortpersonsbytotal();
	//prompteditperson();
	//promptremoveperson();
	//displayallpersons();


	system("pause");

#endif
	readallpersons();
	while (choice != 'g')
	{
		printf("\n\t ������Ϣ����ϵͳ");
		printf("\n\t 0---������Ϣ�Ĵ���");
		printf("\n\t 1---������Ϣ������");
		printf("\n\t 2---������Ϣ������");
		printf("\n\t 3---������Ϣ��ɾ��");
		printf("\n\t 4---������Ϣ���޸�");
		printf("\n\t 5---������Ϣ�Ĳ���");
		printf("\n\t 6---������Ϣ�����");
		printf("\n\t 7---�˳�\n\n");
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
		switch (choice)
		{
		case '0':
			printf("\n\n��ѡ���� 0\n");
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			sortpersonsbytotalanddisplay();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptaddperson();
			break;
		case '3':
			printf("\n\n��ѡ���� c\n");
			promptremoveperson();
			break;
		case '4':
			printf("\n\n��ѡ���� d\n");
			prompteditperson();
			break;
		case '5':
			printf("\n\n��ѡ���� e\n");
			promptsearchbyname();
			break;
		case '6':
			printf("\n\n��ѡ���� f\n");
			displayallpersons();
			break;
		case '7':
			printf("\n\n ��ѡ�����˳���");
			fseek(stdin, 0, SEEK_END);
			system("pause");
			exit(0);
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
	printf("\n\n��������˳�\n");
	system("pause");
	return 0;
}
