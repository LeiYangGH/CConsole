#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#define FILE_UNAME "uname.txt"
typedef struct user//����һ��denglu�ṹ��
{
	char name[20];//����û���
	char password[20];//��Ӧ������
}user;//����ṹ�����
user allusers[30];
int alluserscount = 0;
//�ַ������
int streq(char *s1, char *s2)
{
	return strcmp(s1, s2) == 0;
}

//��һ���ı����벢����\t���Ų�֣���ϳ�һ��user
user getuserfromline(char *line)
{
	char *part;
	int index = 0;
	user u;
	part = strtok(line, " \n");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(u.name, part);
			break;
		case 2:
			strcpy(u.password, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, " \n");
	}
	return u;
}

void readallusers()
{
	char line[200];
	FILE *fp = fopen(FILE_UNAME, "r");
	if (fp == NULL)
	{
		printf("\n���ļ�%sʧ��!", FILE_UNAME);
	}
	else
	{
		alluserscount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			allusers[alluserscount++] = getuserfromline(line);
		}
		//printf("\n�Ѷ����û���������!", FILE_UNAME);
	}
}

void welcome()//��ҳ��
{
	system("cls");
	printf("\t\t       -----------------------------------------------\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t��ӭ����ϵͳ\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       |\t\t\t\t\t     |\n");
	printf("\t\t       -----------------------------------------------\n");
}
void choices()//��ҳ��
{
	system("cls");
	printf("\t\t\t0���鿴��Ʒ");
	printf("\t\t\t1��ѡ���Ʒ");
}

int getpassword(char name[], char password[])
{
	int i;
	for (i = 0; i < alluserscount; i++)
	{
		if (streq(allusers[i].name, name))
		{
			strcpy(password, allusers[i].password);
			return 1;
		}
	}
	return 0;
}

int validatepassword(char password[])
{
	int i = 3;
	char input[20] = "";

	do {
		printf("\n����������(����%d�λ���)��", i);
		scanf("%s", input);
		if (streq(input, password))
			return 1;
	} while (--i > 0);
	return 0;
}

