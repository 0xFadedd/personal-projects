#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"
#include "StandardSetup.hpp"
#include "Move.hpp"
#include <vector>

#ifndef GAME
#define GAME

class Game {
private:
    Player whitePlayer;
    Player blackPlayer;
    //std::vector<Piece> pieces;
    Player* currentPlayer;
//accessors
public:
  std::array<Player, 2> getPlayers(){
    return {whitePlayer, blackPlayer};
  }
  
  Player* getCurrentPlayer() {
    return currentPlayer;
  }

//checkers
public:
  bool isCheck() {
      
    }

  bool isCheckMate() {
      
  }

//game setup
public:
    void setupPieces() {
      standardGameSetup(whitePlayer, blackPlayer);
    }

    void switchTurns() {
      if(currentPlayer == &whitePlayer) {
        currentPlayer = &blackPlayer;
      } else { currentPlayer = &whitePlayer; }
    }

    void move(Piece piece, Move move) {
      Board board = Board(whitePlayer, blackPlayer);
      if(move.checkMove(piece.convertMoveToLocation(move))) {
        piece = Piece(piece.getType(), piece.getColour(), piece.convertMoveToLocation(move));
      }
      board.display();
    }

    void startGame() {
      Board board = Board(whitePlayer, blackPlayer);
      currentPlayer = &whitePlayer;
      board.display();
    }

    void gameLoop() {
      startGame();

      while(isCheckMate());
    }

  //constructor 
  public:
    Game()
      : whitePlayer(Colour::White),
        blackPlayer(Colour::Black) {
      setupPieces();
    }
};

int main(){
  Game game = Game();
  game.gameLoop();

};
#endif
