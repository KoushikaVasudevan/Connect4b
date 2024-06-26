#include <iostream>
using namespace std;

const int rows = 6, cols = 7;

class GameManager {
private:
  char gameBoard[rows][cols] = {{' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' '}};

public:
  bool isDraw = false;

public:
  void displayGameBoard() {
    bool newRow = false;
    for (int row = 0; row < rows; row++) {
      newRow = true;
      for (int col = 0; col < cols; col++) {
        

        if ((col == cols - 1) && (newRow)) {
          cout << gameBoard[row][col];
          cout << "\n";
          newRow = false;
        } else {
          cout << gameBoard[row][col] << " "
               << "|"
               << " ";
        }
      }
    }
  }

  bool playTurn(string playerName, char marker) {
    int colInput;
    int row;
    bool isValidInput = false;

    do {
      cout << "\n"
           << playerName << " (" << marker << ") - Enter column number: ";
      cin >> colInput;

      if (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "\nInvalid input. Please enter a number between 0 and 6.\n";
        isValidInput = false;
        continue;
      }

      if ((0 <= colInput) && (colInput <= cols - 1)) {
        isValidInput = true;
        break;
      }

      isValidInput = false;
      cout << "\nInvalid input. Please enter a number between 0 and 6.\n";

    } while (!isValidInput);

    row = addPieceToGameBoard(colInput, marker);

    displayGameBoard();

    return (checkGame(row, colInput, marker));
  }

  int addPieceToGameBoard(int column, char marker) {
    int row = 0;

    for (int i = rows - 1; i >= 0; i--) {
      if (gameBoard[i][column] == ' ') {
        gameBoard[i][column] = marker;
        row = i;
        break;
      }
    }
    return row;
  }

  bool checkGame(int row, int column, char marker) {
    bool win = false;

    int r = row;
    int c = column;
    char m = marker;

    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}};

    for (int directionIndex = 0; directionIndex < 4; directionIndex++) {
      if (gameWinCheck(r, c, m, directions[directionIndex])) {
        win = true;
        break;
      }
    }

    if (!win) {
      isDraw = checkDraw();
    }

    return win;
  }

  bool checkDraw() {
    bool draw = true;

    for (int j = 0; j < cols; j++) {
      if (gameBoard[0][j] == ' ') {
        draw = false;
        break;
      }
    }
    return draw;
  }

  bool gameWinCheck(int r, int c, char m, int direction[]) {
    int startCell[2] = {r, c};
    int newStartCell[2];

    int endCell[2] = {r, c};
    int newEndCell[2];

    bool gameWin = false;
    int consecutiveCheck = 0;

    for (int i = 0; i < 4; i++) {
      newStartCell[0] = startCell[0] - direction[0];
      newStartCell[1] = startCell[1] - direction[1];

      if (newStartCell[0] < 0 || newStartCell[0] > rows - 1 ||
          newStartCell[1] < 0 || newStartCell[1] > cols - 1) {
        break;
      } else {
        startCell[0] = newStartCell[0];
        startCell[1] = newStartCell[1];
      }
    }

    for (int j = 0; j < 4; j++) {
      newEndCell[0] = endCell[0] + direction[0];
      newEndCell[1] = endCell[1] + direction[1];

      if (newEndCell[0] < 0 || newEndCell[0] > rows - 1 || newEndCell[1] < 0 ||
          newEndCell[1] > cols - 1) {
        break;
      } else {
        endCell[0] = newEndCell[0];
        endCell[1] = newEndCell[1];
      }
    }

    while (true) {
      if (gameBoard[startCell[0]][startCell[1]] == m) {
        consecutiveCheck++;
      } else {
        consecutiveCheck = 0;
      }
      if (consecutiveCheck == 4) {
        consecutiveCheck = 0;
        if (m == 'R') {
          cout << "\nPlayer1 (Red) wins!";
        } else if (m == 'B') {
          cout << "\nPlayer2 (Blue) wins!";
        }

        gameWin = true;
        break;
      }

      if (startCell[0] == endCell[0] && startCell[1] == endCell[1]) {
        break;
      }

      startCell[0] += direction[0];
      startCell[1] += direction[1];
    }
    return gameWin;
  }
};