#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"
#include "StandardSetup.hpp"
#include "Move.hpp"
#include <vector>
#include <algorithm>

#ifndef GAME
#define GAME

/**
 * @class Game
 * @brief This class represents a Chess game.
 */
class Game
{
private:
  Player whitePlayer;    ///< Represents the player with white pieces.
  Player blackPlayer;    ///< Represents the player with black pieces.
  Board *board;          ///< Represents the game board.
  Player *currentPlayer; ///< Represents the player whose turn it currently is.

public:
  /// @brief Retrieves both players in the game.
  std::array<Player, 2> getPlayers()
  {
    return {whitePlayer, blackPlayer};
  }

  /// @brief Gets the current player whose turn it is.
  Player *getCurrentPlayer()
  {
    return currentPlayer;
  }

  /// @brief Gets the opponent of the current player.
  Player *getOpposition()
  {
    return &(((PieceColour)currentPlayer->colour == PieceColour::White) ? this->whitePlayer : this->blackPlayer);
  }

  /**
   *
   *
   *            CALCULATING AVAILABLE MOVES AND CHECKERS
   *
   *
   */

public:
  /// @brief Checks if the current player's king is under threat.
  bool isCheck()
  {
    std::vector<Piece *> pieces = currentPlayer->pieces;
    Player *opposition = this->getOpposition();
    auto iterator = (std::find_if(pieces.begin(), pieces.end(), [](Piece *piece)
                                  { return piece->getType() == PieceType::King; }));
    Piece *currentPlayerKing;
    if (iterator != pieces.end())
    {
      currentPlayerKing = *iterator;
    }
    for (Piece *piece : opposition->pieces)
    {
      std::vector<Move> oppositionMoves = this->CalculateAvailableMoves(piece);
      std::cout << "OPPOSITION MOVES: " << oppositionMoves.size() << "\n";
      for (Move move : oppositionMoves)
      {
        if (move.getNewLocation() == currentPlayerKing->getLocation())
        {
          return true;
        }
      }
    }
  }

  /// @brief Checks if the current player is in a checkmate position.
  bool isCheckMate()
  {
  }

  /**
   * @brief Converts a move (in string format) to its location coordinates on the board.
   * @param move The move string.
   * @return The location in row, column format.
   */
  std::array<int, 2> convertMoveToLocation(std::string move)
  {
    int column = move[0] - 'a' + 1;
    int row = move[1] - '1' + 1;
    return {column, row};
  }

  /// @brief Determines if a space is occupied by an opponent's piece.
  bool spaceIsOccupiedByOpposition(std::array<int, 2> newLocation)
  {
    Piece *pieceAtLocation = this->board->getPieceAt(newLocation);
    return pieceAtLocation != nullptr && pieceAtLocation->getPieceColour() == (PieceColour)this->getOpposition()->colour;
  }

  /// @brief Determines if a space is occupied by the current player's piece.
  bool spaceIsOccupiedByCurrentPlayer(std::array<int, 2> newLocation)
  {
    Piece *pieceAtLocation = this->board->getPieceAt(newLocation);
    return pieceAtLocation != nullptr && pieceAtLocation->getPieceColour() == (PieceColour)this->currentPlayer->colour;
  }

  /// @brief Determines if a piece can move to the given location.
  bool canMoveThere(std::array<int, 2> newLocation)
  {
    bool newLocationOnTheBoard = newLocation[0] < 1 || newLocation[0] > 8 || newLocation[1] < 1 || newLocation[1] > 8;
    return !this->spaceIsOccupiedByCurrentPlayer(newLocation) && newLocationOnTheBoard;
  }

  /**
   * @brief Determines if the list of moves contains a specific move.
   * @param moves The list of available moves.
   * @param move The specific move to check for.
   * @return True if the move is found, false otherwise.
   */
  bool containsMove(std::vector<Move> const &moves, Move const &move)
  {
    return std::find(moves.begin(), moves.end(), move) != moves.end();
  }

  /// @brief Gets any piece that lies in the path of the current piece's move.
  std::pair<Piece *, std::array<int, 2>> getPieceOnPath(std::array<int, 2> currentLocation, std::array<int, 2> newLocation)
  {
    Piece *piece;
    for (int row = 1; row <= 8 - newLocation[0]; row++)
    {
      for (int column = 1; column <= 8 - newLocation[1]; column++)
      {
        std::array<int, 2> locationToCheck = {currentLocation[0] + row, currentLocation[1] + column};
        piece = this->board->getPieceAt(locationToCheck);
        if (piece != nullptr)
        {
          return std::make_pair(piece, locationToCheck);
        }
        else
        {
          continue;
        }
      }
    }
  }

