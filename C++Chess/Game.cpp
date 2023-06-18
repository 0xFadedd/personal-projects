#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"
#include "StandardSetup.hpp"
#include "Move.hpp"
#include <vector>
#include <algorithm>

#ifndef GAME
#define GAME

class Game {
private:
    Player whitePlayer;
    Player blackPlayer;
    //std::vector<Piece> pieces;
    Board* board;
    Player* currentPlayer;
//accessors
public:
  std::array<Player, 2> getPlayers(){
    return {whitePlayer, blackPlayer};
  }
  
  Player* getCurrentPlayer() {
    return currentPlayer;
  }

  Player* getOpposition() {
    return &(((PieceColour)currentPlayer->colour == PieceColour::White) ? this->whitePlayer : this->blackPlayer);  
  }

//checkers
public:
  bool isCheck() {
    std::vector<Piece*> pieces = currentPlayer->pieces;
    Player* opposition = this->getOpposition();
    auto iterator = (std::find_if(pieces.begin(), pieces.end(), [](Piece* piece) {
      return piece->getType() == PieceType::King;
    }));
    Piece* currentPlayerKing;
    if(iterator != pieces.end()) {
      currentPlayerKing = *iterator;
    }
    for(Piece* piece : opposition->pieces){
      std::vector<Move> oppositionMoves = this->CalculateAvailableMoves(piece);
      std::cout << "OPPOSITION MOVES: " << oppositionMoves.size() << "\n";
      for(Move move : oppositionMoves) {
        if(move.getNewLocation() == currentPlayerKing->getLocation()) {
          return true;
        }
      }
    } 
  }

  bool isCheckMate() {

    
  }

  std::array<int, 2> convertMoveToLocation(std::string move) {
      int column = move[0] - 'a' + 1;
      int row = move[1] - '1' + 1;
      return {column, row};
    }
  
  bool spaceIsOccupiedByOpposition(std::array<int, 2> newLocation) {
    Piece* pieceAtLocation = this->board->getPieceAt(newLocation);
    return pieceAtLocation != nullptr && pieceAtLocation->getPieceColour() == (PieceColour)this->getOpposition()->colour;
  }

  bool spaceIsOccupiedByCurrentPlayer(std::array<int, 2> newLocation) {
    Piece* pieceAtLocation = this->board->getPieceAt(newLocation);
    return pieceAtLocation != nullptr && pieceAtLocation->getPieceColour() == (PieceColour)this->currentPlayer->colour;
  }



  bool canMoveThere(std::array<int, 2> newLocation) {
    bool newLocationOnTheBoard = newLocation[0] < 1 || newLocation[0] > 8 || newLocation[1] < 1 || newLocation[1] > 8;
    return !this->spaceIsOccupiedByCurrentPlayer(newLocation) && newLocationOnTheBoard;
  }

  bool containsMove(std::vector<Move> const& moves, Move const& move) {
    return std::find(moves.begin(), moves.end(), move) != moves.end();
  }

  std::vector<Move> CalculateAvailableMoves(Piece* piece) {
   
     
    std::vector<Move> availableMoves;
    std::array<int, 2> currentLocation = piece->getLocation();
    
    for (int row = 1; row <= 8; row++){
      for (int column = 1; column <= 8; column++) {
        int dx = row - currentLocation[0];
        int dy = column - currentLocation[1];
        try {
        switch (piece->getType()) {
          
        case PieceType::Pawn:
          if (dx == 0 && (dy == 1 || (dy == 2 && currentLocation[1] == 2))){
            availableMoves.push_back(Move(piece, {currentLocation[0] + dx, currentLocation[1] + dy}));
          }
          if ((dx == 1 && (dy == 1 || (dy == 2 && currentLocation[1] == 2)) 
            && this->spaceIsOccupiedByOpposition({currentLocation[0] + dx, currentLocation[1] + dy}))) {
            availableMoves.push_back(Move(piece, {currentLocation[0] + dx, currentLocation[1] + dy}));
          }
          break;
        case PieceType::Knight:
          if ((std::abs(dx) == 2 && std::abs(dy) == 1) || (std::abs(dx) == 1 && std::abs(dy) == 2)) {
            availableMoves.push_back(Move(piece, {currentLocation[0] + dx, currentLocation[1] + dy}));
          }
          break;
        case PieceType::Bishop:
          if (std::abs(dx) == std::abs(dy)) {
            availableMoves.push_back(Move(piece, {currentLocation[0] + dx, currentLocation[1] + dy}));
          }
          break;
        case PieceType::Rook:
          if (dx == 0 || dy == 0) {
            availableMoves.push_back(Move(piece, {currentLocation[0] + dx, currentLocation[1] + dy}));
          }
          break;
        case PieceType::Queen:
          if ((dx == 0 || dy == 0) || (std::abs(dx) == std::abs(dy))) {
            availableMoves.push_back(Move(piece, {currentLocation[0] + dx, currentLocation[1] + dy}));
          }
          break;
        case PieceType::King:
          if (std::abs(dx) <= 1 && std::abs(dy) <= 1) {
            availableMoves.push_back(Move(piece, {currentLocation[0] + dx, currentLocation[1] + dy}));
          }
          break;
        case PieceType::Empty:
          return availableMoves;
        default:
          return availableMoves;
        }
        }catch (const std::length_error& le) {
      std::cerr << "Length error: " << le.what() << '\n';}
      }  
    }
    
    return availableMoves;
      
  }  

public: //move

    void move(Piece* &piece, std::string newLocation) {
      std::vector<Move> availableMoves = this->CalculateAvailableMoves(piece);
      Move move = Move(piece, this->convertMoveToLocation(newLocation));
      if( this->containsMove(availableMoves, move) ) {
        Board* board = new Board(whitePlayer, blackPlayer);
        piece->setLocation(move.getNewLocation());
        board->display();
        delete board;
      }
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

    void startGame() {
      Board* board = new Board(whitePlayer, blackPlayer);
      currentPlayer = &whitePlayer;
      board->display();
      delete board;
    }

    void gameLoop() {
      startGame();
      while(!this->isCheck()) {
        std::string playerColour = currentPlayer->colour == Colour::White ? "White" : "Black";
        std::cout<< playerColour << " player it's your turn! \n";
      }
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
