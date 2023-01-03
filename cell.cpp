#include "cell.h"
#include <iostream>

Cell::Cell() : index(-1) {}

Cell::Cell(const Cell& other) {
    index = other.index;
    std::copy(std::begin(other.stack), std::end(other.stack), std::begin(stack));
}

bool Cell::canPush(const Piece& piece) {
    if(index == -1) {
        return true;
    }
    return peek().getSize() < piece.getSize();
}

void Cell::push(const Piece& piece) {
    stack[++index] = piece;
}

bool Cell::canPop() {
    return index != -1;
}

Piece& Cell::pop() {
    return stack[index--];
}

Piece& Cell::peek() {
    if(index==-1){
        stack[0].reinitilize();
        return stack[0];
    }
    return stack[index];
}

Cell& Cell::operator=(const Cell &other) {
    index = other.index;
    std::copy(std::begin(other.stack), std::end(other.stack), std::begin(stack));
    return *this;
}
