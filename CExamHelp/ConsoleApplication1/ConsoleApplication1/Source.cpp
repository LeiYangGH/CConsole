#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void delchar(char *str, char c)
{
	char  *p, *q;
	for (p = str, q = str; *p != '\0'; p++)
		if (*p != c)*q++ = *p;
	*q = *p;
}
int main()
{
	char str[100], c;
	puts("������str���س�����:");
	//��Щ��������֧��gets��
	//��scanf�ֲ���������ո���ַ���
	fgets(str, 100, stdin);
	printf("ɾ��ǰ���ַ�����\n%s\n", str);
	//�������������Ӱ���������
	fseek(stdin, 0, SEEK_END);
	printf("����Ҫɾ�����ַ����س�����:");
	c = getchar();
	delchar(str, c);
	printf("ɾ������ַ�����\n%s\n", str);
	system("pause");
	return 0;
}

