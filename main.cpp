#include <iostream>
#include <string>
#include "board.h"
#include <stdio.h>
#include "uioutils.h"

int main()
{
    char action; int sourceRow, sourceCol, targetRow, targetCol;
    Size size; //inputs
    StatusEnum status = INVALID_ENTRY;
    Player winner = NO_PLAYER;

    Board* game = new Board();
    Player currentPlayer = PLAYER_1;
    std::ostream& outStream = std::cout;
    std::istream& inStream = std::cin;
    do {
        UiOutils::printSeparator(outStream);
        UiOutils::printPlayerTurn(outStream, currentPlayer);
        std::cout << *game;
        action = UiOutils::selectAction(outStream, inStream);
        switch (action) {
            case '0':
                targetRow = UiOutils::selectPosition(outStream, inStream, "Sur quelle ligne voulez-vous jouer? ");
                targetCol = UiOutils::selectPosition(outStream, inStream, "Sur quelle colonne voulez-vous jouer? ");
                size = UiOutils::selectSize(outStream, inStream);
                status = game->placePiece(currentPlayer, size, targetRow, targetCol);
                UiOutils::printPlaceErrorMessageByStatus(outStream, status);
                break;
            case '1':
                sourceRow = UiOutils::selectPosition(outStream, inStream, "De quelle ligne voulez-vous déplacer? ");
                sourceCol = UiOutils::selectPosition(outStream, inStream, "De quelle colonne voulez-vous déplacer? ");
                targetRow = UiOutils::selectPosition(outStream, inStream, "Sur quelle ligne voulez-vous jouer? ");
                targetCol = UiOutils::selectPosition(outStream, inStream, "Sur quelle colonne voulez-vous jouer? ");
                status = game->movePiece(sourceRow, sourceCol, targetRow, targetCol);
                UiOutils::printMoveErrorMessageByStatus(outStream, status);
                break;
            case 'q':
                if(UiOutils::exitConfirmation(outStream, inStream)) {
                    UiOutils::printWinnerByQuit(outStream,game->nextPlayer(currentPlayer),currentPlayer);
                    system("pause");
                    exit(0);
                }
            default:
                break;
        }
        if (status==OK) {
            currentPlayer = game->nextPlayer(currentPlayer);
            winner = game->getWinner();
        }
    }
    while(winner==NO_PLAYER);
    std::cout << *game;
    UiOutils::printWinner(outStream,winner);
    system("pause");
    return 0;
}

