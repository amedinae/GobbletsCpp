#ifndef UIOUTILS_H
#define UIOUTILS_H

#include <iostream>
#include <string>
#include "piece.h"
#include "playerEnum.h"
#include "statusEnum.h"

class UiOutils
{
private:
    UiOutils();
    static int charToInt(char c);
    static char getValidChar(std::ostream& out, std::istream& in, const std::string message, const char *validChars);
    static void changeColorToRed();
    static std::ostream& printInputErrorMessage(std::ostream& stream);
public:
    static void changeColorByPlayer(Player player);
    static void resetColor();
    static std::ostream& printSeparator(std::ostream& stream);
    static std::ostream& printPlayerTurn(std::ostream& stream, Player player);
    static int selectPosition(std::ostream& out, std::istream& in, const std::string message);
    static char selectAction(std::ostream& out, std::istream& in);
    static Size selectSize(std::ostream& out, std::istream& in);
    static bool exitConfirmation(std::ostream& out, std::istream& in);
    static std::ostream& printPlaceErrorMessageByStatus(std::ostream& out, StatusEnum status);
    static std::ostream& printMoveErrorMessageByStatus(std::ostream& out, StatusEnum status);
    static std::ostream& printWinnerByQuit(std::ostream& out, Player winner, Player looser);
    static std::ostream& printWinner(std::ostream& out, Player winner);
};

#endif // UIOUTILS_H
