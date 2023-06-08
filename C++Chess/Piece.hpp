#include <array>
#include <string>

#ifndef PIECE
#define PIECE

enum class PieceType {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
    Empty
};

enum class PieceColour {
    White,
    Black,
    Empty
};

class Piece {
    private:
        PieceType type;
        PieceColour colour;
        std::array<int, 2> location;

    public:    
        std::array<int, 2> getLocaiton() {
            return location;
        };
        void setLocation(std::string position) {
            int column = position[0] - 'a' + 1;
            int row = position[1] - '1' + 1;
            location = {column, row};
        }

        Piece(PieceType type, PieceColour colour, std::array<int, 2> location) 
            : type(type), colour(colour), location(location) {}
};




#endif 