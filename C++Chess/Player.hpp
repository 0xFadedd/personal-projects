#include <vector>
#include "Piece.hpp"

#ifndef PLAYER
#define PLAYER

enum class Colour {
    White,
    Black,
    Empty
};

class Player {
    public:
        Colour colour;
        std::vector<Piece> pieces; 

        Player(Colour colour) : colour(colour) {}
};

#endif
