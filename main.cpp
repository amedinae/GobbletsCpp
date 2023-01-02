#include <iostream>
#include <string>
#include "board.h"
#include "uioutils.h"

int main()
{
    char action; int sourceRow, sourceCol, targetRow, targetCol;
    Size size; //inputs
    StatusEnum status = INVALID_ENTRY;

    Board* game = new Board();
    Player currentPlayer = PLAYER_1;
    do {
        UiOutils::printSeparator(std::cout);
        UiOutils::printPlayerTurn(std::cout, currentPlayer);
        std::cout << *game;
        action = UiOutils::selectAction(std::cout, std::cin);
        switch (action) {
            case '0':
                targetRow = UiOutils::selectPosition(std::cout, std::cin, "Sur quelle ligne voulez-vous jouer? ");
                targetCol = UiOutils::selectPosition(std::cout, std::cin, "Sur quelle colonne voulez-vous jouer? ");
                size = UiOutils::selectSize(std::cout, std::cin);
                status = game->placePiece(currentPlayer, size, targetRow, targetCol);
                UiOutils::printPlaceErrorMessageByStatus(std::cout, status);
                break;
            case '1':
                sourceRow = UiOutils::selectPosition(std::cout, std::cin, "De quelle ligne voulez-vous déplacer? ");
                sourceCol = UiOutils::selectPosition(std::cout, std::cin, "De quelle colonne voulez-vous déplacer? ");
                targetRow = UiOutils::selectPosition(std::cout, std::cin, "Sur quelle ligne voulez-vous jouer? ");
                targetCol = UiOutils::selectPosition(std::cout, std::cin, "Sur quelle colonne voulez-vous jouer? ");
                status = game->movePiece(sourceRow, sourceCol, targetRow, targetCol);
                UiOutils::printMoveErrorMessageByStatus(std::cout, status);
                break;
            case 'q':
                if(UiOutils::exitConfirmation(std::cout, std::cin)) {
                    UiOutils::printWinnerByQuit(std::cout,game->nextPlayer(currentPlayer),currentPlayer);
                    exit(0);
                }
            default:
                break;
        }
        if (status==OK) {
            currentPlayer = game->nextPlayer(currentPlayer);
        }
    }
    while(game->getWinner()==NO_PLAYER);
    std::cout << *game;
    return 0;
}

