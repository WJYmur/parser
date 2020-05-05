#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STR_LEN 16

struct Node
{
    char data;         //佇列資料的宣告
    struct Node *next; //佇列中用來指向下一個節點
} Queue_Node;

Queue_Node *front = NULL;        //指向佇列頂端的指標
Queue_Node *rear = NULL;         //指向佇列尾端的指標

struct Network
{
    char dev[N];
    char dhcp[N];
    char addr[N];
    char mask[N];
    char getway[N];
    char dns1[N];
    char dns2[N];
    char wan[N];
    struct Network *next;
};
typedef struct Network Net_Node;
typedef Net_Node *Linked_Net;
Linked_Net first = NULL;
Linked_Net temp = NULL;

Linked_Net new_net();
Linked_Net push_net(Linked_Net);

/*新增Linked_Net*/
Linked_Net push_net(Linked_Net n)
{
    if (first == NULL)
    {
        first = n;
        n = new_net();
        first->next = n;
        n->next = NULL;
    }
    else
    {
        temp = n;
        n = new_net();
        temp->next = n;
        n->next = NULL;
    }

    return n;
}

/*釋放net取用過的記憶體空間*/
void free_net(Linked_Net n)
{
    if (n != NULL)
    {
        //printf("釋放記憶體空間!!!\n");
        if (n->next != NULL)
            free_net(n->next);
        free(n);
    }
}

/*印出net parser後的值*/
void print_net(Linked_Net n)
{
    if (n != NULL)
    {
        printf(" --------------------------------\n");
        printf(" | dev    :%20s |\n", n->dev);
        printf(" | dhcp   :%20s |\n", n->dhcp);
        printf(" | addr   :%20s |\n", n->addr);
        printf(" | mask   :%20s |\n", n->mask);
        printf(" | getway :%20s |\n", n->getway);
        printf(" | dns1   :%20s |\n", n->dns1);
        printf(" | dns2   :%20s |\n", n->dns2);
        printf(" | wan    :%20s |\n", n->wan);

        if (n->next != NULL)
            print_net(n->next);
        else
            printf(" --------------------------------\n");
    }
}

/*創建新的net*/
Linked_Net new_net()
{
    Linked_Net new_net;
    new_net = (Linked_Net)malloc(sizeof(Net_Node));
    return new_net;
}

/*將佇列中的資料輸出存放*/
void worker(int i, Linked_Net net, char *c)
{
    //printf("[%d]", i);
    //dev | dhcp | ip addr | mask | getway | dns1 | dns2 | wan
    for (int j = 0; j < strlen(c); j++)
    {
        switch (i)
        {
        case 1:
            net->dev[j] = c[j];
            break;
        case 2:
            net->dhcp[j] = *(c + j);
            break;
        case 3:
            net->addr[j] = *(c + j);
            break;
        case 4:
            net->mask[j] = *(c + j);
            break;
        case 5:
            net->getway[j] = *(c + j);
            break;
        case 6:
            net->dns1[j] = *(c + j);
            break;
        case 7:
            net->dns2[j] = *(c + j);
            break;
        case 8:
            net->wan[j] = *(c + j);
            break;
        default:
            break;
        }
    }
}

/*判斷是否為空佇列*/
int isEmpty()
{
    return (front == NULL) ? 1 : 0;
}

/*將指定的資料存入佇列*/
void push(char data)
{
    Linked_Queue new_add_node; //新加入節點的指標

    /*配置新節點的記憶體*/
    new_add_node = (Linked_Queue)malloc(sizeof(Queue_Node));
    new_add_node->data = data; //將傳入的值設為節點的內容
    new_add_node->next = NULL; //將新節點指向佇列的點端

    if (isEmpty())
    {
        front = new_add_node;
        rear = new_add_node;
    }
    else
    {
        rear->next = new_add_node;
        rear = new_add_node;
    }
}

/*從佇列取出資料*/
char pop()
{
    Linked_Queue ptr_f = front; //指向佇列頂端的指標
    char temp;

    if (ptr_f != NULL)
    {
        front = front->next;
        temp = ptr_f->data;
    }
    free(ptr_f);
    return temp;
}

int main(int arcg, char *argv[])
{
   
    char ch;
    char cookie[N];
    int i = 0, count = 1;

     FILE *fp = fopen("addr.txt", "r");

    if (fp == NULL)
    {
        printf("open file error!!\n");
        return 0;
    }

    Linked_Net new_add_net;
    new_add_net = new_net();
    //EOF = end of file
    while ((ch = getc(fp)) != EOF)
    {
        if (ch == ',' || ch == '\n' || ch == '\r')
        {
            i = 0;

            if (ch == ',' || ch == '\r')
            {
                while (!isEmpty())
                {
                    cookie[i] = pop();
                    i++;
                }

                //printf("%s", cookie);
                worker(count, new_add_net, cookie);
                //printf(" | ");
                count++;
            }
            else
            {
                //printf("\n");
                new_add_net = push_net(new_add_net);
                count = 1;
                //break;
            }
        }
        else
        {
            push(ch);
            //pop();
        }

        while (i >= 0)
        {
            cookie[i] = '\0';
            i--;
        }
    }

    i = 0;
    while (!isEmpty())
    {
        cookie[i] = pop();
        i++;
    }

    //printf("%s", cookie);
    worker(count, new_add_net, cookie);

    //printf("\n\n");
    print_net(first);
    free_net(first);


    fclose(fp);
    return 0;
}


