#include <stdlib.h>
#include <stdio.h>

struct Node
{
    char data;         //佇列資料的宣告
    struct Node *next; //佇列中用來指向下一個節點
};
typedef struct Node Stack_Node;   //定義堆疊中節點的新形態
typedef Stack_Node *Linked_Stack; //定義串列佇列的新形態
Linked_Stack front = NULL;        //指向佇列頂端的指標
Linked_Stack rear = NULL;         //指向佇列尾端的指標

int isEmpty();
void push(char);
char pop();

int main()
{
    FILE *fp;
    char ch;

    fp = fopen("addr.txt", "r");

    if (fp == NULL)
    {
        printf("open file error!!\n");
    }
    else
    {
        //EOF = end of file
        while ((ch = getc(fp)) != EOF)
        {
            if (ch == '\r')
            {
                printf("\n---------------------------------------------------------------");
            }
            else if (ch == ',')
            {
                while (!isEmpty())
                {
                    printf("%c", pop());
                }
                printf(" | ");
            }
            else
            {
                push(ch);
                //printf("%c", pop());
            }
        }

        printf("\n");
    }

    fclose(fp);
    return 0;

    //dev | dhcp | ip addr | net mask | getway | dns1 | dns2 | wan
}

/*判斷是否為空佇列*/
int isEmpty()
{
    if (front == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*將指定的資料存入佇列*/
void push(char data)
{
    Linked_Stack new_add_node; //新加入節點的指標

    /*配置新節點的記憶體*/
    new_add_node = (Linked_Stack)malloc(sizeof(Stack_Node));
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
    Linked_Stack ptr_f = front; //指向佇列頭端的指標
    char temp;

    if (ptr_f != NULL)
    {
        front = front->next;
        temp = ptr_f->data;
    }
    free(ptr_f);
    return temp;
}