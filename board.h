#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "cell.h"
#include "playerEnum.h"
#include "config.h"
#include "statusEnum.h"
#include <iostream>

class Board
{
    private:
        Cell state[DIMENSIONS][DIMENSIONS];
        int p1Pieces[NB_SIZE];
        int p2Pieces[NB_SIZE];

        Cell& getCellAt(int row, int column);
        int* getHousesOfPlayer(Player player);
        bool isValideTarget(int row, int column);
        Player validateRow(int row);
        Player validateColumn(int column);
        Player validateDiagonals();
        std::ostream& printColoredPiece(std::ostream& stream, Piece piece);
        std::ostream& printBoardRow(std::ostream& stream, int row);
    public:
        Board();
        Board(const Board& other);
        ~Board();

        Player nextPlayer(Player currentPlayer) const;
        Player getPlaceHolder(int row, int column);
        Size getPieceSize(int row, int column);
        int getNbPiecesInHouse(Player checkedPlayer, Size pieceSize);

        StatusEnum placePiece(Player currentPlayer, Size pieceSize, int row, int column);
        StatusEnum movePiece(int sourcerow, int sourceColumn, int targetrow, int targetColumn);

        Player getWinner();

        std::ostream& printHouses(std::ostream& stream, Player player);
        friend std::ostream& operator<<(std::ostream& stream, Board& board);
};

#endif // BOARD_H
