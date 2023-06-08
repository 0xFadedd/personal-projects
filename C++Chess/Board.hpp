#include <vector>
#include <iostream>
#include <string>
#include <array>
#include "Piece.hpp"
#include "Player.hpp"

#ifndef BOARD
#define BOARD

class Board
{
private:
  std::vector<Player> Players;

public:
  Player player1;
  Player player2;

  Board(Player player1, Player player2) : player1(player1), player2(player2)
  {
    Players.push_back(player1);
    Players.push_back(player2);
  }

  void display(){
  for (int row = 1; row <= 8; row++){
    for (int column = 1; column <= 8; column++){
      bool squareOccupied = false;
      for (Player player : Players) {
        for (Piece piece : player.pieces) {
          std::array<int, 2> pieceLocation = piece.getLocation();
          if (pieceLocation[0] == column && pieceLocation[1] == row) {
            std::cout << piece.getPieceSymbol() + " ";
            squareOccupied = true;
            break;
          }
        }
        if (squareOccupied) break;
      }
      if (!squareOccupied) {
        if((row + column)%2 == 0) {
          std::cout << "\u25A0" << " ";
        } else { std::cout << "\u25A1" << " "; }
      }
    }
    std::cout << std::endl;
  }

  
}
};

#endif
