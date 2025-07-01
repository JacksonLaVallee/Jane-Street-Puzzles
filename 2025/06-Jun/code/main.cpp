#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using Clock = chrono::steady_clock;

class Tile {
public:
  int size;
  bool inuse;

  Tile(int setSize, bool setUse) : size(setSize), inuse(setUse) {}
};

class TileStack {
public:
  vector<Tile> tile_array;
  int tile_count;

  TileStack(int BigN) {
    tile_count = BigN * (BigN + 1) / 2;
    tile_array.reserve(tile_count);
    for (int sz = 1; sz <= BigN; ++sz) {
      for (int k = 0; k < sz; ++k) {
        tile_array.emplace_back(sz, false);
      }
    }
  }

  bool unused() const {
    for (const auto &t : tile_array) {
      if (!t.inuse)
        return true;
    }
    return false;
  }

  int almost_smallest(int tsize) const {
    bool seen_one = false;
    for (const auto &t : tile_array) {
      if (!t.inuse) {
        if (t.size != tsize) {
          return t.size;
        } else {
          if (seen_one) {
            return t.size;
          } else {
            seen_one = true;
          }
        }
      }
    }
    return 0;
  }
};

class BoardSquare {
public:
  static int board_size;
  static vector<vector<int>> matrix;

  static long long attempts;
  static long long solutions;
  static Clock::time_point startTime;

  static const string CSI_BEG;
  static const string CSI_END;
  static const string CSI_OFF;
  static const string CSI_NONE;
  static const string CSI_black;
  static const string CSI_red;
  static const string CSI_green;
  static const string CSI_blue;
  static const string CSI_yellow;
  static const string CSI_purple;
  static const string CSI_teal;
  static const string CSI_grey;

  static const vector<string> TILE_SYMBOLS;

  BoardSquare(int BigN) {
    board_size = BigN * (BigN + 1) / 2;
    matrix.assign(board_size, vector<int>(board_size, 0));
    testSquare1();
    attempts = 0;
    solutions = 0;
    startTime = Clock::now();
  }

  static void show() {
    for (int row = board_size - 1; row >= 0; --row) {
      for (int col = 0; col < board_size; ++col) {
        int tsize = matrix[row][col];
        if (tsize < (int)TILE_SYMBOLS.size()) {
          cout << TILE_SYMBOLS[tsize] << ' ';
        } else {
          cout << tsize << ' ';
        }
      }
      cout << '\n';
    }
    cout << '\n';
  }

  static bool canfit(int pos_row, int pos_col, int tsize) {
    if (pos_row + tsize > board_size || pos_col + tsize > board_size) {
      return false;
    }
    for (int r = pos_row; r < pos_row + tsize; ++r) {
      for (int c = pos_col; c < pos_col + tsize; ++c) {
        if (matrix[r][c] != 0)
          return false;
      }
    }
    return true;
  }

  static void addtile(int pos_row, int pos_col, int tsize) {
    for (int r = pos_row; r < pos_row + tsize; ++r) {
      for (int c = pos_col; c < pos_col + tsize; ++c) {
        matrix[r][c] = tsize;
      }
    }
  }

  static void deltile(int pos_row, int pos_col, int tsize) {
    for (int r = pos_row; r < pos_row + tsize; ++r) {
      for (int c = pos_col; c < pos_col + tsize; ++c) {
        matrix[r][c] = 0;
      }
    }
  }

  void testSquare1() {
    addtile(0, 0, 9);
    addtile(9, 0, 8);
    addtile(17, 0, 8);
    addtile(25, 0, 7);
    addtile(32, 0, 7);
    addtile(39, 0, 4);
    addtile(43, 0, 2);
    // addtile(9, 0, 9);
    // addtile(18, 0, 9);
    // addtile(27, 0, 9);
    // addtile(36, 0, 9);
    // addtile(0, 15, 9);
    // addtile(0, 24, 9);
    // addtile(13, 29, 9);
    // addtile(29, 9, 8);
    // addtile(37, 9, 8);
    // addtile(30, 29, 8);
    // addtile(30, 37, 8);
    // addtile(22, 37, 8);
    // addtile(0, 37, 8);
    // addtile(8, 38, 7);
    // addtile(15, 38, 7);
    // addtile(38, 31, 7);
    // addtile(38, 38, 7);
    // addtile(13, 9, 6);
    // addtile(19, 9, 5);
    // addtile(24, 9, 5);
    // addtile(8, 33, 5);
    // addtile(0, 11, 4);
    // addtile(0, 33, 4);
    // addtile(4, 33, 4);
    // addtile(4, 12, 3);
  }
};

int BoardSquare::board_size = 0;
vector<vector<int>> BoardSquare::matrix;
long long BoardSquare::attempts = 0;
long long BoardSquare::solutions = 0;
Clock::time_point BoardSquare::startTime;

