#include "stdlib.h"  
#include "stdio.h"  

#define NULL 0  
#define LEN sizeof(struct student)  

struct student
{
	int num;              //ѧ��   
	int score;          //������������Ϣ���Լ��������������ֶ�  
	struct student *next;       //ָ����һ�ڵ��ָ��  
};

int n;  //�ڵ�����   
		/*
		==========================
		���ܣ�����n���ڵ������
		���أ�ָ�������ͷ��ָ��
		==========================
		*/
struct student *Create()
{
	int nn = 1;
	struct student *head;       //ͷ�ڵ�  
	struct student *p1 = NULL;  //p1���洴�����½ڵ�ĵ�ַ  
	struct student *p2 = NULL;  //p2����ԭ�������һ���ڵ�ĵ�ַ  

	n = 0;          //����ǰ����Ľڵ�����Ϊ0��������  
	p1 = (struct student *) malloc(LEN);   //����һ���½ڵ�  
	p2 = p1;            //����ڵ㿪�ٳɹ�����p2�Ȱ�����ָ�뱣�������Ա�����  

	if (p1 == NULL)        //�ڵ㿪�ٲ��ɹ�  
	{
		printf("\nCann't create it, try it again in a moment!\n");
		return NULL;
	}
	else                //�ڵ㿪�ٳɹ�  
	{
		head = NULL;        //��ʼheadָ��NULL  
		//printf("Please input %d node -- num,score: ", n + 1);
		//scanf("%d %f", &(p1->num), &(p1->score));    //¼������ 
		p1->num = 1;
		p1->score = 11;
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

		p1 = (struct student *) malloc(LEN);
		//printf("Please input %d node -- num,score: ", n + 1);
		//scanf("%d %f", &(p1->num), &(p1->score));

		++nn;
		p1->num = nn * 2;
		p1->score = nn * 22;
	}
	p2->next = NULL;     //�˾���Ǹ��ݵ�����������һ���ڵ�Ҫָ��NULL  

	free(p1);           //p1->numΪ0��ʱ��������whileѭ���������ͷ�p1  
	p1 = NULL;          //�ر�Ҫ���ǰ��ͷŵı��������ΪNULL,����ͱ��"Ұָ��"������ַ��ȷ����ָ��  
	return head;        //���ش��������ͷָ��   
}


/*
===========================
���ܣ�����ڵ�
���أ� void
===========================
*/
void Print(struct student *head)
{
	struct student *p;
	printf("\nNow , These %d records are:\n", n);
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
			//printf("%o   %d   %5.1f   %o\n", p, p->num, p->score, p->next);
			printf("%d   %d\n", p->num, p->score);
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
struct student *Del(struct student *head, int num)
{
	struct student *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ  
	struct student *p2;     //p2���浱ǰ�����Ľڵ�ĵ�ַ  
	if (head == NULL)       //�ǿ��������ͼ3��⣩  
	{
		printf("\nList is null!\n");
		return head;
	}

	//��λҪɾ���Ľڵ�  
	p1 = head;
	while (p1->num != num && p1->next != NULL)    //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬�ͼ���������  
	{
		p2 = p1;            //���浱ǰ�ڵ�ĵ�ַ  
		p1 = p1->next;       //����һ���ڵ�  
	}

	if (p1->num == num)     //�ҵ��ˡ������ͼ4��5��⣩  
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
		printf("\ndelete %ld success!\n", num);
		n -= 1;         //�ڵ�������1��  
	}
	else                //û���ҵ�  
	{
		printf("\n%ld not been found!\n", num);
	}

	return head;
}

//��������  
int DestroyList(struct student *head)
{
	struct student *p;
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

/*
==========================
���ܣ�����ָ���ڵ�ĺ���
(��������ָ��ѧ�ŵĽڵ�)
���أ�ָ�������ͷ��ָ��
==========================
*/
struct student *Insert(struct student *head, int num, struct student *node)
{
	struct student *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ  
	if (head == NULL)       //�����ͼʾ7��⣩  
	{
		head = node;
		node->next = NULL;
		n += 1;
		return head;
	}

	p1 = head;
	while (p1->num != num && p1->next != NULL)  //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬����������  
	{
		p1 = p1->next;       //����һ���ڵ�  
	}

	if (p1->num == num)        //�ҵ��ˣ����ͼʾ8��⣩  
	{
		node->next = p1->next;    //��Ȼnode����һ�ڵ���ԭp1��next  
		p1->next = node;     //�����ԭp1����һ�ڵ����Ҫ�����node  
		n += 1;         //�ڵ���������1��  
	}
	else
	{
		printf("\n%ld not been found!\n", num);
	}
	return head;
}



/*
���Ϻ����Ĳ��Գ���
��ʾ�����ݲ��Ժ����Ĳ�ͬע����Ӧ�ĳ���Σ���Ҳ��һ�ֲ��Է�����
*/
int main(void)
{
	struct student *head;
	struct student *stu;
	int thenumber;

	// ����Create()��Print()   
	head = Create();
	Print(head);

	//����Del()  
	/*printf("\nWhich one delete: ");
	scanf("%d", &thenumber);
	head = Del(head, thenumber);
	Print(head);*/

	//����Insert()  
	stu = (struct student *)malloc(LEN);
	//printf("\nPlease input insert node -- num,score: ");
	//scanf("%d%d", &stu->num, &stu->score);
	stu->num = 3;
	stu->score = 33;
	//printf("\nInsert behind num: ");
	//scanf("%d", &thenumber);
	thenumber = 1;
	head = Insert(head, thenumber, stu);
	Print(head);

	Del(head, 3);
	Print(head);


	//��������  
	DestroyList(head);

	printf("\n");
	system("pause");
}