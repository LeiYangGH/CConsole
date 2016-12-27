#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define DEV 1
typedef struct flightnode
{
	char flight_num[10];//�����
	char start_time[15];//���ʱ��
	char end_time[15];//�ִ�ʱ��
	char start_place[20];//��ɳ���
	char end_place[20];//�������
	int left;//������
	float price;//Ʊ��
	int ifull;//�����Ƿ�����
	struct flightnode *next;//ָ����һ�ڵ�
}flightnode;

typedef struct passengernode
{
	char name[20];//����
	char ID_num[20];//֤����
	char flight_num[10];//�����
	int order_num;//������
	int ticket_num;//��Ʊ����
	struct passengernode *next;//ָ����һ�ڵ�
}passengernode;

typedef struct passengerList
{
	passengernode *head;
	passengernode *rear;
}passengerList;

typedef struct waitnode
{
	char name[20];//����
	char phone[20];//�ֻ���
	char flight_num[10];//�����
	int ticket_num;//��Ʊ����
	int order_num;//ԤԼ�ŶӺ�
	struct waitnode *next;//ָ����һ�ڵ�

}waitnode;

typedef struct waitList
{
	waitnode *head;
	waitnode *rear;
}waitList;



//������hΪͷ���Ŀ�����¼�뺽����Ϣ�����Ӻ���󽫺�������������
void init_flight(flightnode *&h)
{
	h = (flightnode *)malloc(sizeof(flightnode));//����ͷ���ռ�
	if (h == NULL)
		exit(0);
	h->next = NULL;//��ͷ���h��ָ������Ϊ��
}
//����һ������ͷβָ��Ŀ������洢���пͻ���Ϣ�Ľڵ�
void init_passengerList(passengerList *&pList)
{
	pList = (passengerList *)malloc(sizeof(passengerList));
	pList->head = (passengernode *)malloc(sizeof(passengernode));//����ͷ���
	pList->rear = pList->head;
	pList->rear->order_num = 0;//�����Ŵ�0��ʼ����
	pList->head->next = NULL;
}
//����һ������ͷβָ��Ŀնӣ��洢����ԤԼ�ͻ���Ϣ�Ľڵ�
void init_waitList(waitList *&wList)
{
	wList = (waitList *)malloc(sizeof(waitList));
	wList->head = (waitnode *)malloc(sizeof(waitnode));//����ͷ���
	wList->rear = wList->head;
	wList->rear->order_num = 0;//ԤԼ�ŶӺŴ�0��ʼ����
	wList->head->next = NULL;
}

//���溽����Ϣ��ָ���������ļ���
void save_flight(flightnode *h)
{
	FILE *fp = fopen("flightList.dat", "wb");//��ֻд('wb')�ķ�ʽ����Ϊ'flightList.dat'���ļ�
	if (fp == NULL)
		return;
	flightnode *temp = h->next;
	while (temp != NULL)
	{
		fwrite(temp, sizeof(flightnode), 1, fp);//������д��temp��temp��ָ�룩��ַ��l��flightnode���͵�����
		temp = temp->next;
	}
	fclose(fp);//�ر�fpָ����ļ�
}
//�Ӵ洢������Ϣ���ļ����뺽����Ϣ������������
void load_flight(flightnode *&h)
{
	flightnode *pt = h;
	FILE *fp = fopen("flight.dat", "rb");
	if (fp == NULL)
		return;
	flightnode *q;
	int n;
	while (!feof(fp))//�ļ�ָ��û�е����ļ�ĩβ�����һ���ַ�����һ��λ�ã�����ʧ��ʱ��λ�ã�
	{
		q = (flightnode *)malloc(sizeof(flightnode));
		n = fread(q, sizeof(flightnode), 1, fp);//��д������ݶ�ȡ����
		if (n != 1)
			break;
		pt->next = q;
		pt = q;
	}
	pt->next = NULL;
	fclose(fp);
}