const string BoardSquare::CSI_BEG = "\u001B[";
const string BoardSquare::CSI_END = "m";
const string BoardSquare::CSI_OFF = BoardSquare::CSI_BEG + "0m";
const string BoardSquare::CSI_NONE = "";
const string BoardSquare::CSI_black =
    BoardSquare::CSI_BEG + "0;30;40" + BoardSquare::CSI_END;
const string BoardSquare::CSI_red =
    BoardSquare::CSI_BEG + "0;30;41" + BoardSquare::CSI_END;
const string BoardSquare::CSI_green =
    BoardSquare::CSI_BEG + "0;30;42" + BoardSquare::CSI_END;
const string BoardSquare::CSI_blue =
    BoardSquare::CSI_BEG + "0;30;44" + BoardSquare::CSI_END;
const string BoardSquare::CSI_yellow =
    BoardSquare::CSI_BEG + "0;30;43" + BoardSquare::CSI_END;
const string BoardSquare::CSI_purple =
    BoardSquare::CSI_BEG + "0;30;45" + BoardSquare::CSI_END;
const string BoardSquare::CSI_teal =
    BoardSquare::CSI_BEG + "0;30;46" + BoardSquare::CSI_END;
const string BoardSquare::CSI_grey =
    BoardSquare::CSI_BEG + "0;30;47" + BoardSquare::CSI_END;

const vector<string> BoardSquare::TILE_SYMBOLS = {
    ".", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C",
    "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};

void go_deep(BoardSquare &board, TileStack &tiles, int start_row,
             int start_col) {
  BoardSquare::attempts++;

  bool init_loop = true;
  for (int row = start_row; row < BoardSquare::board_size; ++row) {
    for (int col = 0; col < BoardSquare::board_size; ++col) {
      if (init_loop) {
        col = start_col;
        init_loop = false;
      }
      if (BoardSquare::matrix[row][col] == 0) {
        int last_tile_used = 0;
        for (int idx = 0; idx < tiles.tile_count; ++idx) {
          if (idx == 0 && (row < 2 || row > BoardSquare::board_size - 3 ||
                           col < 2 || col > BoardSquare::board_size - 3)) {
            continue;
          }
          Tile &t = tiles.tile_array[idx];
          if (!t.inuse && t.size != last_tile_used) {
            last_tile_used = t.size;

            if (last_tile_used == 1) {
              if (row + 1 < BoardSquare::board_size && col - 1 >= 0 &&
                  BoardSquare::matrix[row + 1][col - 1] != 0) {
                if ((col + 1 < BoardSquare::board_size &&
                     BoardSquare::matrix[row][col + 1] == 0) ||
                    (col + 1 < BoardSquare::board_size &&
                     row + 1 < BoardSquare::board_size &&
                     BoardSquare::matrix[row + 1][col + 1] != 0)) {
                  continue;
                }
              } else {
                if ((col + 1 < BoardSquare::board_size &&
                     BoardSquare::matrix[row][col + 1] == 0) &&
                    (col + 2 < BoardSquare::board_size &&
                     BoardSquare::matrix[row][col + 2] != 0)) {
                  continue;
                }
              }
            }

            if (!BoardSquare::canfit(row, col, last_tile_used)) {
              return;
            } else {
              int top_gap = BoardSquare::board_size - (row + last_tile_used);
              int smallest_tile = tiles.almost_smallest(last_tile_used);
              if (top_gap > 0) {
                if (top_gap == 1 || smallest_tile > top_gap) {
                  continue;
                }
              }
              int right_gap = BoardSquare::board_size - (col + last_tile_used);
              if (right_gap > 0) {
                if (right_gap == 1 || smallest_tile > right_gap) {
                  continue;
                }
              }

              t.inuse = true;
              BoardSquare::addtile(row, col, last_tile_used);

              if (tiles.unused()) {
                go_deep(board, tiles, row, col);
              } else {
                BoardSquare::solutions++;
                auto now = Clock::now();
                auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(
                                      now - BoardSquare::startTime)
                                      .count();
                double elapsed_min = elapsed_ms / (1000.0 * 60.0);
                cout << "Solution #" << BoardSquare::solutions
                     << " found at configuration #" << BoardSquare::attempts
                     << " after " << fixed << setprecision(2) << elapsed_min
                     << " minutes\n";
                BoardSquare::show();
              }

              BoardSquare::deltile(row, col, last_tile_used);
              t.inuse = false;
            }
          }
        }
        return;
      }
    }
  }
}



int main() {
  int BigN = 9;
  TileStack tilesTop(BigN);
  BoardSquare boardTop(BigN);

  cout << "Solution for N = " << BigN << "\n\n";
  go_deep(boardTop, tilesTop, 0, 0);

  auto now = Clock::now();
  auto elapsed_ms =
      chrono::duration_cast<chrono::milliseconds>(now - BoardSquare::startTime)
          .count();
  double elapsed_min = elapsed_ms / (1000.0 * 60.0);
  cout << "Tried " << BoardSquare::attempts << " configurations in " << fixed
       << setprecision(2) << elapsed_min << " minutes\n";

  return 0;
}
