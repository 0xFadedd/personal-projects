#include <vector>
#include <iostream>
#include <string>
#include <array>
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

  Piece* getPieceAt(std::array<int, 2> locationToCheck) {
  for (Player player : Players) {
    for (Piece* piece : player.pieces) {
      std::array<int, 2> pieceLocation = piece->getLocation();
      if (pieceLocation[0] == locationToCheck[0] && pieceLocation[1] == locationToCheck[1]) {
        return piece;
      }
    }
  }
  return nullptr;  
}

  void display(){
    for (int row = 1; row <= 8; row++){
      for (int column = 1; column <= 8; column++){
        bool squareOccupied = false;
        Piece* piece = this->getPieceAt({column, row});
        if(piece != nullptr) {
          std::cout << piece->getPieceSymbol() + " ";
          squareOccupied = true;
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
