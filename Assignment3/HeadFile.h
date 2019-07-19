#ifndef HeadFile_H
#define HeadFile_H

struct node;
typedef struct node* NodePtr; // declare a pointer type
typedef NodePtr List; // declare the header
typedef NodePtr Position; // declare the position pointer 

List CreateList(int n); // function: to create a singly linked list
void DeleteNode(int x, List l); // function: to delete the first occurance of x from list l; assume use of a header node
void AddNode(int x, Position p, List l); // function: to add x in position p, list l

#endif /* HeadFile_H */