#include "Piece.hpp"
#include "Player.hpp"
#include "CalculateAvailableMoves.hpp"

#ifndef MOVE
#define MOVE

class Move {
  private:
    std::array<int, 2> currentLocation;
    std::array<int, 2> newLocation;
  public:
    std::array<int, 2> getCurrentLocation() {
      return currentLocation;
    }
    std::array<int, 2> getNewLocation() {
      return newLocation;
    }
  
  public:
   



    bool checkMove(std::array<int, 2> newLocation, Piece piece)
  {
    int dx = newLocation[0] - (piece.getLocation())[0];
    int dy = newLocation[1] - (piece.getLocation())[1];

    if ((newLocation[0] <= 0 || newLocation[1] <= 0) ||
        (newLocation[0] > 8 || newLocation[1] > 8))
    {
      switch (piece.getType())
      {
      case PieceType::Pawn:
        if (piece.getColour() == PieceColour::White)
        {
          return dx == 0 && (dy == 1 || (dy == 2 && (piece.getLocation())[1] == 2));
        }
        else if (piece.getColour() == PieceColour::Black)
        {
          return dx == 0 && (dy == -1 || (dy == -2 && (piece.getLocation())[1] == 7));
        }

      case PieceType::Knight:
        return (std::abs(dx) == 2 && std::abs(dy) == 1) || (std::abs(dx) == 1 && std::abs(dy) == 2);

      case PieceType::Bishop:
        return (std::abs(dx) == std::abs(dy));

      case PieceType::Rook:
        return (dx == 0 || dy == 0);

      case PieceType::Queen:
        return (dx == 0 || dy == 0) || (std::abs(dx) == std::abs(dy));

      case PieceType::King:
        return (std::abs(dx) <= 1 && std::abs(dy) <= 1);

      default:
        throw std::invalid_argument("Invalid Move");
        return false;
      }
    }

    return false;
  }

  Move(Piece* piece, std::array<int, 2> newLocation) 
    : currentLocation(piece->getLocation()), newLocation(newLocation)
    {
      this->checkMove(this->getNewLocation(), *piece);
    }
  
    
};


#endif 