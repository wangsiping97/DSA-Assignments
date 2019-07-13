#include<stdio.h>
#include<stdlib.h>
#include"2.h"
#include"fatal.h"

# define HEIGHT(p) ( ((p) == NULL) ? -1 : ((p)->height) )
# define MAX(a, b) ( (a) > (b) ? (a) : (b) )

struct AVLNode{
    int element;
    AVLTree left;
    AVLTree right;
    int height;
};

int Update_Height(Position p) {
    return p->height = MAX(HEIGHT(p->left), HEIGHT(p->right)) + 1;
}

void Retrieve(Position p){
    printf("%d ", p->element);
}

/* (a)
 * Implement routines introduced in class 
 */

Position SingleRotateWithLeft(Position k2){
    Position k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    Update_Height(k2);
    Update_Height(k1);
    return k1;
}

Position SingleRotateWithRight(Position k2){
    Position k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    Update_Height(k2);
    Update_Height(k1);
    return k1;
}

Position DoubleRotateWithLeft(Position k3){
    k3->left = SingleRotateWithRight(k3->left);
    return SingleRotateWithLeft(k3);
}

Position DoubleRotateWithRight(Position k3){
    k3->right = SingleRotateWithLeft(k3->right);
    return SingleRotateWithRight(k3);
}

AVLTree Insert(int x, AVLTree t){
    if(t == NULL){
        t = (AVLTree)malloc(sizeof(struct AVLNode));
        if(t == NULL) { printf("Out of Space!"); return NULL; }
        else{ t->element = x; t->left = NULL; t->right = NULL; }
    }
    else if(x < t->element){
        t->left = Insert(x, t->left);
        if(HEIGHT(t->left) - HEIGHT(t->right) == 2)
            t = (x < t->left->element) ? SingleRotateWithLeft(t) : DoubleRotateWithLeft(t);
    }
    else if(x > t->element){
        t->right = Insert(x, t->right);
        if(HEIGHT(t->right) - HEIGHT(t->left) == 2)
            t = (x > t->right->element) ? SingleRotateWithRight(t) : DoubleRotateWithRight(t);
    }
    Update_Height(t);
    return t;
}

void InOrder(AVLTree t){
    if(t != NULL){
        InOrder(t->left);
        Retrieve(t);
        InOrder(t->right);
    }
}

void PreOrder(AVLTree t){
    if(t != NULL){
        Retrieve(t);
        PreOrder(t->left);
        PreOrder(t->right);
    }
}

void PostOrder(AVLTree t){
    if(t != NULL){
        PostOrder(t->left);
        PostOrder(t->right);
        Retrieve(t);
    }
}

void LevelOrder(AVLTree t){
    AVLTree Queue[100];
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

/* (b)
 * Implement PrintTreeEdge()
 */

void PrintTreeEdge(Position p){
    if(p == NULL) return;
    if(p->left != NULL){
        printf("%d -> %d\n", p->element, p->left->element);
        PrintTreeEdge(p->left);
    }
    if(p->right != NULL){
        printf("%d -> %d\n", p->element, p->right->element);
        PrintTreeEdge(p->right);
    }
}

/* (d)
 * Read data from the text file in main()
 * Call Insert() with rotate operations
 * Output the finally derived AVL tree to screen by calling PrintTreeEdge() 
 */

int main(){
    AVLTree t = NULL;
    int i;
    FILE* f = fopen("TreeData.txt", "r");
    if(f == NULL) return 0;
    while(! feof(f)){
        fscanf(f,"%d ",&i);
        t=Insert(i,t);
    } 
    printf("All edges:\n");
    PrintTreeEdge(t);
    printf("InOrder:\n");
    InOrder(t);
    printf("\nPreOrder:\n");
    PreOrder(t);
    printf("\nPostOrder:\n");
    PostOrder(t);
    printf("\nLevelOrder:\n");
    LevelOrder(t);
    printf("\n");
    fclose(f);
    return 0;
}