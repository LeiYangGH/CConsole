#include "stdlib.h"  
#include "stdio.h"  

#define NULL 0  
#define LEN sizeof(struct student)  

struct student
{
	int num;              //学号   
	int score;          //分数，其他信息可以继续在下面增加字段  
	struct student *next;       //指向下一节点的指针  
};

int n;  //节点总数   
		/*
		==========================
		功能：创建n个节点的链表
		返回：指向链表表头的指针
		==========================
		*/
struct student *Create()
{
	int nn = 1;
	struct student *head;       //头节点  
	struct student *p1 = NULL;  //p1保存创建的新节点的地址  
	struct student *p2 = NULL;  //p2保存原链表最后一个节点的地址  

	n = 0;          //创建前链表的节点总数为0：空链表  
	p1 = (struct student *) malloc(LEN);   //开辟一个新节点  
	p2 = p1;            //如果节点开辟成功，则p2先把它的指针保存下来以备后用  

	if (p1 == NULL)        //节点开辟不成功  
	{
		printf("\nCann't create it, try it again in a moment!\n");
		return NULL;
	}
	else                //节点开辟成功  
	{
		head = NULL;        //开始head指向NULL  
		//printf("Please input %d node -- num,score: ", n + 1);
		//scanf("%d %f", &(p1->num), &(p1->score));    //录入数据 
		p1->num = 1;
		p1->score = 11;
	}
	//while (p1->num != 0)      //只要学号不为0，就继续录入下一个节点  
	while (nn < 5)      //只要学号不为0，就继续录入下一个节点  
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

		p1 = (struct student *) malloc(LEN);
		//printf("Please input %d node -- num,score: ", n + 1);
		//scanf("%d %f", &(p1->num), &(p1->score));

		++nn;
		p1->num = nn * 2;
		p1->score = nn * 22;
	}
	p2->next = NULL;     //此句就是根据单向链表的最后一个节点要指向NULL  

	free(p1);           //p1->num为0的时候跳出了while循环，并且释放p1  
	p1 = NULL;          //特别不要忘记把释放的变量清空置为NULL,否则就变成"野指针"，即地址不确定的指针  
	return head;        //返回创建链表的头指针   
}


/*
===========================
功能：输出节点
返回： void
===========================
*/
void Print(struct student *head)
{
	struct student *p;
	printf("\nNow , These %d records are:\n", n);
	p = head;
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
			//printf("%o   %d   %5.1f   %o\n", p, p->num, p->score, p->next);
			printf("%d   %d\n", p->num, p->score);
			p = p->next;     //移到下一个节点  
		} while (p != NULL);
	}
}

/*
==========================
功能：删除指定节点
(此例中是删除指定学号的节点)
返回：指向链表表头的指针
==========================
*/
struct student *Del(struct student *head, int num)
{
	struct student *p1;     //p1保存当前需要检查的节点的地址  
	struct student *p2;     //p2保存当前检查过的节点的地址  
	if (head == NULL)       //是空链表（结合图3理解）  
	{
		printf("\nList is null!\n");
		return head;
	}

	//定位要删除的节点  
	p1 = head;
	while (p1->num != num && p1->next != NULL)    //p1指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找  
	{
		p2 = p1;            //保存当前节点的地址  
		p1 = p1->next;       //后移一个节点  
	}

	if (p1->num == num)     //找到了。（结合图4、5理解）  
	{
		if (p1 == head)     //如果要删除的节点是第一个节点  
		{
			head = p1->next; //头指针指向第一个节点的后一个节点，也就是第二个节点。这样第一个节点就不在链表中，即删除  
		}
		else            //如果是其它节点，则让原来指向当前节点的指针，指向它的下一个节点，完成删除  
		{
			p2->next = p1->next;
		}

		free(p1);      //释放当前节点  
		p1 = NULL;
		printf("\ndelete %ld success!\n", num);
		n -= 1;         //节点总数减1个  
	}
	else                //没有找到  
	{
		printf("\n%ld not been found!\n", num);
	}

	return head;
}

//销毁链表  
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
功能：插入指定节点的后面
(此例中是指定学号的节点)
返回：指向链表表头的指针
==========================
*/
struct student *Insert(struct student *head, int num, struct student *node)
{
	struct student *p1;     //p1保存当前需要检查的节点的地址  
	if (head == NULL)       //（结合图示7理解）  
	{
		head = node;
		node->next = NULL;
		n += 1;
		return head;
	}

	p1 = head;
	while (p1->num != num && p1->next != NULL)  //p1指向的节点不是所要查找的，并且它不是最后一个节点，继续往下找  
	{
		p1 = p1->next;       //后移一个节点  
	}

	if (p1->num == num)        //找到了（结合图示8理解）  
	{
		node->next = p1->next;    //显然node的下一节点是原p1的next  
		p1->next = node;     //插入后，原p1的下一节点就是要插入的node  
		n += 1;         //节点总数增加1个  
	}
	else
	{
		printf("\n%ld not been found!\n", num);
	}
	return head;
}



/*
以上函数的测试程序：
提示：根据测试函数的不同注释相应的程序段，这也是一种测试方法。
*/
int main(void)
{
	struct student *head;
	struct student *stu;
	int thenumber;

	// 测试Create()、Print()   
	head = Create();
	Print(head);

	//测试Del()  
	/*printf("\nWhich one delete: ");
	scanf("%d", &thenumber);
	head = Del(head, thenumber);
	Print(head);*/

	//测试Insert()  
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


	//销毁链表  
	DestroyList(head);

	printf("\n");
	system("pause");
}