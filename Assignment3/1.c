# include<stdio.h>
# include<stdlib.h>
# include"HeadFile.h"

struct node{
    int element;
    Position next;
};

/* 轮子 */
List CreateList(int n){
    List head = NULL;
    Position p = NULL;
    int i;

    for(i = 1; i <= n; ++i){
        if (p == NULL) 
            head = p = (Position)malloc(1);
        else {
            p -> next = (Position)malloc(1);
            p = p -> next;
        }
        scanf("%d", &p -> element);
        p -> next = NULL;
    }
    return (head);
}

/* 实验 */
int main(){
    int n;
    scanf("%d", &n);
    List A; 
    A = CreateList(n);
    Print(A);
    system("pause");
    return 0;
}