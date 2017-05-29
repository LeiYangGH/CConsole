#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct student
{
	char no[20];
	char name[20];
	char score[3];
	student *next;
}student;

int n;

void fillstudent(student *n)
{
	printf("请依次输入学生的学号，姓名，3门课程的成绩(整数)，空格隔开，回车结束\n");
	scanf("%s%s%d%d%d", n->no, n->name, &n->score[0], &n->score[1], &n->score[2]);
	fseek(stdin, 0, SEEK_END);
	printf("\n%s的信息添加成功!\n", n->name);
}

student *create()
{
	int max = 3;
	student *head;       //头节点
	student *p1 = NULL;  //p1保存创建的新节点的地址
	student *p2 = NULL;  //p2保存原链表最后一个节点的地址

	n = 0;          //创建前链表的节点总数为0：空链表
	p1 = (student *)malloc(sizeof(student));   //开辟一个新节点
	p2 = p1;            //如果节点开辟成功，则p2先把它的指针保存下来以备后用

	if (p1 == NULL)        //节点开辟不成功
	{
		printf("\nCann't create it, try it again in a moment!\n");
		return NULL;
	}
	else                //节点开辟成功
	{
		head = NULL;        //开始head指向NULL
		//strcpy(p1->name, "n1");
		//strcpy(p1->tel, "111");
		fillstudent(p1);
	}
#if 1
	while (n < max)      //只要学号不为0，就继续录入下一个节点
	{
		n += 1;         //节点总数增加1个
		if (n == 1)      //如果节点总数是1，则head指向刚创建的节点p1
		{
			head = p1;
			p2->next = NULL;  //此时的p2就是p1,也就是p1->next指向NULL。
		}
		else
		{
			p2->next = p1;   //指向上次下面刚刚开辟的新节点
		}

		p2 = p1;            //把p1的地址给p2保留，然后p1产生新的节点

		p1 = (student *)malloc(sizeof(student));

		if (n < max)
			fillstudent(p1);
		//n++;
		/*++nn;
		sprintf(name, "n%d", nn * 2);
		sprintf(tel, "t%d", nn * 22);
		strcpy(p1->name, name);
		strcpy(p1->tel, tel);*/
	}
#endif
	p2->next = NULL;     //此句就是根据单向链表的最后一个节点要指向NULL

	free(p1);           //p1->num为0的时候跳出了while循环，并且释放p1
	p1 = NULL;          //特别不要忘记把释放的变量清空置为NULL,否则就变成"野指针"，即地址不确定的指针
	return head;        //返回创建链表的头指针
}


void print(student *head)
{
	student *p;
	//printf("\nNow , These %d records are:\n", n);
	p = head;
	//p = head->next;
	if (head != NULL)        //只要不是空链表，就输出链表中所有节点
	{
		//printf("head is %o\n", head);    //输出头指针指向的地址
		do
		{
			/*
			输出相应的值：当前节点地址、各字段值、当前节点的下一节点地址。
			这样输出便于读者形象看到一个单向链表在计算机中的存储结构，和我们
			设计的图示是一模一样的。
			*/
			//printf("%s %s\n", p->name, p->tel);
			student stu = *p;

			printf("%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.score[0], stu.score[1], stu.score[2]);

			p = p->next;     //移到下一个节点
		} while (p != NULL);
	}
}

//显示一个通讯信息
void displaystudent(student stu)
{
	printf("%s\t%s\t%d\t%d\t%d\n", stu.no, stu.name, stu.score[0], stu.score[1], stu.score[2]);
}



//新增通讯信息






int main()
{
	student *head = create();


#if 1

	print(head);
#endif


	fseek(stdin, 0, SEEK_END);
	system("pause");
	return 0;
}