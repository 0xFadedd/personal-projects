#include <array>
#include <string>
#include <map>

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

public:
  std::array<int, 2> getLocation()
  {
    return location;
  };

  std::array<int, 2> convertMoveToLocation(Move move)
  {
    int column = move[0] - 'a' + 1;
    int row = move[1] - '1' + 1;
    return {column, row};
  }

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


  Piece(PieceType type, PieceColour colour, std::array<int, 2> location)
      : type(type), colour(colour), location(location) {}
};

#endif