//�����Ѷ�Ʊ�ͻ���Ϣ��ָ�������ļ���
void save_passenger(passengerList *PList)
{
	FILE *fp = fopen("passenger.dat", "wb");
	if (fp == NULL)
		return;
	passengernode *temp = PList->head->next;
	while (temp != NULL)
	{
		fwrite(temp, sizeof(passengernode), 1, fp);//������д��temp��temp��ָ�룩��ַ��l��passengernode���͵�����
		temp = temp->next;
	}
	fclose(fp);//�ر�fpָ����ļ�
}
//�Ӵ洢�ͻ���Ϣ���ļ�����ͻ���Ϣ���ͻ�������
void load_passenger(passengerList *&PList)
{
	FILE *fp = fopen("passenger.dat", "rb");
	if (fp == NULL)
		return;
	passengernode *q;
	int n;
	while (!feof(fp))//�ļ�ָ��û�е����ļ�ĩβ�����һ���ַ�����һ��λ�ã�����ʧ��ʱ��λ�ã�
	{
		q = (passengernode *)malloc(sizeof(passengernode));
		n = fread(q, sizeof(passengernode), 1, fp);//��д������ݶ�ȡ����
		if (n != 1)
			break;
		PList->rear->next = q;
		PList->rear = q;
	}
	PList->rear->next = NULL;
	fclose(fp);
}

//����ԤԼ�ͻ���Ϣ��ָ�������ļ���
void save_wait(waitList *WList)
{
	FILE *fp = fopen("waitpassenger.dat", "wb");
	if (fp == NULL)
		return;
	waitnode *temp = WList->head->next;
	while (temp != NULL)
	{
		fwrite(temp, sizeof(waitnode), 1, fp);//������д��temp��temp��ָ�룩��ַ��l��waitnode���͵�����
		temp = temp->next;
	}
	fclose(fp);//�ر�fpָ����ļ�
}
//�Ӵ洢ԤԼ�ͻ���Ϣ���ļ�����ԤԼ�ͻ���Ϣ��ԤԼ�ͻ�������
void load_wait(waitList *&WList)
{
	FILE *fp = fopen("waitpassenger.dat", "rb");
	if (fp == NULL)
		return;
	waitnode *w;
	int n;
	while (!feof(fp))//�ļ�ָ��û�е����ļ�ĩβ�����һ���ַ�����һ��λ�ã�����ʧ��ʱ��λ�ã�
	{
		w = (waitnode *)malloc(sizeof(waitnode));
		n = fread(w, sizeof(waitnode), 1, fp);//��д������ݶ�ȡ����
		if (n != 1)
			break;
		WList->rear->next = w;
		WList->rear = w;
	}
	WList->rear->next = NULL;
	fclose(fp);
}

//¼�뺽������������µĺ���󣬽��µĺ�������뵽����������
void insert_flight(flightnode *&h, char *flight_num, char *start_place, char *end_place, char *start_time, char *end_time, int left, float price, int ifull)
{
	flightnode *q;//����qΪ�����ӵĺ���ڵ��ָ����β�
	flightnode *p = h;
	q = (flightnode *)malloc(sizeof(flightnode));//Ϊ�ڵ�q����ռ�
	strcpy(q->flight_num, flight_num);
	strcpy(q->start_place, start_place);
	strcpy(q->end_place, end_place);
	strcpy(q->start_time, start_time);
	strcpy(q->end_time, end_time);
	q->left = left;
	q->price = price;
	q->ifull = ifull;
	//��strcpy�����������Ӻ���ĸ�����Ϣ���Ƶ�q�ڵ���
	q->next = p->next;//��q�ڵ��ָ������Ϊ��
	p->next = q;
	p = p->next;//��ָ�����
}

