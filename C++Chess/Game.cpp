#include <vector>
#include <iostream>
#include <string>
#include <array>
#include "Piece.hpp"
#include "Player.hpp"
#include "Board.hpp"

#ifndef GAME
#define GAME

class Game {
  private:
    Board board;
    std::vector<Player> Players;
  public:

    Game(Board board, std::vector<Player> gamePlayers) : board(board), Players(gamePlayers) {}

    
};

#endif
