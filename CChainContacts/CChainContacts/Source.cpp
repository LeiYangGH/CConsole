#include "stdlib.h"  
#include "string.h"  
#include "stdio.h"  
#include "ctype.h"  

#define NULL 0  
#define LEN sizeof(person)  

typedef struct person
{
	char name[20];              //ѧ��   
	char tel[20];          //������������Ϣ���Լ��������������ֶ�  
	person *next;       //ָ����һ�ڵ��ָ��  
}person;

int n;  //�ڵ�����   
		/*
		==========================
		���ܣ�����n���ڵ������
		���أ�ָ�������ͷ��ָ��
		==========================
		*/
person *create()
{
	int nn = 1;
	//char name[] = "n";
	//char tel[] = "t";
	char name[20];
	char tel[20];
	person *head;       //ͷ�ڵ�  
	person *p1 = NULL;  //p1���洴�����½ڵ�ĵ�ַ  
	person *p2 = NULL;  //p2����ԭ�������һ���ڵ�ĵ�ַ  

	n = 0;          //����ǰ����Ľڵ�����Ϊ0��������  
	p1 = (person *)malloc(LEN);   //����һ���½ڵ�  
	p2 = p1;            //����ڵ㿪�ٳɹ�����p2�Ȱ�����ָ�뱣�������Ա�����  

	if (p1 == NULL)        //�ڵ㿪�ٲ��ɹ�  
	{
		printf("\nCann't create it, try it again in a moment!\n");
		return NULL;
	}
	else                //�ڵ㿪�ٳɹ�  
	{
		head = NULL;        //��ʼheadָ��NULL  
		strcpy(p1->name, "n1");
		strcpy(p1->tel, "111");
	}
	//while (p1->num != 0)      //ֻҪѧ�Ų�Ϊ0���ͼ���¼����һ���ڵ�  
	while (nn < 5)      //ֻҪѧ�Ų�Ϊ0���ͼ���¼����һ���ڵ�  
	{
		n += 1;         //�ڵ���������1��  
		if (n == 1)      //����ڵ�������1����headָ��մ����Ľڵ�p1  
		{
			head = p1;
			p2->next = NULL;  //��ʱ��p2����p1,Ҳ����p1->nextָ��NULL��  
		}
		else
		{
			p2->next = p1;   //ָ���ϴ�����ոտ��ٵ��½ڵ�  
		}

		p2 = p1;            //��p1�ĵ�ַ��p2������Ȼ��p1�����µĽڵ�  

		p1 = (person *)malloc(LEN);

		++nn;
		sprintf(name, "n%d", nn * 2);
		sprintf(tel, "t%d", nn * 22);
		strcpy(p1->name, name);
		strcpy(p1->tel, tel);
	}
	p2->next = NULL;     //�˾���Ǹ��ݵ�����������һ���ڵ�Ҫָ��NULL  

	free(p1);           //p1->numΪ0��ʱ��������whileѭ���������ͷ�p1  
	p1 = NULL;          //�ر�Ҫ���ǰ��ͷŵı��������ΪNULL,����ͱ��"Ұָ��"������ַ��ȷ����ָ��  
	return head;        //���ش��������ͷָ��   
}

void print(person *head)
{
	person *p;
	//printf("\nNow , These %d records are:\n", n);
	p = head;
	if (head != NULL)        //ֻҪ���ǿ�������������������нڵ�  
	{
		//printf("head is %o\n", head);    //���ͷָ��ָ��ĵ�ַ  
		do
		{
			/*
			�����Ӧ��ֵ����ǰ�ڵ��ַ�����ֶ�ֵ����ǰ�ڵ����һ�ڵ��ַ��
			����������ڶ������󿴵�һ�����������ڼ�����еĴ洢�ṹ��������
			��Ƶ�ͼʾ��һģһ���ġ�
			*/
			printf("%s %s\n", p->name, p->tel);
			p = p->next;     //�Ƶ���һ���ڵ�  
		} while (p != NULL);
	}
}

/*
==========================
���ܣ�ɾ��ָ���ڵ�
(��������ɾ��ָ��ѧ�ŵĽڵ�)
���أ�ָ�������ͷ��ָ��
==========================
*/
person *deleteperson(person *head, char *num)
{
	person *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ  
	person *p2;     //p2���浱ǰ�����Ľڵ�ĵ�ַ  
	if (head == NULL)       //�ǿ��������ͼ3��⣩  
	{
		printf("\nList is null!\n");
		return head;
	}

	//��λҪɾ���Ľڵ�  
	p1 = head;
	while (strcmp(p1->name, num) != 0 && p1->next != NULL)    //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬�ͼ���������  
	{
		p2 = p1;            //���浱ǰ�ڵ�ĵ�ַ  
		p1 = p1->next;       //����һ���ڵ�  
	}

	if (strcmp(p1->name, num) == 0)     //�ҵ��ˡ������ͼ4��5��⣩  
	{
		if (p1 == head)     //���Ҫɾ���Ľڵ��ǵ�һ���ڵ�  
		{
			head = p1->next; //ͷָ��ָ���һ���ڵ�ĺ�һ���ڵ㣬Ҳ���ǵڶ����ڵ㡣������һ���ڵ�Ͳ��������У���ɾ��  
		}
		else            //����������ڵ㣬����ԭ��ָ��ǰ�ڵ��ָ�룬ָ��������һ���ڵ㣬���ɾ��  
		{
			p2->next = p1->next;
		}

		free(p1);      //�ͷŵ�ǰ�ڵ�  
		p1 = NULL;
		//printf("\ndelete %ld success!\n", num);
		n -= 1;         //�ڵ�������1��  
	}
	else                //û���ҵ�  
	{
		printf("\n%ld not been found!\n", num);
	}

	return head;
}


int destroylist(person *head)
{
	person *p;
	if (head == NULL)
		return 0;
	while (head)
	{
		p = head->next;
		free(head);
		head = p;
	}
	return 1;
}

person *insertafter(person *head, char *name, person *node)
{
	person *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ  
	if (head == NULL)       //�����ͼʾ7��⣩  
	{
		head = node;
		node->next = NULL;
		n += 1;
		return head;
	}

	p1 = head;
	while (strcmp(p1->name, name) != 0 && p1->next != NULL)  //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬����������  
	{
		p1 = p1->next;       //����һ���ڵ�  
	}

	if (strcmp(p1->name, name) == 0)        //�ҵ��ˣ����ͼʾ8��⣩  
	{
		if (strcmp(p1->name, node->name) == 0)
		{
			strcpy(p1->tel, node->tel);
		}
		else
		{
			node->next = p1->next;    //��Ȼnode����һ�ڵ���ԭp1��next  
			p1->next = node;     //�����ԭp1����һ�ڵ����Ҫ�����node  
			n += 1;
		}
		//�ڵ���������1��  
	}
	else
	{
		printf("\n%ld not been found!\n", name);
	}
	return head;
}

int main(void)
{
	person *head;
	person *per;
	int thenumber;

	head = create();
	print(head);


	//����Insert()  
	per = (person *)malloc(LEN);
	strcpy(per->name, "n2");
	strcpy(per->tel, "t2");

	head = insertafter(head, "n1", per);
	print(head);

	per = (person *)malloc(LEN);
	strcpy(per->name, "n2");
	strcpy(per->tel, "t22222222");
	head = insertafter(head, "n2", per);
	print(head);

	deleteperson(head, "n2");
	print(head);

	destroylist(head);

	system("pause");
}