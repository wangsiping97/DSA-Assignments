#ifndef _AVLTree_H
#define _AVLTree_H

struct AVLNode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;

AVLTree MakeEmpty(AVLTree t);
AVLTree Insert(int x, AVLTree t);

Position SingleRotateWithLeft(Position k2);
Position SingleRotateWithRight(Position k2);
Position DoubleRotateWithLeft(Position k3);
Position DoubleRotateWithRight(Position k3);

void Retrieve(Position p);

#endif