//¼�뺽����Ϣ�����insert_flight�������Ӻ���
void add_flight(flightnode *&h)
{
	flightnode *p = h;
	char flight_num[10], start_time[10], end_time[10], start_place[10], end_place[10];
	int left, ifull, mark = 1;
	float price;
	for (; p->next != NULL; p = p->next)
	{
	}//�ƶ�ָ�룬�ҵ����һ���ڵ�
	while (mark == 1)
	{
#if DEV
		strcpy(flight_num, "a");
		insert_flight(h, flight_num, "f", "t", "y", "t", 0, 1, 1);
#else
		printf("\t\t��������Ҫ���ӵĺ���ţ�");
		scanf("%s", flight_num);
		printf("\t\t����������أ�");
		scanf("%s", start_place);
		printf("\t\t������Ŀ�ĵأ�");
		scanf("%s", end_place);
		printf("\t\t���������ʱ�䣺");
		scanf("%s", start_time);
		printf("\t\t������ִ�ʱ�䣺");
		scanf("%s", end_time);
		printf("\t\t������Ʊ�ۣ�");
		scanf("%f", &price);
		printf("\t\t������ʣ����λ����");
		scanf("%d", &left);
		printf("\t\t�������Ƿ����֣�0��ʾû�����֣�1��ʾ�����֣���");
		scanf("%d", &ifull);
		insert_flight(h, flight_num, start_place, end_place, start_time, end_time, left, price, ifull);
#endif
		printf("\t\t���Ӻ����%s�ɹ���\n", flight_num);
		printf("\t\t�Ƿ����¼�뺽����Ϣ��1��ʾ����¼�룬0��ʾֹͣ¼�룩\n");
		printf("\t\t�����룺");
		scanf("%d", &mark);
	}
}

//������ɵִ���в�ѯ������Ϣ
int place_check(flightnode *h, char *start_place, char *end_place)
{
	flightnode *p = h;
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "�����", "��ɳ���", "�ִ����", "���ʱ��", "�ִ�ʱ��", "�۸�", "�Ƿ�����", "������");
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->start_place, start_place) == 0 && strcmp(p->end_place, end_place) == 0)
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
			mark = 1;
		}
	}
	if (mark == 0)
	{
		printf("\t\t��Ǹ��û�д�%s��%s�ĺ�����Ϣ��\n", start_place, end_place);
		return 0;
	}
	return 1;
}

//�ڹ˿Ͷ�Ʊ�󣬽��ù˿ͽ����뵽�˿��������޸���Ӧ������Ϣ
void insert_passengerList(flightnode *&h, passengerList *&PList, char *name, char *ID_num, char *flight_num, int ticket_num)
{
	flightnode *p = h->next;
	for (; p != NULL; p = p->next)
		if (strcmp(p->flight_num, flight_num) == 0)
		{
			p->left = p->left - ticket_num;
			if (p->left == 0)
				p->ifull = 1;
		}
	passengernode *q = (passengernode *)malloc(sizeof(passengernode));//�½���㣬����µĿͻ�������Ϣ
	strcpy(q->name, name);
	strcpy(q->ID_num, ID_num);
	strcpy(q->flight_num, flight_num);
	q->ticket_num = ticket_num;
	q->next = NULL;
	//���¶������ӵ�������
	PList->rear->next = q;
	q->order_num = PList->rear->order_num + 1;//���ɶ�����
	PList->rear = q;
}

