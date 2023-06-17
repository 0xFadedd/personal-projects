#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"
#include <vector>

#ifndef STANDARDSETUP
#define STANDARDSETUP

void standardGameSetup(Player& whitePlayer, Player& blackPlayer)
{
  // pawns
  for (int i = 0; i < 8; i++){
    Piece* pawnW = new Piece(PieceType::Pawn, PieceColour::White, std::array<int, 2>{i + 1, 2});
    whitePlayer.pieces.push_back(pawnW);
    Piece* pawnB = new Piece(PieceType::Pawn, PieceColour::Black, std::array<int, 2>{i + 1, 7});
    blackPlayer.pieces.push_back(pawnB);
  }

  // rooks
  Piece* rookW1 = new Piece(PieceType::Rook, PieceColour::White, std::array<int, 2>{1, 1});
  whitePlayer.pieces.push_back(rookW1);
  Piece* rookW2 = new Piece(PieceType::Rook, PieceColour::White, std::array<int, 2>{8, 1});
  whitePlayer.pieces.push_back(rookW2);

  Piece* rookB1 = new Piece(PieceType::Rook, PieceColour::Black, std::array<int, 2>{1, 8});
  blackPlayer.pieces.push_back(rookB1);
  Piece* rookB2 = new Piece(PieceType::Rook, PieceColour::Black, std::array<int, 2>{8, 8});
  blackPlayer.pieces.push_back(rookB2);

  // bishops
  Piece* bishopW1 = new Piece(PieceType::Bishop, PieceColour::White, std::array<int, 2>{2, 1});
  whitePlayer.pieces.push_back(bishopW1);
  Piece* bishopW2 = new Piece(PieceType::Bishop, PieceColour::White, std::array<int, 2>{7, 1});
  whitePlayer.pieces.push_back(bishopW2);

  Piece* bishopB1 = new Piece(PieceType::Bishop, PieceColour::Black, std::array<int, 2>{2, 8});
  blackPlayer.pieces.push_back(bishopB1);
  Piece* bishopB2 = new Piece(PieceType::Bishop, PieceColour::Black, std::array<int, 2>{7, 8});
  blackPlayer.pieces.push_back(bishopB2);

  // knights
  Piece* knightW1 = new Piece(PieceType::Knight, PieceColour::White, std::array<int, 2>{3, 1});
  whitePlayer.pieces.push_back(knightW1);
  Piece* knightW2 = new Piece(PieceType::Knight, PieceColour::White, std::array<int, 2>{6, 1});
  whitePlayer.pieces.push_back(knightW2);

  Piece* knightB1 = new Piece(PieceType::Knight, PieceColour::Black, std::array<int, 2>{3, 8});
  blackPlayer.pieces.push_back(knightB1);
  Piece* knightB2 = new Piece(PieceType::Knight, PieceColour::Black, std::array<int, 2>{6, 8});
  blackPlayer.pieces.push_back(knightB2);

  // queen
  Piece* queenW = new Piece(PieceType::Queen, PieceColour::White, std::array<int, 2>{4, 1});
  whitePlayer.pieces.push_back(queenW);
  Piece* queenB = new Piece(PieceType::Queen, PieceColour::Black, std::array<int, 2>{4, 8});
  blackPlayer.pieces.push_back(queenB);

  // queen
  Piece* kingW = new Piece(PieceType::King, PieceColour::White, std::array<int, 2>{5, 1});
  whitePlayer.pieces.push_back(kingW);
  Piece* kingB = new Piece(PieceType::King, PieceColour::Black, std::array<int, 2>{5, 8});
  blackPlayer.pieces.push_back(kingB);
};

#endif