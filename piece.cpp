#include "piece.h"
#include "config.h"
#include <iostream>

Piece::Piece() : owner(NO_PLAYER), size(NONE) {}

Piece::Piece(Player owner, Size size) : owner(owner), size(size) {}

Piece::Piece(const Piece& other) : owner(other.owner), size(other.size) {}

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

std::ostream& operator<<(std::ostream& stream, const Piece& piece) {
    char empty = ' ';
    switch (piece.getOwner()) {
    case NO_PLAYER:
        return stream << empty;
    case PLAYER_1:
        switch (piece.getSize()) {
            case NONE:
                return stream << empty;
            case SMALL:
                return stream << SMALLP1;
            case MEDIUM:
                return stream << MEDIUMP1;
            case LARGE:
                return stream << LARGEP1;
        }
    case PLAYER_2:
        switch (piece.getSize()) {
            case NONE:
                return stream << empty;
            case SMALL:
                return stream << SMALLP2;
            case MEDIUM:
                return stream << MEDIUMP2;
            case LARGE:
                return stream << LARGEP2;
        }  
    }
    return stream;
}
