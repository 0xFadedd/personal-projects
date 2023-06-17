#include <array>
#include <string>
#include <map>
#include "Board.hpp"

#ifndef PIECE
#define PIECE

enum class PieceType
{
  King,
  Queen,
  Rook,
  Bishop,
  Knight,
  Pawn,
  Empty
};

enum class PieceColour
{
  White,
  Black,
  Empty
};

class Piece
{
private:
  PieceType type;
  PieceColour colour;
  std::array<int, 2> location;
  std::vector<Move> availableMoves;

public:
  std::array<int, 2> getLocation()
  {
    return location;
  };

  
  std::string getPieceSymbol()
  {
    std::string base;
    if (colour == PieceColour::White)
      base = "\u2654";
    else if (colour == PieceColour::Black)
      base = "\u265A";
    else
      return " ";

    std::map<PieceType, std::string> white_symbols = {
        {PieceType::King, "\u2654"},
        {PieceType::Queen, "\u2655"},
        {PieceType::Rook, "\u2656"},
        {PieceType::Bishop, "\u2657"},
        {PieceType::Knight, "\u2658"},
        {PieceType::Pawn, "\u2659"}};

    std::map<PieceType, std::string> black_symbols = {
        {PieceType::King, "\u265A"},
        {PieceType::Queen, "\u265B"},
        {PieceType::Rook, "\u265C"},
        {PieceType::Bishop, "\u265D"},
        {PieceType::Knight, "\u265E"},
        {PieceType::Pawn, "\u265F"}};

    if (colour == PieceColour::White)
      return white_symbols[type];
    else if (colour == PieceColour::Black)
      return black_symbols[type];
    else
      return " ";
  }

  PieceType getType()
  {
    return type;
  }

  PieceColour getColour()
  {
    return colour;
  }

  bool canMoveThere(std::array<int, 2> newLocation) {
    bool newLocationOnTheBoard = newLocation[0] < 1 || newLocation[0] > 8 || newLocation[1] < 1 || newLocation[1] > 8;
    bool newLocationNotOccupied = getPieceAt(newLocation);
  }

  std::vector<Move> CalculateAvailableMoves() {
    // int dx = newLocation[0] - location[0];
    // int dy = newLocation[1] - location[1];

    // if ((newLocation[0] <= 0 || newLocation[1] <= 0) ||
    //     (newLocation[0] > 8 || newLocation[1] > 8))
    std::vector<Move> availableMoves;
    std::array<int, 2> currentLocation = this->getLocation();
    std::array<int, 2> availableMove;
    int direction = (this->getColour() == PieceColour::White) ? 1 : -1;
    {
      switch (this->getType())
      {
      case PieceType::Pawn:
        availableMoves.push_back(Move(this, {currentLocation[0],currentLocation[1]+direction}));

      case PieceType::Knight:
        availableMoves.push_back(Move(this, ))
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

  Piece(PieceType type, PieceColour colour, std::array<int, 2> location)
      : type(type), colour(colour), location(location) {}
};

#endif
