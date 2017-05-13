#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define LEN sizeof(person)
#define TEST 1

typedef struct person
{
	char name[21];
	char tel[21];
	struct person *next;
}person;
person *head;

//��������ο���
//http://blog.csdn.net/hackbuteer1/article/details/6591486/#
int n;  //�ڵ�����
		/*
		==========================
		���ܣ�����n���ڵ������
		���أ�ָ�������ͷ��ָ��
		==========================
		*/
person *create()
{
#if TEST
	int nn = 1;
	char name[21] = "n";
	char tel[21] = "t";
#endif
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
#if TEST
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
#endif
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
person *deleteperson(person *head, char *name)
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
	while (strcmp(p1->name, name) != 0 && p1->next != NULL)    //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬�ͼ���������
	{
		p2 = p1;            //���浱ǰ�ڵ�ĵ�ַ
		p1 = p1->next;       //����һ���ڵ�
	}

	if (strcmp(p1->name, name) == 0)     //�ҵ��ˡ������ͼ4��5��⣩
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
	//else                //û���ҵ�
	//{
	//	printf("\n%s not been found!\n", name);
	//}

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
		//printf("\n%ld not been found!\n", name);
		node->next = head;
		head = node;
	}
	return head;
}

void executeinsert(char *name, char *tel, char *nameafter)
{
	//printf("\nexecuteinsert %s %s %s\n", name, tel, nameafter);

	//person *head;
	person *per;
	per = (person *)malloc(LEN);
	strcpy(per->name, name);
	strcpy(per->tel, tel);
	head = insertafter(head, nameafter, per);
}

void executeprint()
{
	//printf("\nexecuteprint\n");
	print(head);

}

void executedelete(char *name)
{
	//printf("\nexecutedelete %s\n", name);
	head = deleteperson(head, name);

}

void splitcmdintoparts(char *cmd, char parts[6][21])
{
	char *part;
	int index = 0;
	part = strtok(cmd, " \n");
	while (part != NULL)
	{
		strcpy(parts[index++], part);
		part = strtok(NULL, " \n");
	}
}

int executecommand(char *cmd)
{
	char parts[6][21] = { "","","","","" };
	splitcmdintoparts(cmd, parts);
	if (strcmp(cmd, "End") == 0)
		return 0;
	if (strcmp(parts[0], "Insert") == 0)
		executeinsert(parts[1], parts[2], parts[4]);
	else if (strcmp(parts[0], "Print") == 0)
		executeprint();
	else if (strcmp(parts[0], "Delete") == 0)
		executedelete(parts[1]);
	else
		printf("invalid command");
	return 1;
}

int main(void)
{
	char cmd[80] = "Print";
#if TEST
	person *per;
#endif
	head = create();
	//print(head);
#if TEST
	printf("\ninsert\n");
	per = (person *)malloc(LEN);
	strcpy(per->name, "n2");
	strcpy(per->tel, "t2");
	head = insertafter(head, "n1", per);
	print(head);

	printf("\ninsertnobody\n");
	per = (person *)malloc(LEN);
	strcpy(per->name, "n0");
	strcpy(per->tel, "t0");
	head = insertafter(head, "nobody", per);
	print(head);

	printf("\nreplace\n");
	per = (person *)malloc(LEN);
	strcpy(per->name, "n2");
	strcpy(per->tel, "t22222222");
	head = insertafter(head, "n2", per);
	print(head);

	printf("\ndelete\n");
	deleteperson(head, "n2");
	print(head);
#else
	while (executecommand(cmd))
	{
		//printf("\?\n");
		fgets(cmd, 80, stdin);
}
#endif
	destroylist(head);
	system("pause");
	return 0;
}