//�ڿͻ�ԤԼƱ�󣬽���ԤԼ�ͻ������뵽ԤԼ�ͻ�����
void insert_waitList(waitList *&WList, char *name, char *phone, char *flight_num, int ticket_num, int order_num)
{
	waitnode *p = (waitnode *)malloc(sizeof(waitnode));
	strcpy(p->name, name);
	strcpy(p->phone, phone);
	strcpy(p->flight_num, flight_num);
	p->ticket_num = ticket_num;
	p->next = NULL;
	if (WList->rear == NULL)
	{
		WList->head = WList->rear = p;
	}
	else
	{
		WList->rear->next = p;
		p->order_num = WList->rear->order_num + 1;//����ԤԼ�ŶӺ�
		WList->rear = p;
	}
}
//��ɿͻ���Ʊ�����ͻ�������ͻ��������޸���Ӧ�ĺ�����Ϣ
int book(flightnode *&h, passengerList *&PList, waitList *WList)
{
	char name[20];
	char ID_num[20];
	char flight_num[10];
	char start_place[20];
	char end_place[20];
	char phone[20];
	int ticket_num;
	int order_num;
	int k;
	flightnode *p = h->next;
#if DEV
	strcpy(start_place, "f");
	strcpy(end_place, "t");
#else
	printf("\t\t��������Ϣ��\n");
	printf("\t\t��������ɳ��У�");
	scanf("%s", start_place);
	printf("\t\t������ִ���У�");
	scanf("%s", end_place);
#endif


	if (place_check(h, start_place, end_place) == 1)
	{
		printf("\t\t����ţ�");
		scanf("%s", flight_num);
		while (flight_num == NULL)
		{
#if DEV
			strcpy(flight_num, "a");
#else
			printf("����Ų���Ϊ�գ�\n");
			printf("\t\t����ţ�");
			scanf("%s", flight_num);
#endif

		}
		while (p != NULL)
		{
			if (strcmp(p->flight_num, flight_num) == 0)
			{

#if DEV
				strcpy(name, "ly");
				strcpy(ID_num, "510");
				ticket_num = 1;
#else
				printf("\t\t������");
				scanf("%s", name);
				printf("\t\t֤�����룺");
				scanf("%s", ID_num);
				printf("\t\t��Ʊ������");
				scanf("%d", &ticket_num);
#endif

				while (name == NULL)
				{
					printf("�ͻ���������Ϊ�գ�\n");
					printf("\t\t������");
					scanf("%s", name);
				}
				while (ID_num == NULL)
				{
					printf("�ͻ�֤�����벻��Ϊ�գ�\n");
					printf("\t\t֤�����룺");
					scanf("%s", ID_num);
				}
				while (ticket_num == 0)
				{
					printf("�ͻ���Ʊ��������Ϊ�գ�\n");
					printf("\t\t��Ʊ������");
					scanf("%d", &ticket_num);
				}
				if (p->left > 0 && p->left >= ticket_num)
				{
					insert_passengerList(h, PList, name, ID_num, flight_num, ticket_num);
					printf("\t\t��Ӧ����%8.2f��\n", p->price*ticket_num);
					getch();
					printf("\t\t��ϲ������Ʊ�ɹ���\n");
					return 1;
				}
				else
				{
					printf("\t\t***���ź����ú���������***\n");
					printf("\t\t***��ѡ���������������롪��1\n\t\t***ԤԼ�����롪��2\n\t\t***��ѡ�����롪��0***\n");
					printf("\t\t�������ֽ���ѡ��");
					scanf("%d", &k);
					if (k == 1)
					{
						printf("\t\t��������ѡ�ĺ��ࣺ");
						scanf("%s", flight_num);
						insert_passengerList(h, PList, name, ID_num, flight_num, ticket_num);
						printf("\t\t��ϲ������Ʊ�ɹ���\n");
						return 1;
					}
					else if (k == 2)
					{
#if DEV
						insert_waitList(WList, "ly", "151", "a", 1, 0);

#else
						printf("\t\t����������������");
						scanf("%s", name);
						printf("\t\t�����������ֻ��ţ�");
						scanf("%s", phone);
						printf("\t\t����������ҪԤԼ�ĺ���ţ�");
						scanf("%s", &flight_num);
						printf("\t\t����������Ҫ�Ļ�Ʊ������");
						scanf("%d", &ticket_num);

						//insert_waitList(WList, name, phone, flight_num, ticket_num, order_num);
						insert_waitList(WList, name, phone, flight_num, ticket_num, 0);
#endif

						printf("\t\t������Ʊ���ᾡ����ϵ����\n");
						return 2;
					}
				}
			}
			else
				p = p->next;
		}
		if (p == NULL)
			printf("\t\t�Բ���������ĺ��಻���ڣ�\n");
	}
	return 0;
}




