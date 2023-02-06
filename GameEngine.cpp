#include <iostream>
using namespace std;
static const int ROWS = 10;
static const int COLUMNS = 11;
static int transitionTable[ROWS][COLUMNS] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 7, 5, 8, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int main() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            cout << transitionTable[r][c] << " ";
        }
        cout << "\n";
    }
    return 0;
}