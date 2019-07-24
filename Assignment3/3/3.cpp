#include <cstdio>
#include <set>
#include <map>

struct Point {
  int x;
  int y;

  Point() = default;
  Point(int x, int y) : x(x), y(y) {
  }

  const bool operator<(const Point &point) const {
    return x == point.x ? y < point.y : x < point.x;
  }

  const bool operator==(const Point &point) const {
    return x == point.x && y == point.y;
  }

  const bool operator!=(const Point &point) const {
    return x != point.x || y != point.y;
  }
};

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

// ==== Solution ====
inline bool InsideMaze(const Point &p, int row, int column) {
  return p.x >= 0 && p.y >= 0 && p.x < row && p.y < column;
}

inline int PointToHash(const Point &p, int column) {
  return p.x * column + p.y;
}

inline Point HashToPoint(int hash, int column) {
  return Point(hash / column, hash % column);
}

void Solve(const Point &start, const Point &target, bool **maze, int row, int column) {
  CircularQueue queue = CircularQueue(row * column + 1);
  std::set<Point> flags;
  std::map<Point, Point> prev_mapping;

  Push(&queue, PointToHash(start, column));
  flags.insert(start);

  Point deltas[] = {
      Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1),
      Point(1, 1), Point(1, -1), Point(-1, 1), Point(-1, -1),
  };

  bool solved = false;

  while (!IsEmpty(&queue)) {
    int cur_hash = Front(&queue);
    Point cur = HashToPoint(cur_hash, column);
    Pop(&queue);

    for (int i = 0; i < 8; ++i) {
      const Point &d = deltas[i];
      Point next = Point(cur.x + d.x, cur.y + d.y);
      if (InsideMaze(next, row, column)
          && maze[next.x][next.y]
          && flags.find(next) == flags.end()) {
        Push(&queue, PointToHash(next, column));
        flags.insert(next);
        prev_mapping[next] = cur;

        if (next == target) {
          solved = true;
          break;
        }
      }
    }

    if (solved) break;
  }

  if (solved) {
    for (Point p = target; p != start; p = prev_mapping[p]) {
      printf("(%d,%d)<-", p.x, p.y);
    }
    printf("(%d,%d)\n", start.x, start.y);
  } else {
    printf("no path.\n");
  }
}

int main() {
  /*
   * ==================== Input format ====================
   *  First line:
   *    starting point.
   *  Second line:
   *    target point.
   *  Third line:
   *    the number of row and column.
   *  4th to (3+row)-th lines:
   *    the maze, "1" represents a block.
   * ======================================================
   */
  freopen("input.txt", "r", stdin);

  int x;
  int y;
  scanf("%d", &x);
  scanf("%d", &y);
  Point start = Point(x, y);

  scanf("%d", &x);
  scanf("%d", &y);
  Point target = Point(x, y);

  int row;
  int column;
  scanf("%d", &row);
  scanf("%d", &column);

  bool **maze = new bool *[row];
  for (int i = 0; i < row; ++i) {
    maze[i] = new bool[column];
    for (int j = 0; j < column; ++j) {
      int v;
      scanf("%d", &v);
      maze[i][j] = v == 0;  // we regard false as block

      if (maze[i][j]) printf("0 ");
      else printf("1 ");
    }
    printf("\n");
  }

  Solve(start, target, maze, row, column);

  return 0;
}