//�ͻ���Ʊʱ����ĺ���Ŷ�Ӧ�����������ṩ������ѡ���ಢ�����ʾ
int find_same_flight(flightnode *h, char *flight_num)
{
	flightnode *t = h->next, *p = h->next;
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "�����", "��ɳ���", "�ִ����", "���ʱ��", "�ִ�ʱ��", "�۸�", "�Ƿ�����", "������");
	while (p != NULL)
	{
		if ((strcmp(t->start_place, p->start_place) == 0) && (strcmp(t->end_place, p->end_place) == 0) && (strcmp(t->flight_num, p->flight_num) != 0))
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
			mark = 1;
		}
		p = p->next;
	}
	if (mark = 0)
	{
		printf("\t\t��Ǹ���޿�ѡ���࣡\n");
		return 0;
	}
	return 1;
}




//����Ҫ��Ʊ�Ŀͻ�������֤���Ų��Ҹÿͻ���㣬����ɾ������
int delete_passenger(passengerList *&PList, flightnode *&h, char *name, char *ID_num)
{
	passengernode *p, *pr = PList->head;//prָ��ͻ������ͷ���
	p = pr->next;
	while (p != NULL)
	{
		if (strcmp(name, p->name) == 0 && strcmp(ID_num, p->ID_num) == 0)
		{
			for (flightnode *f = h->next; f != NULL; f = f->next)
			{
				if (strcmp(p->flight_num, f->flight_num) == 0)
				{
					f->left = f->left + p->ticket_num;
					f->ifull = 0;
					break;
				}
			}
			pr->next = p->next;
			free(p);
			printf("\t\t�ͻ�%s,%s��Ʊ�ɹ���\n", name, ID_num);
			return 1;
		}
		pr = pr->next;
		p = pr->next;
	}
	printf("\t\t�޴˿ͻ����޷���Ʊ��\n");
	return 0;
}
//�����Ʊ���������ӿͻ�����ɾ�����޸���Ӧ������Ϣ
void cancel(passengerList *&PList, flightnode *&h)
{
	char name[20], ID_num[20];
	printf("\t\t���������������");
	scanf("%s", name);
	printf("\t\t���������֤���ţ�");
	scanf("%s", ID_num);
	delete_passenger(PList, h, name, ID_num);
}

//���պ���Ų�ѯ������Ϣ
int flight_num_check(flightnode *h, char *flight_num)
{
	flightnode *p = h;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "�����", "��ɳ���", "�ִ����", "���ʱ��", "�ִ�ʱ��", "�۸�", "�Ƿ�����", "������");
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->flight_num, flight_num) == 0)
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
			return 1;
		}
	}
	printf("\t\t��Ǹ��û�к����Ϊ%s�ĺ�����Ϣ��\n", flight_num);
	return 0;
}

//������к�����Ϣ
void check_all_flight(flightnode *h)
{
	flightnode *p = h;
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-10s%-8s\n", "�����", "��ɳ���", "�ִ����", "���ʱ��", "�ִ�ʱ��", "�۸�", "�Ƿ�����", "������");
	for (; p != NULL; p = p->next)
	{
		printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-10d%-8d\n", p->flight_num, p->start_place, p->end_place, p->start_time, p->end_time, p->price, p->ifull, p->left);
		mark = 1;
	}
	if (mark == 0)
		printf("\t\t������ϢΪ�գ�\n");
}

