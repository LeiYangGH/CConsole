#include <stdio.h>
#include<stdlib.h>
#include <windows.h>
struct denglu//����һ��denglu�ṹ��
{
	char name[20];//����û���
	int key[20];//��Ӧ������
}str[20];//����ṹ�����
void main_menu()
{
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
void lesser_menu()
{
	printf("\t\t\t\t�Ϻ�С��\n");
	printf("\t\t\t\t1-----С���˰�ն��\n");
	printf("\t\t\t\t2-----�ϴ������±�\n");
	printf("\t\t\t\t3-----���˹�������\n");
	printf("\t\t\t\t4-----���������㶹\n");
	printf("\t\t\t\t5-----������\n");
	printf("\t\t\t\t6-----�����ɱ�\n");
	printf("\t\t\t\t7-----����С��\n");
	printf("\t\t\t\t8-----������˿�����\n");
	printf("\t\t\t\t9-----�����\n");
	printf("\t\t\t\t10----�ú���\n");
}
int uname(char names)
{
	int i = 0;
	FILE *fp;
	fp = fopen("uname.txt", "r");
	if (fp == NULL) //���ļ�����
	{
		printf("����"); exit(0);
	}
	while (fscanf(fp, "%s", &str[i].name[i]) != EOF) //��ȡ�ַ������飬ֱ���ļ���β(����EOF)
		i++;
	fclose(fp);//�ر��ļ�
	for (i = 0; i<20; i++)
	{
		if (names == str[i].name[i])
			break;
	}
	if (i == 19)
		if (str[19].name[19] != names)
			i++;
	return i;
}
int ukey(int keys, int j)
{
	int i = 0, flags = 0;
	FILE *fp;
	fp = fopen("ukey.txt", "r");
	if (fp == NULL) //���ļ�����
	{
		printf("����"); exit(0);
	}
	while (fscanf(fp, "%d", &str[i].key[i]) != EOF) //��ȡ���ݵ����飬ֱ���ļ���β(����EOF)
		i++;
	for (i = 0; i<20; i++)
		if (str[j].key[j] == keys)
		{
			flags = 1;
			break;
		}
	return flags;
}
int main()
{
	char name;
	int n = 0, key, timer = 3, count = 3, flag, p, j;
	char op;
	main_menu();
	while (timer != 0) { Sleep(1000); timer--; }
	system("cls");
	printf("\t\t�������û�����");
	scanf("%s", &name);
	printf("\n");
	n = uname(name);
	if (n<20)
	{
		for (j = 0; j<3; j++)
		{
			printf("\t\t���������룺");
			scanf("%d", &key);
			flag = ukey(key, n);
			if (flag)
			{
				system("cls");
				lesser_menu();
				while (count != 0)
				{
					printf("���������Ȥ�ģ�");
					scanf("%d", p);
					if (p>0 && p<11)
						switch (p)
						{
						case 1:printf("\t\tС���˰�ն��\n\t\tС���˵İ�ն�����ڶ�����ο����Ϻ��Թ������������ζ��������ʮ����Ĵ�ҵ��ʷ��С�����Ѿ��ӵ���һ��СС�ļ���̯�ӷ�չ��Ϊ����ʳ���š���˵������ͬ�İ�ն����˵����ֶ��ܳԵ�������˵����Դ����ζ�������ڵĻ���Ҫ�������"); break;
						case 2:printf("\t\t�ϴ������±�\n\t\t���Ϻ���˵���±�����������ľ��������±��ˣ����ᵽ�����±����Ͳ��ò��ᡰ�ϴ󷿡��ˡ����Ǽ������±�һ��ʮ�������Ǹճ����ģ��Ŀ�Ǯһ�����������ڣ��������ֵģ������������۶�֭�����ֵ���Ƥ�о���࣬���ڸо��ʶ����塣"); break;
						case 3:printf("\t\t���˹�������\n\t\t\t���˹�����ڵ������棬һֱ���Ϻ�����Ϊ���Ϻ���һ�桱�������ѹǵ������������У�������ʧ���Σ���ͷ��������Ϊһ�壬���д����������ʣ������������Ϻ�������õİ���䷶��"); break;
						case 4:printf("\t\t���������㶹\n\t\t���������㶹���Ϻ�������ͳС�ԡ����������㶹Ƥ�����ɣ���˪���ȣ�ҧ����Ŵ���Ե����������硢�����̣����з�ζ"); break;
						case 5:printf("\t\t������\n\t\t���������Ϻ�����������ͳ��ɫ���֮һ����ɫ��ζС�ԡ����ɸ��Ӳ�����֡�ѡ�Ͻ�������Ⱥ���������У����������������ѧ�������ɿڣ�Ŵ����ճ��"); break;
						case 6:printf("\t\t�����ɱ�\n\t\t�����ɱ�Ϊ�Ϻ����ֶ������������Ĵ����㣬����������ɶ�������������Ƥ��η�����ÿ�㱡��ֽ�����ǧ�����"); break;
						case 7:printf("\t\t����С��\n\t\t����С���������Ǽ������������⽴����������ĩ����Ƥ�����Ρ����͡��Ǻ�ˮ���ƶ��ɣ�Ƥ���ò����͵ľ�����������ɵġ�"); break;
						case 8:printf("\t\t������˿�����\n\t\t������˿�������һ������⡢���ˡ�����������ɵ���ʳ��"); break;
						case 9:printf("\t\t�����\n\t\t�������һ�ֽ���ʡ�����д�ͳ����ʳ���ԣ�������Ϊ�������еĻʵۡ����۸񲻷ơ���ź�ͺ��ٹ�Ӧ����ʧ���ж���ʮ�꣬���������������ֺŲ������ٴ�����"); break;
						case 10:printf("\t\t�ú���\n\t\t�Ϻ��ú������Ϻ��˵Ľз���ͨ��һ��˵--���ǰ���������õģ�����һ���ĺ�״����ȴ��Ҫ�ö���𤣬������������ȴ�ǳ����Թ��򡱡���������ú��棬��������ˣ���˿��Ϻ�ʣ�Ѽ�Ƹ����������������Ȳ��ٸ��ϣ�ζ���������ʵ���üë��"); break;
						default: count--;
						}
					else
					{
						system("cls");
						main_menu();
					}
				}
			}
			else
			{
				system("cls");
				main_menu();
			}
		}
	}
	return 0;
}
