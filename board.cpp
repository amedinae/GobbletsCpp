#include "board.h"
#include <iostream>
#include "uioutils.h"
#include <vector>
#include <algorithm>

Board::Board() {
    std::fill(std::begin(p1Pieces), std::end(p1Pieces), NB_INITIAL_PIECES);
    std::fill(std::begin(p2Pieces), std::end(p2Pieces), NB_INITIAL_PIECES);
}

Board::~Board() {}

Cell& Board::getCellAt(int row, int column) {
    return state[row][column];
}

int* Board::getHousesOfPlayer(Player player) {
    return player == PLAYER_1 ? p1Pieces : p2Pieces;
}

Player Board::nextPlayer(Player currentPlayer) const {
    return currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}

Player Board::getPlaceHolder(int row, int column) {
    return getCellAt(row, column).peek().getOwner();
}

Size Board::getPieceSize(int row, int column) {
    return getCellAt(row, column).peek().getSize();
}

int Board::getNbPiecesInHouse(Player checkedPlayer, Size pieceSize) {
    return getHousesOfPlayer(checkedPlayer)[pieceSize-1];
}

bool Board::isValideTarget(int row, int column) {
    return row>=0 && row<DIMENSIONS && column>=0 && column<DIMENSIONS;
}

StatusEnum Board::placePiece(Player currentPlayer, Size pieceSize, int row, int column) {
    if (getNbPiecesInHouse(currentPlayer, pieceSize) == 0) {
        return NO_PIECE_IN_HOUSE;
    }

    if (!isValideTarget(row, column)) {
        return INVALID_TARGET;
    }
    Cell *targetCell = &getCellAt(row, column);
    Piece pieceToPlace = Piece(currentPlayer, pieceSize);
    if ((*targetCell).canPush(pieceToPlace)) {
        (*targetCell).push(pieceToPlace);
        getHousesOfPlayer(currentPlayer)[pieceSize-1]--;
        return OK;
    }
    return INVALID_TARGET;
}

StatusEnum Board::movePiece(int sourcerow, int sourceColumn, int targetrow, int targetColumn) {
    if (!isValideTarget(sourcerow, sourceColumn)) {
        return INVALID_SOURCE;
    }

    if (!isValideTarget(targetrow, targetColumn)) {
        return INVALID_TARGET;
    }

    Cell *sourceCell = &getCellAt(sourcerow, sourceColumn);
    Cell *targetCell = &getCellAt(targetrow, targetColumn);

    if(!(*sourceCell).canPop()) {
        return INVALID_SOURCE;
    }

    if ((*targetCell).canPush((*sourceCell).peek())) {
        (*targetCell).push((*sourceCell).pop());
        return OK;
    }
    return INVALID_TARGET;
}

Player Board::validateRow(int row) {
    Player winner = getCellAt(row,0).peek().getOwner();
    if (winner == NO_PLAYER) {
        return NO_PLAYER;
    }
    for (int i = 1; i < DIMENSIONS; i++) {
        if (getCellAt(row, i).peek().getOwner() != winner) {
            return NO_PLAYER;
        }
    }
    return winner;
}

Player Board::validateColumn(int column) {
    Player winner = getCellAt(0,column).peek().getOwner();
    if (winner == NO_PLAYER) {
        return NO_PLAYER;
    }
    for (int i = 1; i < DIMENSIONS; i++) {
        if (getCellAt(i, column).peek().getOwner() != winner) {
            return NO_PLAYER;
        }
    }
    return winner;
}

Player Board::validateDiagonals() {
    Player mainDiagonalWinner = getCellAt(0,0).peek().getOwner();
    Player secondaryDiagonalWinner = getCellAt(0,DIMENSIONS-1).peek().getOwner();
    for (int i = 1; i < DIMENSIONS; i++) {
        if (mainDiagonalWinner == NO_PLAYER && secondaryDiagonalWinner == NO_PLAYER) {
            return NO_PLAYER;
        }
        if (getCellAt(i, i).peek().getOwner() != mainDiagonalWinner) {
            mainDiagonalWinner = NO_PLAYER;
        }
        if (getCellAt(i, DIMENSIONS-1-i).peek().getOwner() != secondaryDiagonalWinner) {
            secondaryDiagonalWinner = NO_PLAYER;
        }
    }

    if (mainDiagonalWinner != NO_PLAYER) {
        return mainDiagonalWinner;
    }
    if (secondaryDiagonalWinner != NO_PLAYER) {
        return secondaryDiagonalWinner;
    }

    return NO_PLAYER;
}

Player Board::getWinner() {
    std::vector<Player> winners;
    winners.push_back(validateDiagonals());
    for (int i = 0; i < DIMENSIONS; i++) {
        winners.push_back(validateRow(i));
        winners.push_back(validateColumn(i));
    }
    winners.erase(std::remove_if(winners.begin(), winners.end(), [](Player p) { return p == NO_PLAYER; }), winners.end());
    if (std::equal(winners.begin() + 1, winners.end(), winners.begin())) {
        return winners[0];
    }
    return NO_PLAYER;
}

std::ostream& Board::printHouses(std::ostream& stream, Player player) {
    UiOutils::changeColorByPlayer(player);
    for (int i = SMALL; i <= LARGE; i++) {
        Size currentSize = Size(i);
        int nbPiecesInHouse = getNbPiecesInHouse(player,currentSize);
        for (int j = 0; j < NB_INITIAL_PIECES; j++) {
            if (j < nbPiecesInHouse) {
                Piece* pieceToPrint = new Piece(player,currentSize);
                stream << *pieceToPrint<<" ";
            } else {
                stream << "  ";
            }
        }
    }
    UiOutils::resetColor();
    return stream;
}

std::ostream& Board::printColoredPiece(std::ostream& stream, Piece piece) {
    UiOutils::changeColorByPlayer(piece.getOwner());
    stream << piece << " ";
    UiOutils::resetColor();
    return stream;
}

std::ostream& Board::printBoardRow(std::ostream& stream, int row) {
    stream << "|";
    for (int j = 0; j < DIMENSIONS; j++) {
        stream << " ";
        printColoredPiece(stream, getCellAt(row, j).peek());
        stream << "|";
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Board& board) {
    char levelSeparator[] = "+---+---+---+\n";
    printf("%s", levelSeparator);
    for (int i = 0; i < DIMENSIONS; i++) {
        board.printBoardRow(stream, i);
        stream<<"       ";
        if (i == 0) {
            stream<<"Contenu des maisons";
        } else {
            board.printHouses(stream, Player(i));
        }
        stream<<"\n";
        stream<<levelSeparator;
    }
    return stream;
}
