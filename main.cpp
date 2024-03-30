#include <iostream>
#include "gameManager.h"
using namespace std;

int main() {
  bool gameWin = false;

  string playerName = "player1";
  char marker = 'R';

  GameManager game;

  cout << "Welcome to Connect 4!\n\n";
  cout << "\nHow to play\n\n1.Connect 4 pieces "
          "horizontally/vertically/diagonally to win\n2.Player1 is Red, "
          "Player2 is Blue\n3.Game is a draw when the board is filled\n\n";
  game.displayGameBoard();

  do {
    gameWin = game.playTurn(playerName, marker);

    if (gameWin == true) {
      break;
    }

    if (game.isDraw == true) {
      cout << "\nThe game is a draw";
      break;
    }

    if (marker == 'R') 
    {
      playerName = "player2";
      marker = 'B';
    } 
    else if (marker == 'B') 
    {
      playerName = "player1";
      marker = 'R';
    }
  } while (!gameWin);

  cout << "\nGame Over";
}