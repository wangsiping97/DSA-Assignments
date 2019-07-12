#include<stdio.h>
#include<stdlib.h>
#include"1.h"
#include"fatal.h"

struct TreeNode{
    int element;
    SearchTree left;
    SearchTree right;
};

/* (a) Implement all the routines */

SearchTree MakeEmpty(SearchTree t){
    if(t != NULL){
        MakeEmpty(t->left);
        MakeEmpty(t->right);
        free(t);
    }
    return NULL;
}

Position Find(int x, SearchTree t){
    if(t == NULL) return NULL;
    if(x > t->element) return Find(x, t->right);
    else if(x < t->element) return Find(x, t->left);
    else return t;
}

Position FindMax(SearchTree t){
    if(t != NULL){
        while(t->right)
        t = t->right;
    }
    return t;
}

Position FindMin(SearchTree t){
  if(t==NULL)
    return NULL;
  else if(t->left==NULL)
    return t;
  else
    return FindMin(t->left);
}

SearchTree Insert(int x, SearchTree t){
    if(t == NULL){
        t = (SearchTree) malloc(sizeof(struct TreeNode));
        if(t == NULL) {
            printf("Out of space!\n");
            return NULL;
        }
        else{
            t->element = x;
            t->left = NULL;
            t->right = NULL;
        }
    }
    else if(x < t->element)
        t->left = Insert(x, t->left);
    else if(x > t->element)
        t->right = Insert(x, t->right);
    return t;
}

SearchTree Delete(int x, SearchTree t){
    Position tmpcell;
    if(t == NULL){
        printf("Element not found.\n");
        return NULL;
    }
    else if(x > t->element) t->right = Delete(x, t->right);
    else if(x < t->element) t->left = Delete(x, t->left);
    else{ // x = t->element
        if(t->left && t->right){ // two chirdren
            tmpcell = FindMin(t->right);
            t->element = tmpcell->element;
            t->right = Delete(t->element, t->right);
        }
        else{ // one or no child
            tmpcell = t;
            if(!t->left) t = t->right;
            else if(!t->left) t = t->left;
            free(tmpcell);
        }
    }
    return t;
}

void Retrieve(Position P){
  printf ("%d ", P->element);
}

void InOrder(SearchTree t){
    if(t != NULL){
        InOrder(t->left);
        Retrieve(t);
        InOrder(t->right);
    }
}

void PreOrder(SearchTree t){
    if(t != NULL){
        Retrieve(t);
        PreOrder(t->left);
        PreOrder(t->right);
    }
}

void PostOrder(SearchTree t){
    if(t != NULL){
        PostOrder(t->left);
        PostOrder(t->right);
        Retrieve(t);
    }
}

void LevelOrder(SearchTree t){
    SearchTree Queue[100];
    int front, rear;
    front = -1; rear = 0;
    Queue[rear] = t;
    while(front != rear){
        front ++;
        Retrieve(Queue[front]);
        if(Queue[front]->left != NULL){
            rear ++;
            Queue[rear] = Queue[front]->left;
        }
        if(Queue[front]->right != NULL){
            rear ++;
            Queue[rear] = Queue[front]->right;
        }
    }
}

/* (b) Construct tree t by inserting the elements one by one with Insert() */

SearchTree ConstructTree(){
    SearchTree t = NULL;
    int i;
    int array[13] = {10, 4, 11, 2, 6, 12, 1, 3, 5, 8, 13, 7, 9};
    t = MakeEmpty(t);
    for(i = 0; i < 13; i ++)
    t = Insert(array[i],t);
    return t;
}

/* (c) Call the ConstructTree() in main and output the traverse sequences */

int main(){
    SearchTree t = ConstructTree();
    printf("InOrder:\n");
    InOrder(t);
    printf("\nPreOrder:\n");
    PreOrder(t);
    printf("\nPostOrder:\n");
    PostOrder(t);
    printf("\nLevelOrder:\n");
    LevelOrder(t);
    printf("\n");
    return 0;
}