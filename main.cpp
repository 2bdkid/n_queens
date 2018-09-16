#include <iostream>
#include <stack>
#include <cmath>

/// represents a queen on a chessboard
struct Queen {
  Queen(int x, int y) : x(x), y(y) {}
  int x;
  int y;
};

/// returns true if the top queen is in conflict with any other queen
bool queens_conflict(std::stack<Queen> queens) {
  Queen top_queen = queens.top();
  queens.pop();

  while (!queens.empty()) {
    // two queens may not be in the same column
    // two queens share a diagonal if the slope between them = 1 or -1
    const bool same_column = queens.top().x == top_queen.x;
    const bool diagonal = std::abs(queens.top().y - top_queen.y) ==
                          std::abs(queens.top().x - top_queen.x);

    if (same_column || diagonal)
      // in conflict
      return true;

    queens.pop();
  }

  return false;
}

/// returns true if n queens will fit on an nxn chessboard
/// such that no two queens may attack the other
bool n_queens(int n) {
  std::stack<Queen> queens;
  queens.push(Queen(1, 1));

  int filled = 0;
  
  while (queens.size() != 0) {
    if (queens.top().x > n) {
      queens.pop();
      --filled;
      if (!queens.empty())
        queens.top().x += 1;
    } else if (queens_conflict(queens)) {
      queens.top().x += 1;
    } else {
      ++filled;
      if (filled == n) return true;
      Queen next_queen(1, queens.top().y + 1);
      queens.push(next_queen);
    }
  }

  // no solution found
  return false;
}

int main() {
  for (int i = 1; i < 100; ++i) {
    if (n_queens(i))
      std::cout << i << ": yes\n";
    else
      std::cout << i << ": no\n";
  }
}
