#include <stdio.h>

struct CircularQueue {
  typedef int value_type;
  typedef value_type *pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;

  CircularQueue();
  explicit CircularQueue(int);

  const static int kMinCapacity = 5;

  int capacity;
  int size;
  pointer elements;
  int head;
  int tail;
};

CircularQueue::CircularQueue()
    : capacity(kMinCapacity), size(0), head(0), tail(0) {
  elements = new value_type[kMinCapacity];
}

CircularQueue::CircularQueue(int capacity)
    : capacity(capacity), size(0), head(0), tail(0) {
  elements = new value_type[capacity];
}

bool IsEmpty(CircularQueue *queue) {
  return queue->size == 0;
}

bool IsFull(CircularQueue *queue) {
  return queue->size == queue->capacity;
}

int Size(CircularQueue *queue) {
  return queue->size;
}

int Capacity(CircularQueue *queue) {
  return queue->capacity;
}

void Push(CircularQueue *queue, CircularQueue::const_reference val) {
  if (IsFull(queue)) {
    printf("Runtime Error: Queue is full.\n");
  } else {
    queue->elements[queue->tail] = val;
    queue->tail = (queue->tail + 1) % queue->capacity;
    ++queue->size;
  }
}

void Pop(CircularQueue *queue) {
  if (IsEmpty(queue)) {
    printf("Runtime Error: Queue is empty.\n");
  } else {
    queue->head = (queue->head + 1) % queue->capacity;
    --queue->size;
  }
}

CircularQueue::reference Front(CircularQueue *queue) {
  return queue->elements[queue->head];
}

CircularQueue::reference Back(CircularQueue *queue) {
  return queue->elements[(queue->tail + queue->capacity - 1) % queue->capacity];
}

void PrintDetails(CircularQueue *queue) {
  printf("CircularQueue[size=%d,capacity=%d] : ", Size(queue), Capacity(queue));
  for (int i = 0; i < queue->size; ++i) {
    printf("%d ", queue->elements[(queue->head + i) % queue->capacity]);
  }
  printf("\n");
}

int main() {
  CircularQueue q = CircularQueue(10);
  printf("Constructed a new circular queue.\n");

  printf("Is empty? Answer: ");
  if (IsEmpty(&q)) printf("true\n");
  else printf("false\n");
  printf("Is full? Answer: ");
  if (IsFull(&q)) printf("true\n");
  else printf("false\n");
  printf("\n");

  Push(&q, 1);
  Push(&q, 2);
  Push(&q, 3);
  Push(&q, 4);
  Push(&q, 5);
  Push(&q, 6);
  Push(&q, 7);
  printf("Pushed 1 ~ 7.\n");
  PrintDetails(&q);
  printf("Is empty? Answer: ");
  if (IsEmpty(&q)) printf("true\n");
  else printf("false\n");
  printf("\n");

  Pop(&q);
  Pop(&q);
  printf("Popped two elements.\n");
  PrintDetails(&q);
  printf("\n");

  Push(&q, 11);
  Push(&q, 12);
  Push(&q, 13);
  Push(&q, 14);
  Push(&q, 15);
  printf("Pushed 11 ~ 15.\n");
  PrintDetails(&q);
  printf("Is full? Answer: ");
  if (IsFull(&q)) printf("true\n");
  else printf("false\n");
  printf("The front number = %d\n", Front(&q));
  printf("The back number = %d\n", Back(&q));
  printf("\n");

  return 0;
}
