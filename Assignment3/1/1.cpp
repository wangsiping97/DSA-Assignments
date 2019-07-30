#include <stdio.h>

struct List {
  typedef int value_type;
  typedef const value_type &const_reference;

  struct Node {
    const_reference val;
    Node *next = NULL;

    explicit Node(const_reference val) : val(val) {
    }
  };

  typedef Node *pointer;
  typedef const Node *const_pointer;

  int size = 0;
  Node *root;
  Node *tail;
};

List CreateList() {
  List list;
  list.root = new List::Node(0);
  list.tail = list.root;
  return list;
}

bool IsEmpty(List *list) {
  return list->size == 0;
}

int Size(List *list) {
  return list->size;
}

List::pointer Previous(List *list, List::const_pointer position) {
  List::pointer it = list->root;
  while (it->next != position) it = it->next;
  return it;
}

void Push(List *list, List::const_reference val) {
  list->tail->next = new List::Node(val);
  list->tail = list->tail->next;
  ++list->size;
}

void Pop(List *list) {
  if (list->size == 0) return;

  List::pointer new_tail = Previous(list, list->tail);

  delete list->tail;
  list->tail = new_tail;
  list->tail->next = NULL;

  --list->size;
}

List::pointer Insert(List *list, List::pointer position, List::const_reference val) {
  if (!position) return NULL;

  List::pointer node = new List::Node(val);
  node->next = position;
  List::pointer prev = Previous(list, position);
  prev->next = node;

  ++list->size;

  return node;
}

List::pointer Erase(List *list, List::pointer position) {
  if (!position) return NULL;

  List::pointer prev = Previous(list, position);
  prev->next = position->next;
  delete position;

  --list->size;

  return prev->next;
}

void Clear(List *list) {
  for (List::pointer i = list->root->next; i; i = i->next) {
    delete i;
  }

  list->root->next = NULL;
  list->tail = list->root;

  list->size = 0;
}

List::pointer Find(List *list, List::const_reference value) {
  for (List::pointer i = list->root->next; i; i = i->next) {
    if (value == i->val) return i;
  }

  return NULL;
}

void PrintDetails(List *list) {
  printf("List[size=%d] : ", Size(list));
  for (List::pointer i = list->root->next; i; i = i->next) {
    printf("%d ", i->val);
  }
  printf("\n");
}

int main() {
  List l = CreateList();
  printf("Constructed a new list.\n");

  printf("Is empty? Answer: ");
  if (IsEmpty(&l)) printf("true\n\n");
  else printf("false\n\n");

  Push(&l, 1);
  Push(&l, 2);
  Push(&l, 3);
  Push(&l, 4);
  Push(&l, 5);
  Push(&l, 6);
  Push(&l, 7);
  printf("Assigned 1 ~ 7.\n");
  PrintDetails(&l);
  printf("Is empty? Answer: ");
  if (IsEmpty(&l)) printf("true\n\n");
  else printf("false\n\n");

  Pop(&l);
  Pop(&l);
  printf("Popped two elements.\n");
  PrintDetails(&l);
  printf("\n");

  List::pointer it = Find(&l, 2);
  it = Insert(&l, it, 100);
  printf("Inserted 100 at position 2.\n");
  PrintDetails(&l);
  printf("\n");

  Erase(&l, it);
  printf("Erased 100.\n");
  PrintDetails(&l);
  printf("\n");

  Clear(&l);
  printf("Cleared.\n");
  PrintDetails(&l);
  printf("Is empty? Answer: ");
  if (IsEmpty(&l)) printf("true\n");
  else printf("false\n");

  return 0;
}
