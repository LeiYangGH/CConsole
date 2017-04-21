#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
typedef struct patient  
{  
    char ID[10];  
    char name[10];  
    char bingli[300];  
    int cost[3];  
    struct patient * next;  
}node1;  
typedef struct storage  
{  
    int amount[3];  
    int price[3];  
}node2;  
node2 init(node2 temp)  
{  
      
    temp.amount[0]=20;  
    temp.amount[1]=20;  
    temp.amount[2]=10;  
    temp.price[0]=5;  
    temp.price[1]=9;  
    temp.price[2]=16;  
    return temp;  
}  
void mainmeun()  
{  
    printf("\n");  
    printf("      �����ǿ��ֵ�ԴȪ\n");  
    printf("********************************\n");  
    printf("1.ע���²�����Ϣ\n");  
    printf("2.��ѯ������Ϣ\n");  
    printf("3.д����\n");  
    printf("4.��������\n");  
    printf("5.�г����в�����Ϣ\n");  
    printf("6.�������в�����Ϣ\n");  
    printf("7.����\n");  
    printf("8.��ѯҩƷ���\n");  
    printf("9.�뿪\n");  
    printf("*********************************\n");  
}  
node1 * create(node1 *p1)  
{  
    node1 *p;  
    p=(node1 *)malloc(sizeof(node1));  
    printf("�����벡��ID\n");  
    scanf("%s",p->ID);  
      
    while(p1->ID&&strcmp(p1->ID,p->ID))  
    {  
        p1=p1->next;  
    }  
    if(p1==NULL)  
    {  
        printf("�����벡������\n");  
        scanf("%s",p->name);  
        strcpy(p->bingli,"0");  
        p->cost[0]=0;  
        p->cost[1]=0;   
        p->cost[2]=0;  
        p->next=NULL;  
        printf("��ע��������Ϣ\n");  
    return p;  
    }  
    else   
    {  
        printf("���벡��ID�Դ���,ע��ʧ��\n");  
        return p;  
    }  
}  
node1 * insert(node1 * head,node1 *p)  
{  
    node1 *p1;   
    if(head==NULL)  
    {  
        head=p;  
        p->next=NULL;   
    }  
    else  
    {  
        p1=head;  
        while(p1->next)  
        {  
            p1=p1->next;   
        }  
        p1->next=p;  
        p->next=NULL;   
    }  
    return(head);  
}  
void search(node1 *p1)  
{  
    int sum;  
    char a[10];  
    printf("�����벡��ID\n");  
    scanf("%s",a);  
    while(p1->ID&&strcmp(p1->ID,a))  
    {  
        p1=p1->next;  
    }  
    if(p1)  
    {  
        printf("ID:%s\n",p1->ID);  
        printf("����:%s\n",p1->name);  
        printf("����:%s\n",p1->bingli);  
        printf("���Ѽ�¼:\n");  
        if(p1->cost[0])  
            printf("���׶�\t%d\n",p1->cost[0]);  
        if(p1->cost[1])  
            printf("��ð��\t%d\n",p1->cost[1]);  
        if(p1->cost[2])  
            printf("������\t%d\n",p1->cost[2]);  
        sum=p1->cost[0]*5+p1->cost[1]*9+p1->cost[2]*16;  
        printf("�ܷ���\t%d\n",sum);  
    }  
        else  
            printf("�ò���û��ע��\n");  
      
  
}  
void bingli(node1 *p)  
{  
    char a[10];  
    char bingli[300];  
    char enter[5]=":\n";  
    printf("�����벡��ID\n");  
    scanf("%s",a);  
    while(p->ID&&strcmp(p->ID,a))  
    {  
        p=p->next;  
    }  
    if(p==NULL)  
    {  
        printf("�޸ò�����Ϣ\n");  
    }  
    else  
    {  
        printf("��д����:\n");  
        scanf("%s",bingli);  
        strcpy(p->bingli,bingli);  
        strcat(p->bingli,enter);  
    }  
}  
node2 buy(node1 *p,node2 temp)  
{  
    char i[10];  
    printf("�����벡��ID\n");  
    scanf("%s",i);  
    while(p->ID&&strcmp(p->ID,i))  
    {  
        p=p->next;  
    }  
      
    while(1)  
    {  
        int a,b,c,d;  
        printf("1.������׶�\n");  
        printf("2.�����ð��\n");  
        printf("3.���򲡶���\n");  
        printf("0.�˳�\n");  
        scanf("%d",&a);  
        switch(a)  
        {  
            case 1:  
                do  
                {  
                    printf("���п��%d\n",temp.amount[0]);  
                    printf("������׶�����:");  
                    scanf("%d",&b);  
                    temp.amount[0]=temp.amount[0]-b;  
                    p->cost[0]+=b*5;   
                }while(b>20);  
                break;  
            case 2:  
                do  
                {  
                    printf("���п��%d\n",temp.amount[1]);  
                    printf("�����ð������:");  
                    scanf("%d",&c);  
                    temp.amount[1]=temp.amount[1]-c;  
                    p->cost[1]+=c*9;  
                }while(c>20);  
                break;  
            case 3:  
                do  
                {  
                    printf("���п��%d\n",temp.amount[2]);  
                    printf("���򲡶�������:");  
                    scanf("%d",&d);  
                    temp.amount[2]=temp.amount[2]-d;  
                    p->cost[2]+=d*16;  
                }while(d>=10);  
                break;  
            case 0:  
                return temp;  
        }  
    }  
      
}  
void list(node1 *p)  
{  
      
    if(p==NULL)  
        printf("���޲�����Ϣ\n");  
    else  
    {     
        do{  
            printf("����ID:%s\n",p->ID);  
            printf("��������:%s\n",p->name);  
          
            printf("���˲���:%s\n",p->bingli);  
              
            printf("������׶�����:%d\n",p->cost[0]);  
              
            printf("�����ð�����:%d\n",p->cost[1]);  
          
            printf("���򲡶������:%d\n",p->cost[2]);  
            printf("\n");  
            p=p->next;   
        }while(p!=NULL);  
    }  
}  
node1 * load(node1 *p)  
{   
    char ID[10],name[10],bingli[300];  
    int cost0,cost1,cost2;  
    FILE *fp;  
    fp=fopen("information.txt","r");  
    int n=0;  
    node1 *p1,*p2;  
      
        while(!feof(fp))  
        {  
            n++;  
            p1=(node1 *)malloc(sizeof(node1));  
            fscanf(fp,"%s",ID);  
            fscanf(fp,"%s",name);  
            fscanf(fp,"%s",bingli);  
            fscanf(fp,"%d",&cost0);  
            fscanf(fp,"%d",&cost1);  
            fscanf(fp,"%d",&cost2);  
              
            strcpy(p1->ID,ID);  
            strcpy(p1->name,name);  
            strcpy(p1->bingli,bingli);  
            p1->cost[0]=cost0;  
            p1->cost[1]=cost1;  
            p1->cost[2]=cost2;  
            p1->next=NULL;   
              
            if(n==1)  
            {  
                p=p1;  
                p2=p1;  
            }  
              
            else  
            {  
                p2->next=p1;  
                p2=p1;  
                   
            }  
        }  
      
        fclose(fp);  
  
        return p;  
}  
void save(node1 *p)  
{  
    FILE *fp;  
    fp=fopen("information.txt","w");  
    if(p!=NULL)  
        do{  
        fprintf(fp,"%s\n",p->ID);  
        fprintf(fp,"%s\n",p->name);  
        fprintf(fp,"%s\n",p->bingli);  
        fprintf(fp,"%d\n",p->cost[0]);  
        fprintf(fp,"%d\n",p->cost[1]);  
        fprintf(fp,"%d\n",p->cost[2]);  
        p=p->next;  
        }while(p!=NULL);  
        fclose(fp);  
}  
void liststock(node2 temp)  
{  
    printf("ҩƷ\t����\t�۸�\t\n");  
    printf("���׶�\t%d\t%d\t\n",temp.amount[0],temp.price[0]);  
    printf("��ð��\t%d\t%d\t\n",temp.amount[1],temp.price[1]);  
    printf("������\t%d\t%d\t\n",temp.amount[2],temp.price[2]);  
                  
}  
chose()  
{  
    node1 *head=NULL,*p;  
    node2 temp;  
    temp=init(temp);  
    while(1)  
    {  
        mainmeun();  
        int a;  
        scanf("%d",&a);  
        switch(a)  
        {  
        case 1:  
            p=create(head);  
            head=insert(head,p);  
            break;  
        case 2:  
            search(head);  
            break;  
        case 3:  
            bingli(head);  
            break;  
        case 4:  
            temp=buy(head,temp);  
            break;  
        case 5:  
            list(head);  
            break;  
        case 6:  
            head=load(head);  
            break;  
        case 7:  
            save(head);  
            break;  
        case 8:  
            liststock(temp);  
            break;  
        case 9:  
            printf("ллʹ��\n");  
            return(0);  
        default:  
            printf("����������������\n");  
            break;  
        }  
    }  
}  
void main()  
{  
    chose();  
} 