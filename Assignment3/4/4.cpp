#include <stdio.h>
#include <set>

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

struct ArrayStack {
  typedef int value_type;
  typedef value_type *pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;

  int size;
  pointer elements;
};

ArrayStack CreateStack(int capacity) {
  ArrayStack stack = {0, new ArrayStack::value_type[capacity]};
  return stack;
}

bool IsEmpty(ArrayStack *stack) {
  return stack->size == 0;
}

void Push(ArrayStack *stack, ArrayStack::const_reference val) {
  stack->elements[stack->size] = val;
  ++stack->size;
}

void Pop(ArrayStack *stack) {
  --stack->size;
}

ArrayStack::reference Top(ArrayStack *stack) {
  return stack->elements[stack->size - 1];
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

bool Dfs(ArrayStack &stack,
         std::set<Point> &flags,
         const Point &target,
         bool **maze,
         int row,
         int column) {
  ArrayStack::reference cur_hash = Top(&stack);
  Point cur = HashToPoint(cur_hash, column);

  if (cur == target) {
    Pop(&stack);
    printf("(%d,%d)", target.x, target.y);
    while (!IsEmpty(&stack)) {
      ArrayStack::reference top_hash = Top(&stack);
      Point top = HashToPoint(top_hash, column);
      printf("<-(%d,%d)", top.x, top.y);
      Pop(&stack);
    }
    printf("\n");

    return true;
  }

  Point deltas[] = {
      Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1),
  };

  for (int i = 0; i < 4; ++i) {
    const Point &d = deltas[i];
    Point next = Point(cur.x + d.x, cur.y + d.y);
    if (InsideMaze(next, row, column)
        && maze[next.x][next.y]
        && flags.find(next) == flags.end()) {
      Push(&stack, PointToHash(next, column));
      flags.insert(next);
      if (Dfs(stack, flags, target, maze, row, column)) return true;
      else {
        Pop(&stack);
        flags.erase(next);
      }
    }
  }

  return false;
}

void Solve(const Point &start, const Point &target, bool **maze, int row, int column) {
  ArrayStack stack = CreateStack(row * column + 1);
  std::set<Point> flags;

  Push(&stack, PointToHash(start, column));
  flags.insert(start);

  if (!Dfs(stack, flags, target, maze, row, column)) printf("no path.\n");
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