  /**
   * @brief Populates the list of available moves based on the movement of a piece.
   * @param availableMoves The list of available moves to populate.
   * @param piece The piece being moved.
   * @param dx The change in the x-coordinate.
   * @param dy The change in the y-coordinate.
   * @param currentLocation The current location of the piece.
   * @param newLocation The target location of the move.
   */
  void addMoves(std::vector<Move> &availableMoves, Piece *piece, int dx, int dy, std::array<int, 2> currentLocation, std::array<int, 2> newLocation)
  {
    Piece *pieceOnPath = this->getPieceOnPath(currentLocation, newLocation).first;
    switch (piece->getType())
    {
      if (pieceOnPath != nullptr)
      {
        if (pieceOnPath->getPieceColour() == (PieceColour)this->getCurrentPlayer()->colour)
        {
          break;
        }
        if (pieceOnPath->getPieceColour() == (PieceColour)this->getOpposition()->colour)
        {
        }
      }

    case PieceType::Pawn:
      if (dx == 0 && (dy == 1 || (dy == 2 && currentLocation[1] == 2)))
      {
        availableMoves.push_back(Move(piece, newLocation));
      }
      if ((dx == 1 && (dy == 1 || (dy == 2 && currentLocation[1] == 2)) && this->spaceIsOccupiedByOpposition(newLocation)))
      {
        availableMoves.push_back(Move(piece, newLocation));
      }
      break;
    case PieceType::Knight:
      if ((std::abs(dx) == 2 && std::abs(dy) == 1) || (std::abs(dx) == 1 && std::abs(dy) == 2))
      {
        availableMoves.push_back(Move(piece, newLocation));
      }
      break;
    case PieceType::Bishop:
      if (std::abs(dx) == std::abs(dy))
      {
        availableMoves.push_back(Move(piece, newLocation));
      }
      break;
    case PieceType::Rook:
      if (dx == 0 || dy == 0)
      {
        availableMoves.push_back(Move(piece, newLocation));
      }
      break;
    case PieceType::Queen:
      if ((dx == 0 || dy == 0) || (std::abs(dx) == std::abs(dy)))
      {
        availableMoves.push_back(Move(piece, newLocation));
      }
      break;
    case PieceType::King:
      if (!this->isCheck() && (std::abs(dx) <= 1 && std::abs(dy) <= 1))
      {
        availableMoves.push_back(Move(piece, newLocation));
      }
      break;
    case PieceType::Empty:
      break;
    default:
      break;
    }
  }

  /**
   * need to work on checking if opposition piece is in path to new location -> then needs to default to add that location as a move
   * then need to work on being able to take opposition pieces
   * need to finish game loop by completing is check mate
   * need to make sure calculate available moves is run at start of each turn to check for check mate/ check and to calculate available moves for the coming turn. this makes sure that when someone makes a turn, the current player will then switch and then calculate for check
   */
  /**
   * @brief Calculates all possible moves for a given piece.
   * @param piece The piece for which the moves are being calculated.
   * @return A list of available moves for the piece.
   */
  std::vector<Move> CalculateAvailableMoves(Piece *piece)
  {
    std::vector<Move> availableMoves;
    std::array<int, 2> currentLocation = piece->getLocation();

    for (int row = 1; row <= 8; row++)
    {
      for (int column = 1; column <= 8; column++)
      {
        int dx = row - currentLocation[0];
        int dy = column - currentLocation[1];
        if (dx == 0 && dy == 0)
        {
          std::cerr << "Length error: new location is current location." << '\n';
        }
        try
        {
          this->addMoves(availableMoves, piece, dx, dy, currentLocation, {{currentLocation[0] + dx, currentLocation[1] + dy}});
        }
        catch (const std::length_error &le)
        {
          std::cerr << "Length error: " << le.what() << '\n';
        }
      }
    }

    return availableMoves;
  }

public: // move
  /**
   * @brief Moves a piece to a new location if the move is valid.
   * @param piece The piece being moved.
   * @param newLocation The target location in string format (e.g., "e4").
   */
  void move(Piece *&piece, std::string newLocation)
  {
    std::vector<Move> availableMoves = this->CalculateAvailableMoves(piece);
    Move move = Move(piece, this->convertMoveToLocation(newLocation));
    if (this->containsMove(availableMoves, move))
    {
      Board *board = new Board(whitePlayer, blackPlayer);
      piece->setLocation(move.getNewLocation());
      board->display();
      delete board;
    }
  }

  /**
   *
   *
   *              GAME LOOPS AND SETUP
   *
   *
   */

public:
  /// @brief Sets up the chess board with the standard initial piece positions.
  void setupPieces()
  {
    standardGameSetup(whitePlayer, blackPlayer);
  }

  /// @brief Switches the turn to the next player.
  void switchTurns()
  {
    if (currentPlayer == &whitePlayer)
    {
      currentPlayer = &blackPlayer;
    }
    else
    {
      currentPlayer = &whitePlayer;
    }
  }

  /// @brief Initiates the chess game, displaying the initial board.
  void startGame()
  {
    Board *board = new Board(whitePlayer, blackPlayer);
    currentPlayer = &whitePlayer;
    board->display();
    delete board;
  }

  /// @brief Runs the main game loop, handling player turns.
  void gameLoop()
  {
    startGame();
    while (!this->isCheck())
    {
      std::string playerColour = currentPlayer->colour == Colour::White ? "White" : "Black";
      std::cout << playerColour << " player it's your turn! \n";
    }
  }

  // constructor
public:
  /// @brief Default constructor for the Game class.
  Game()
      : whitePlayer(Colour::White),
        blackPlayer(Colour::Black)
  {
    setupPieces();
  }
};

/**
 * @brief The main entry point for the chess game.
 */
int main()
{
  Game game = Game();
  game.gameLoop();
};
#endif
