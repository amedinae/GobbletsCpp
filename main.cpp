#include <iostream>
#include <string>
#include "board.h"

using namespace std;

int main()
{
    char action; int l1; int c1; int l2; int c2; int s; //inputs
    StatusEnum status;
    Player winner;

    Board* game = new Board();
    Player currentPlayer = PLAYER_1;

    do{
        std::cout << std::endl << std::endl << std::endl;
        std::cout << *game << std::endl;

        winner = game->getWinner();

        if(winner != NO_PLAYER){
            switch(currentPlayer){
            case PLAYER_1:
            // A compléter

            case PLAYER_2:
            // A compléter

            default:
            ;// A compléter
            }
            return 0;
        }


        std::cout << "Action choice. 1: Place, 2: Move, q:Quit" << std::endl;
        std::cin >> action;

        // A compléter

        /* If an error occurs, print something and replay this turn.*/
        // A compléter


    } while(true);
    return 0;
}