//ѡ��ʹ�ú��ַ�ʽ�Ժ�����Ϣ���в�ѯ
void flight_check(flightnode *h)
{
	flightnode *p = h->next;
	char flight_num[10], start_place[20], end_place[20];
	char a;
	printf("\t\t��ѡ�񺽰��ѯ��ʽ��\n");
	printf("\t\t1��������Ž��в�ѯ��\n");
	printf("\t\t2������ɵִ���н��в�ѯ��\n");
	printf("\t\t3�����ȫ��������Ϣ.\n\t\t�����룺\n");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
	{
		printf("\t\t�����뺽��ţ�");
		scanf("%s", flight_num);
		flight_num_check(p, flight_num);
	}
	else if (a == '2')
	{
		printf("\t\t��������ɳ��У�");
		scanf("%s", start_place);
		printf("\t\t������ִ���У�");
		scanf("%s", end_place);
		place_check(p, start_place, end_place);
	}
	else if (a == '3')
		check_all_flight(p);
	else
		return;
}




//���ͻ�������֤���Ų�ѯ������Ϣ
int ID_name_check(passengerList *PList, char *name, char *ID_num)
{
	passengernode *p = PList->head->next;
	int mark = 0;
	printf("%-8s%-20s%-20s%-10s%-8s%\n", "������", "����", "֤����", "�����", "��Ʊ����");
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->ID_num, ID_num) == 0 && strcmp(p->name, name) == 0)
		{
			printf("%-8d%-20s%-20s%-10s%-8d%\n", p->order_num, p->name, p->ID_num, p->flight_num, p->ticket_num);
			mark = 1;
		}
	}
	if (mark == 0)
	{
		printf("\t\t��Ǹ��û��%s��%s�Ķ�����Ϣ��\n", name, ID_num);
		return 0;
	}
	return 1;
}
//�������Ų�ѯ������Ϣ
int order_num_check(passengerList *PList, int order_num)
{
	passengernode *p = PList->head->next;
	printf("%-8s%-20s%-20s%-10s%-8s%\n", "������", "����", "֤����", "�����", "��Ʊ����");
	for (; p != NULL; p = p->next)
	{
		if (p->order_num == order_num)
		{
			printf("%-8d%-20s%-20s%-10s%-8d%\n", p->order_num, p->name, p->ID_num, p->flight_num, p->ticket_num);
			return 1;
		}
	}
	printf("\t\t��Ǹ��û�ж�����Ϊ%d�Ķ�����Ϣ��\n", order_num);
	return 0;
}


//������ж�����Ϣ
void check_all_passenger(passengerList *PList)
{
	passengernode *p = PList->head->next;
	int m = 0;
	printf("%-8s%-20s%-20s%-10s%-8s%\n", "������", "����", "֤����", "�����", "��Ʊ����");
	for (; p != NULL; p = p->next)
	{
		printf("%-8d%-20s%-20s%-10s%-8d%\n", p->order_num, p->name, p->ID_num, p->flight_num, p->ticket_num);
		m = 1;
	}
	if (m == 0)
		printf("\t\t������ϢΪ�գ�\n");
}

//ѡ��ʹ�ú��ַ�ʽ��ѯ������Ϣ
void passenger_check(passengerList *PList)
{
	char name[20], ID_num[15];
	int order_num = 0;
	char a;
	printf("\t\t��ѡ�񶩵���ѯ��ʽ��\n");
	printf("\t\t1�����ͻ�������֤���Ž��в�ѯ\n");
	printf("\t\t2���������Ž��в�ѯ\n");
	printf("\t\t3���鿴ȫ��������Ϣ\n\t\t��ѡ�����룺");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
	{
		printf("\t\t������ͻ�������");
		scanf("%s", name);
		printf("\t\t������֤���ţ�");
		scanf("%s", ID_num);
		ID_name_check(PList, name, ID_num);
	}
	else if (a == '2')
	{
		printf("\t\t�����붩���ţ�");
		scanf("%d", order_num);
		order_num_check(PList, order_num);
	}
	else
		check_all_passenger(PList);
}


