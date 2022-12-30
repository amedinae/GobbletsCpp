#include "piece.h"
#include <iostream>

Piece::Piece() : owner(NO_PLAYER), size(NONE) {
    std::cout<<"Piece created"<<std::endl;
}

Piece::Piece(Player owner, Size size) : owner(owner), size(size) {
    std::cout<<"Piece created"<<std::endl;
}

Piece::Piece(const Piece& other) : owner(other.owner), size(other.size) {
    std::cout<<"Piece copied"<<std::endl;
}

Player Piece::getOwner() const {
    return owner;
}

Size Piece::getSize() const {
    return size;
}

Piece& Piece::operator=(const Piece& other) {
    owner = other.owner;
    size = other.size;
    return *this;
}