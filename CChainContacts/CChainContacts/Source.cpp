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

//链表操作参考：
//http://blog.csdn.net/hackbuteer1/article/details/6591486/#
int n;  //节点总数
		/*
		==========================
		功能：创建n个节点的链表
		返回：指向链表表头的指针
		==========================
		*/
person *create()
{
#if TEST
	int nn = 1;
	char name[21] = "n";
	char tel[21] = "t";
#endif
	person *head;       //头节点
	person *p1 = NULL;  //p1保存创建的新节点的地址
	person *p2 = NULL;  //p2保存原链表最后一个节点的地址

	n = 0;          //创建前链表的节点总数为0：空链表
	p1 = (person *)malloc(LEN);   //开辟一个新节点
	p2 = p1;            //如果节点开辟成功，则p2先把它的指针保存下来以备后用

	if (p1 == NULL)        //节点开辟不成功
	{
		printf("\nCann't create it, try it again in a moment!\n");
		return NULL;
	}
	else                //节点开辟成功
	{
		head = NULL;        //开始head指向NULL
		strcpy(p1->name, "n1");
		strcpy(p1->tel, "111");
	}
#if TEST
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

		p1 = (person *)malloc(LEN);

		++nn;
		sprintf(name, "n%d", nn * 2);
		sprintf(tel, "t%d", nn * 22);
		strcpy(p1->name, name);
		strcpy(p1->tel, tel);
	}
#endif
	p2->next = NULL;     //此句就是根据单向链表的最后一个节点要指向NULL

	free(p1);           //p1->num为0的时候跳出了while循环，并且释放p1
	p1 = NULL;          //特别不要忘记把释放的变量清空置为NULL,否则就变成"野指针"，即地址不确定的指针
	return head;        //返回创建链表的头指针
}

void print(person *head)
{
	person *p;
	//printf("\nNow , These %d records are:\n", n);
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
			printf("%s %s\n", p->name, p->tel);
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
person *deleteperson(person *head, char *name)
{
	person *p1;     //p1保存当前需要检查的节点的地址
	person *p2;     //p2保存当前检查过的节点的地址
	if (head == NULL)       //是空链表（结合图3理解）
	{
		printf("\nList is null!\n");
		return head;
	}

	//定位要删除的节点
	p1 = head;
	while (strcmp(p1->name, name) != 0 && p1->next != NULL)    //p1指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找
	{
		p2 = p1;            //保存当前节点的地址
		p1 = p1->next;       //后移一个节点
	}

	if (strcmp(p1->name, name) == 0)     //找到了。（结合图4、5理解）
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
		//printf("\ndelete %ld success!\n", num);
		n -= 1;         //节点总数减1个
	}
	//else                //没有找到
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
	person *p1;     //p1保存当前需要检查的节点的地址
	if (head == NULL)       //（结合图示7理解）
	{
		head = node;
		node->next = NULL;
		n += 1;
		return head;
	}

	p1 = head;
	while (strcmp(p1->name, name) != 0 && p1->next != NULL)  //p1指向的节点不是所要查找的，并且它不是最后一个节点，继续往下找
	{
		p1 = p1->next;       //后移一个节点
	}

	if (strcmp(p1->name, name) == 0)        //找到了（结合图示8理解）
	{
		if (strcmp(p1->name, node->name) == 0)
		{
			strcpy(p1->tel, node->tel);
		}
		else
		{
			node->next = p1->next;    //显然node的下一节点是原p1的next
			p1->next = node;     //插入后，原p1的下一节点就是要插入的node
			n += 1;
		}
		//节点总数增加1个
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