//��ԤԼ����Ų�ѯԤԼ�ͻ���Ϣ
int wait_flightnum_check(waitList *WList, char *flight_num)
{
	waitnode *p = WList->head->next;
	printf("%-20s%-20s%-10s%-8s%\n", "����", "�ֻ���", "�����", "��Ʊ����");
	for (; p != NULL; p = p->next)
	{
		if (p->flight_num == flight_num)
		{
			printf("%-20s%-20s%-10s%-8d%\n", p->name, p->phone, p->flight_num, p->ticket_num);
			return 1;
		}
	}
	printf("\t\t��Ǹ��û��ԤԼ�˺���ŵ���Ϣ��\n");
	return 0;
}

//�������ԤԼ�ͻ���Ϣ
void check_all_wait(waitList *WList)
{
	waitnode *a = WList->head->next;
	int m = 0;
	printf("%-20s%-20s%-10s%-8s%\n", "����", "�ֻ���", "�����", "��Ʊ����", "ԤԼ�ŶӺ�");
	for (; a != NULL; a = a->next)
	{
		printf("%-20s%-20s%-10s%-8d%\n", a->name, a->phone, a->flight_num, a->ticket_num, a->order_num);
		m = 1;
	}
	if (m == 0)
		printf("\t\tԤԼ�ͻ���ϢΪ�գ�\n");
}

//ѡ��ʹ�ú��ַ�ʽ��ѯԤԼ�ͻ���Ϣ
void wait_check(waitList *WList)
{
	char flight_num[10];
	char a;
	printf("\t\t��ѡ��ԤԼ�ͻ���Ϣ��ѯ��ʽ��\n");
	printf("\t\t1����ԤԼ����Ž��в�ѯ\n");
	printf("\t\t2���鿴ȫ��ԤԼ�ͻ���Ϣ\n\t\t��ѡ�����룺");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
	{
		printf("\t\t������ԤԼ����ţ�");
		scanf("%c", &flight_num);
		wait_flightnum_check(WList, flight_num);
	}
	else if (a == '2')
	{
		check_all_wait(WList);
	}
}



//�޸ĺ���ʱ��
void modify_flight_time(flightnode *&h, passengerList *&PList)
{
	flightnode *p = h->next;
	char flight_num[10], start_time[10], end_time[10];
	printf("\t\t������Ҫ�޸ĺ���ĺ���ţ�");
	scanf("%s", flight_num);
	if (flight_num_check(p, flight_num) == 1)
	{
		printf("\t\t�������޸ĺ�����ʱ�䣺");
		scanf("%s", start_time);
		printf("\t\t�������޸ĺ�ĵִ�ʱ�䣺");
		scanf("%s", end_time);
		for (; p != NULL; p = p->next)
		{
			if (strcmp(flight_num, p->flight_num) == 0)
			{
				strcpy(p->start_time, start_time);
				strcpy(p->end_time, end_time);
				printf("\t\t����%sʱ���޸ĳɹ���\n", flight_num);
			}
		}
	}
}

//����ĳ�������ɾ��������
void delete_flight(flightnode *&h, passengerList *&PList)
{
	flightnode *p, *pr;
	passengernode *q, *qr;
	char flight_num[10];
	int mark = 1;
	qr = PList->head;//prΪ�ͻ������ͷ���
	q = qr->next;//��p��Ϊ�м�ָ��Կͻ�������Ҫɾ���Ŀͻ��ڵ���в���
	pr = h;//prΪ���������ͷ���
	p = pr->next;//��p��Ϊָ��Ժ���������Ҫɾ���ĺ���ڵ���в���
	printf("\t\t��������Ҫɾ���ĺ���ţ�");
	scanf("%s", flight_num);
	while (p != NULL)//Ҫɾ���ĺ��಻���ڣ��������ɾ������
	{
		if (strcmp(flight_num, p->flight_num) == 0)
		{
			pr->next = p->next;//�ƶ�ָ����Ҫɾ���ĺ���ڵ�
			free(p);
			printf("\t\tɾ��%s����ɹ���\n", flight_num);
			mark = 0;
			p = NULL;
		}
		if (pr->next != NULL)
		{
			pr = pr->next;
			p = pr->next;
		}
	}
	if (mark == 1)
		printf("\t\t�޴˺��࣬�޷�ɾ����\n");
	else
	{
		while (q != NULL)//Ҫɾ���Ŀͻ������ڣ��������ɾ������
		{
			if (strcmp(flight_num, q->flight_num) == 0)
			{
				qr->next = q->next;//�ƶ�ָ����Ҫɾ���Ŀͻ��ڵ�
				free(q);
				q = NULL;
			}
			if (qr->next != NULL)
			{
				qr = qr->next;
				q = qr->next;
			}
		}
	}
}


