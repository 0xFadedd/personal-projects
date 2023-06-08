#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"
#include "StandardSetup.hpp"
#include <vector>

#ifndef GAME
#define GAME

class Game {
private:
    Player whitePlayer;
    Player blackPlayer;
    //std::vector<Piece> pieces;

public:
    Game()
        : whitePlayer(Colour::White),
          blackPlayer(Colour::Black) {
        setupPieces();
    }

    void setupPieces() {
      standardGameSetup(whitePlayer, blackPlayer);
    }

    void move(Piece piece, std::string newLocation) {
      Board board = Board(whitePlayer, blackPlayer);
      if(piece.checkMove(piece.convertMoveToLocation(newLocation))) {
        piece = Piece(piece.getType(), piece.getColour(), piece.convertMoveToLocation(newLocation));
      }
      board.display();
    }

    void startGame() {
      Board board = Board(whitePlayer, blackPlayer);
      board.display();
    }
};

int main(){
  Game game = Game();
  game.startGame();
};
#endif
