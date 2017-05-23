#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FILE_STU "stu.txt"
typedef struct student
{
	char no[20];
	char name[20];
	int age;
	char sex[5];
	char birthday[20];
	char address[20];
	char telephone[20];
	char email[20];
}student;

student allstudents[100];//�������ݿ�洢������û
int allstudentscount = 0;//ѧ������

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

//��ʾһ��ѧ��
void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", stu.no, stu.name, stu.age, stu.sex,
		stu.birthday, stu.address, stu.telephone, stu.email);
}

//���������õ���
int cmpstubyno(const void * a, const void * b)
{
	return ((student*)a)->no - ((student*)b)->no;
}

//��ʾ����ѧ��
void displayallstudents()
{
	int i;
	qsort(allstudents, allstudentscount, sizeof(student), cmpstubyno);//��������
	printf("����%d��������\r\n", allstudentscount);
	printf("--------------------------------------------\r\n");
	for (i = 0; i < allstudentscount; i++)
	{
		displaystudent(allstudents[i]);
	}
	printf("--------------------------------------------\r\n");
}
//������ѧ��д���ļ�
void writeallstudents()
{
	int i;
	student stu;
	FILE *fp = fopen(FILE_STU, "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_STU);
		getchar();
		exit(1);
	}
	for (i = 0; i < allstudentscount; i++)
	{
		stu = allstudents[i];
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s\r\n", stu.no, stu.name, stu.age, stu.sex,
			stu.birthday, stu.address, stu.telephone, stu.email);
	}
	fclose(fp);
	printf("�ѱ����¼���ļ���");
}



//��һ���ı���ֳ��ֶβ���ϳ�һ��ѧ��
student getstudentfromline(char *line)
{
	char *part;
	int index = 0;
	student stu;
	//strtok \t �Ǹ���Tab���
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(stu.no, part);
			break;
		case 2:
			strcpy(stu.name, part);
			break;
		case 3:
			stu.age = toint(part);
			break;
		case 4:
			strcpy(stu.sex, part);
			break;
		case 5:
			strcpy(stu.birthday, part);
			break;
		case 6:
			strcpy(stu.address, part);
			break;
		case 7:
			strcpy(stu.telephone, part);
			break;
		case 8:
			strcpy(stu.email, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return stu;
}

//���ļ�
void readallstudents()
{
	char line[200];
	FILE *fp = fopen(FILE_STU, "r");
	if (fp == NULL)
		return;
	else
	{
		allstudentscount = 0;
		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)//���в���
				continue;
			allstudents[allstudentscount++] = getstudentfromline(line);
		}
		printf("\n�Ѷ����ļ�!", FILE_STU);
	}
}

//��������
void searcbyname(char *name)
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (strcmp(name, allstudents[i].name) == 0)
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}
//�û����벢��������
void promptsearchbyname()
{
	char name[20];
	printf("����������:");
	scanf("%s", name);
	searcbyname(name);
}
//����ѧ��
void searchbyno(char no[20])
{
	int i;
	for (i = 0; i < allstudentscount; i++)
		if (streq(allstudents[i].no, no))
		{
			displaystudent(allstudents[i]);
			return;
		}
	printf("û�ҵ���Ӧѧ������Ϣ��\r\n");
}
//�û����벢����ѧ��
void promptsearchbyno()
{
	char no[20];
	printf("������Ҫ��ѯ��ѧ��:");
	scanf("%s", no);
	searchbyno(no);
}

//����ѧ��ɾ��ѧ��
void removestudent(char no[20])
{
	int i, index, found = 0;
	//�ҵ�ѧ����ͬ���±�index
	for (index = 0; index < allstudentscount; index++)
	{
		if (streq(allstudents[index].no, no))
		{
			found = 1;
			break;
		}
	}
	if (found)
	{
		//����ҵ����ͰѺ���Ķ���ǰ�ƶ�һλ���൱��ɾ��index���ڵ�ѧ����
		for (i = index; i < allstudentscount - 1; i++)
			allstudents[i] = allstudents[i + 1];
		allstudentscount--;
		writeallstudents();
		printf("ɾ����ϣ�ʣ��%d����\n", allstudentscount);
	}
	else
		printf("û�ҵ����޷�ɾ��\n");
}

//�û�����ѧ�Ų�ɾ��
void promptremove()
{
	char no[20];
	printf("������Ҫɾ����ѧ��:");
	scanf("%s", no);
	removestudent(no);
}

//���ѧ��
void addstudent(char no[20], char name[], int age, char sex[5],
	char birthday[20], char address[20], char telephone[20], char email[20])
{
	student stu;
	strcpy(stu.no, no);
	strcpy(stu.name, name);
	stu.age = age;
	strcpy(stu.sex, sex);
	strcpy(stu.birthday, birthday);
	strcpy(stu.address, address);
	strcpy(stu.telephone, telephone);
	strcpy(stu.email, email);
	allstudents[allstudentscount++] = stu;
	writeallstudents();
}

//�û����벢���ѧ��
void promptaddstudent()
{
	char no[20];
	char name[20];
	int age;
	char sex[5];
	char birthday[20];
	char address[20];
	char telephone[20];
	char email[20];
	printf("\n������ѧ�ţ����������䣬�Ա𣬳������£���ַ���绰��E-mail���ո�������س�����\n");
	scanf("%s%s%d%s%s%s%s%s", no, name, &age, sex, birthday, address, telephone, email);
	addstudent(no, name, age, sex, birthday, address, telephone, email);
	printf("��ɵ�%d�����¼��!\r\n", allstudentscount);
}


int main()
{
	int choice = -1;
	readallstudents();
#if 0

	//addstudent("01", "name1", 1, "F", "b1", "add1", "tel1111", "1dsfsfs@ssss");
	//addstudent("03", "name3", 3, "F", "b3", "add3", "tel1333", "3dsfsfs@ssss");
	//addstudent("02", "name2", 2, "M", "b2", "add2", "tel2222", "2ddfdsfs@fsss");

	//displayallstudents();
	//promptaddstudent();

	///*promptremovestudent();
	////promptsearchtotalbyname();
	////promptsearchtotalbyno();

	displayallstudents();
	//removestudent("03");
	//promptremovestudent();
	//promptsearchbyname();
	//promptsearchbyno();
	//displayallstudents();
	//searcbyname("name2");
	//searchbyno("033");
	//writeallstudents();

#else
	while (choice != 0)
	{
		printf("\n\t ѧ����Ϣ����ϵͳ");
		printf("\n\t 0. �˳�");
		printf("\n\t 1. ��ѧ�������������ѧ����Ϣ");
		printf("\n\t 2. ���ѧ����Ϣ");
		printf("\n\t 3. ��ѧ�Ų�ѯ");
		printf("\n\t 4. ��������ѯ");
		printf("\n\t 5. ��ѧ��ɾ��");
		printf("\n\n  ��ѡ��: ");
		fseek(stdin, 0, SEEK_END);//������뻺��������������Ƿ����������ѭ��
		choice = getchar();
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
			displayallstudents();
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			promptaddstudent();
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			promptsearchbyno();
			break;
		case '4':
			printf("\n\n��ѡ���� 3\n");
			promptsearchbyname();
			break;
		case '5':
			printf("\n\n��ѡ���� 3\n");
			promptremove();
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
	}
#endif
	printf("\n\n��������˳�\n");
	system("pause");

	return 0;
}