//�޸ĺ�����Ϣ���������ɾ��������Ϣ���޸ĺ�����ɵִ�ʱ�䣩
void modify_flight(flightnode *&h, passengerList *&PList)
{
	flightnode *p = h->next;
	char a;
	printf("\t\t****************************\n");
	printf("\t\t********������Ϣ�޸�********\n");
	printf("\t\t****************************\n");
	printf("\t\t*       ���Ӻ��ࡪ��1      *\n");
	printf("\t\t*       ɾ�����ࡪ��2      *\n");
	printf("\t\t*       �޸ĺ���ʱ�䡪��3  *\n");
	printf("\t\t****************************\n");
	printf("\t\t��ѡ��");
	a = getch();
	printf("%c\n", a);
	if (a == '1')
		add_flight(h);
	else if (a == '2')
		delete_flight(h, PList);
	else if (a == '3')
	{
		modify_flight_time(h, PList);
	}
	else
		return;
}


int main()
{
	char choice;
	int t = 1;
	flightnode *flight;
	passengerList *PList;
	waitList *WList;
	init_flight(flight);
	init_passengerList(PList);
	init_waitList(WList);
	load_flight(flight);
	load_passenger(PList);
	load_wait(WList);
#if DEV
	insert_flight(flight, "a", "f", "t", "y", "t", 0, 1, 1);
	printf("����Ӳ��Ժ���\n");
#else
#endif

	while (t == 1)
	{
		printf("\t\t****************************\n");
		printf("\t\t******�ɻ���Ʊϵͳ�˵�******\n");
		printf("\t\t****************************\n");
		printf("\t\t*       ¼����Ϣ����1      *\n");
		printf("\t\t*       ��    Ʊ����2      *\n");
		printf("\t\t*       ��    Ʊ����3      *\n");
		printf("\t\t*       ��ѯ���ࡪ��4      *\n");
		printf("\t\t*       ��ѯ��������5      *\n");
		printf("\t\t*       ��ѯԤԼ����6      *\n");
		printf("\t\t*       �޸ĺ��ߡ���7      *\n");
		printf("\t\t*       �����˳�����0      *\n");
		printf("\t\t****************************\n");
		printf("\t\t��ѡ�����");
		choice = getch();
		printf("%c\n", choice);
		system("cls");
		if (choice == '1')
		{
			add_flight(flight);
			getch();
			system("cls");
		}
		else if (choice == '2')
		{
			book(flight, PList, WList);
			getch();
			system("cls");
		}
		else if (choice == '3')
		{
			cancel(PList, flight);
			getch();
			system("cls");
		}
		else if (choice == '4')
		{
			flight_check(flight);
			getch();
			system("cls");
		}
		else if (choice == '5')
		{
			passenger_check(PList);
			getch();
			system("cls");
		}
		else if (choice == '6')
		{
			wait_check(WList);
			getch();
			system("cls");
		}
		else if (choice == '7')
		{
			modify_flight(flight, PList);
			getch();
			system("cls");
		}
		else if (choice == '0')
		{
			printf("\t\t�ټ���\n");
			t = 0;
		}
	}
	save_flight(flight);
	save_passenger(PList);
	save_wait(WList);
	return 0;
}