void exitprogram()
{
	printf("\n\n��������˳�\n");
	system("pause");
	exit(0);
}
void login()
{
	char name[20] = "";
	char password[20] = "";
	printf("\n�������û�����");
	scanf("%s", name);
	if (getpassword(name, password))
	{
		if (!validatepassword(password))
		{
			printf("\n��¼ʧ�ܣ�\n");
			exitprogram();
		}
	}
	else
	{
		printf("�û��������ڣ�\n");
		exitprogram();
	}

}
//�˿͵�ˣ�������0��ʱ��ֹͣ
void book(int dishs[])
{
	int i = 0, n;
	printf("��ѡ��Ĳ�Ʒ�ǣ�");
	while (scanf("%d", &dishs[i]) && dishs[i])
		i++;
	n = i;
	printf("��ѡ��Ĳ�Ʒ�ǣ�");
	for (i = 0; i<n; i++)
		printf("%4d", dishs[i]);
}
#define TEST 1
int main()
{
	int cho;
	int dish[20];
	int choicetry = 3;
	char name[20] = "";
	char password[20];
	char choice[3] = "";

	readallusers();
#if TEST
	login();

	/*printf("\n\n��������˳�\n");
	system("pause");*/
#endif // TEST

	welcome();
	Sleep(3000);
	choices();
	printf("\n��ѡ��");
	scanf("%d", cho);
	switch (cho)
	{
	case 0:
		while (!streq(choice, "0"))
		{
			system("cls");
			printf("\n\t �Ϻ�С��");
			printf("\n\t 1��С���˰�ն��");
			printf("\n\t 2���ϴ������±�");
			printf("\n\t 3�����˹�������");
			printf("\n\t 4�����������㶹");
			printf("\n\t 5��������");
			printf("\n\t 6�������ɱ�");
			printf("\n\t 7������С��");
			printf("\n\t 8��������˿�����");
			printf("\n\t 9�������");
			printf("\n\t 10���ú���");
			printf("\n\t 0���˳�ϵͳ\n\n");
			printf("\n\t ��ѡ����Ҫ�鿴�Ĳ�Ʒ��");
			fseek(stdin, 0, SEEK_END);
			scanf("%s", choice);
			if (streq(choice, "1"))
				printf("\t\tС���˰�ն��\n\t\tС���˵İ�ն�����ڶ�����ο����Ϻ��Թ������������ζ��������ʮ����Ĵ�ҵ��ʷ��С�����Ѿ��ӵ���һ��СС�ļ���̯�ӷ�չ��Ϊ����ʳ���š���˵������ͬ�İ�ն����˵����ֶ��ܳԵ�������˵����Դ����ζ�������ڵĻ���Ҫ�������");
			else if (streq(choice, "2"))
				printf("\t\t�ϴ������±�\n\t\t���Ϻ���˵���±�����������ľ��������±��ˣ����ᵽ�����±����Ͳ��ò��ᡰ�ϴ󷿡��ˡ����Ǽ������±�һ��ʮ�������Ǹճ����ģ��Ŀ�Ǯһ�����������ڣ��������ֵģ������������۶�֭�����ֵ���Ƥ�о���࣬���ڸо��ʶ����塣");
			else if (streq(choice, "3"))
				printf("\t\t���˹�������\n\t\t\t���˹�����ڵ������棬һֱ���Ϻ�����Ϊ���Ϻ���һ�桱�������ѹǵ������������У�������ʧ���Σ���ͷ��������Ϊһ�壬���д����������ʣ������������Ϻ�������õİ���䷶��");
			else if (streq(choice, "4"))
				printf("\t\t���������㶹\n\t\t���������㶹���Ϻ�������ͳС�ԡ����������㶹Ƥ�����ɣ���˪���ȣ�ҧ����Ŵ���Ե����������硢�����̣����з�ζ");
			else if (streq(choice, "5"))
				printf("\t\t������\n\t\t���������Ϻ�����������ͳ��ɫ���֮һ����ɫ��ζС�ԡ����ɸ��Ӳ�����֡�ѡ�Ͻ�������Ⱥ���������У����������������ѧ�������ɿڣ�Ŵ����ճ��");
			else if (streq(choice, "6"))
				printf("\t\t�����ɱ�\n\t\t�����ɱ�Ϊ�Ϻ����ֶ������������Ĵ����㣬����������ɶ�������������Ƥ��η�����ÿ�㱡��ֽ�����ǧ�����");
			else if (streq(choice, "7"))
				printf("\t\t����С��\n\t\t����С���������Ǽ������������⽴����������ĩ����Ƥ�����Ρ����͡��Ǻ�ˮ���ƶ��ɣ�Ƥ���ò����͵ľ�����������ɵġ�");
			else if (streq(choice, "8"))
				printf("\t\t������˿�����\n\t\t������˿�������һ������⡢���ˡ�����������ɵ���ʳ��");
			else if (streq(choice, "9"))
				printf("\t\t�����\n\t\t�������һ�ֽ���ʡ�����д�ͳ����ʳ���ԣ�������Ϊ�������еĻʵۡ����۸񲻷ơ���ź�ͺ��ٹ�Ӧ����ʧ���ж���ʮ�꣬���������������ֺŲ������ٴ�����");
			else if (streq(choice, "10"))
				printf("\t\t�ú���\n\t\t�Ϻ��ú������Ϻ��˵Ľз���ͨ��һ��˵--���ǰ���������õģ�����һ���ĺ�״����ȴ��Ҫ�ö���𤣬������������ȴ�ǳ����Թ��򡱡���������ú��棬��������ˣ���˿��Ϻ�ʣ�Ѽ�Ƹ����������������Ȳ��ٸ��ϣ�ζ���������ʵ���üë��");
			else if (streq(choice, "0"))
				exitprogram();
			else
			{
				if (choicetry-- > 0)
					printf("�����д�����������\n");
				else
				{
					printf("������󳬳�3�Σ������˳���\n");
					exitprogram();
				}
			}
			system("pause");

		}break;
	case 1:
		book(dish); break;
	}
	return 0;
}
