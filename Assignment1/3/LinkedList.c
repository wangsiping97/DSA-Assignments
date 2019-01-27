#include<stdio.h>
#include<stdlib.h>

#define LEN sizeof(struct linkedlist)

struct linkedlist
{
    int num;
    struct linkedlist *next;
};

struct linkedlist *create()
{
    struct linkedlist *head = NULL;
    struct linkedlist *p = NULL;

    for(int i = 0; i < 10; ++ i)
    {
        if (p == NULL) 
            head = p = (struct linkedlist *)malloc(LEN);
        else 
        {
            p -> next = (struct linkedlist *)malloc(LEN);
            p = p -> next;
        }
        scanf("%d", &p -> num);
        p -> next = NULL;
    }
    return(head);
}

struct linkedlist *reverse(struct linkedlist *head)
{
    struct linkedlist *p, *q, *r;
    if(NULL == head || NULL == head -> next)
        return head;
    else
    {
        p = head;
        q = head -> next;
        head -> next = NULL;
        while(q)
        {
            r = q -> next;
            q -> next = p;
            p = q;
            q = r;
        }
        head = p;
        return head;
    }
}

int main()
{
    printf("Please input 10 numbers: \n");
    struct linkedlist *head = create();
    head = reverse(head);
    printf("The reversed list: \n");
    struct linkedlist *p = head;
    while(p)
    {
        printf("%d", p -> num);
        p = p -> next;
    }
    return 0;
}