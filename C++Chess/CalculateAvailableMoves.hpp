#include <array>
#include <string>
#include <map>
#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"

#ifndef AVAILABLEMOVES
#define AVAILABLEMOVES




  bool checkMove(std::array<int, 2> newLocation)
  {
    int dx = newLocation[0] - location[0];
    int dy = newLocation[1] - location[1];

    if ((newLocation[0] <= 0 || newLocation[1] <= 0) ||
        (newLocation[0] > 8 || newLocation[1] > 8))
    {
      switch (type)
      {
      case PieceType::Pawn:
        if (colour == PieceColour::White)
        {
          return dx == 0 && (dy == 1 || (dy == 2 && location[1] == 2));
        }
        else if (colour == PieceColour::Black)
        {
          return dx == 0 && (dy == -1 || (dy == -2 && location[1] == 7));
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
        return false;
      }
    }

    return false;
  }

 
#endif
