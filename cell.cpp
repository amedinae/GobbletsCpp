#include "cell.h"
#include <iostream>

Cell::Cell() : index(-1) {
    std::cout<<"Cell created"<<std::endl;
}

Cell::Cell(const Cell& other) {
    index = other.index;
    std::copy(std::begin(other.stack), std::end(other.stack), std::begin(stack));
    std::cout<<"Cell copied"<<std::endl;
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
    return stack[index];
}

Cell& Cell::operator=(const Cell &other) {
    index = other.index;
    std::copy(std::begin(other.stack), std::end(other.stack), std::begin(stack));
    return *this;
}