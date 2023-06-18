#include "Piece.hpp"
#include "Player.hpp"

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
  
  Move(Piece* piece, std::array<int, 2> newLocation) 
    : currentLocation(piece->getLocation()), newLocation(newLocation)
    {}
  
  bool operator==(const Move& other) const {
        return this->currentLocation == other.currentLocation 
               && this->newLocation == other.newLocation;
    }
};


#endif 