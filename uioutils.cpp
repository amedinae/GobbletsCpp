#include "uioutils.h"
#include <iostream>
#include "config.h"
#include "piece.h"
#include "statusEnum.h"
#include <string>
#include <cstring>
#include <cctype>
#include <iostream>
#include <windows.h>

void UiOutils::changeColorByPlayer(Player player) {
    if (!USE_COLORS){
        return;
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (player) {
    case NO_PLAYER:
        resetColor();
        break;
    case PLAYER_1:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN );   // bold yellow
        break;
    case PLAYER_2:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // bold blue
        break;
    }
}

void UiOutils::changeColorToRed() {
    if (!USE_COLORS){
        return;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
}

void UiOutils::resetColor() {
    if (!USE_COLORS){
        return;
    }
    int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
}

std::ostream& UiOutils::printSeparator(std::ostream& stream) {
    stream << "-------------------------------------\n";
    return stream;
}

std::ostream& UiOutils::printPlayerTurn(std::ostream& stream, Player player) {
    changeColorByPlayer(player);
    stream << "Joueur " << player;
    resetColor();
    stream << ", a vous de jouer :\n\n";
    return stream;
}

int UiOutils::selectPosition(std::ostream& out, std::istream& in, const std::string message) {
    char input;
    char options[] = "123";
    input = getValidChar(out, in, message, options);
    return UiOutils::charToInt(input)-1;
}

int UiOutils::charToInt(char c) {
    return c - '0';
}

char UiOutils::getValidChar(std::ostream& out, std::istream& in, const std::string message, const char *validChars) {
    std::string c;
    while (true) {
        out << message;
        in >> c;
        if ((c.length() == 1) && (strchr(validChars, c[0]) != nullptr)) {
            return c[0];
        } else {
            printInputErrorMessage(out);
        }
    }
}

std::ostream& UiOutils::printInputErrorMessage(std::ostream& stream) {
    changeColorToRed();
    stream << "ERREUR:\nEntrée incorrecte\n";
    resetColor();
    return stream;
}

char UiOutils::selectAction(std::ostream& out, std::istream& in) {
    char input;
    std::string message = "Voulez-vous ajouter (0) ou deplacer (1) une piece? (q pour quitter): ";
    char options[] = "01qQ";
    input = getValidChar(out, in, message, options);
    return input;
}

Size UiOutils::selectSize(std::ostream& out, std::istream& in) {
    char input;
    std::string message = "Quelle taille de piece voulez-vous ajouter?\n(1: petit, 2: moyen, 3: grand) ";
    char options[] = "123";
    input = getValidChar(out, in, message, options);
    return Size(charToInt(input));
}

bool UiOutils::exitConfirmation(std::ostream& out, std::istream& in) {
    char input;
    std::string message = "Voulez-vous vraiment quitter, Oui(o) ou Non(n)?";
    char options[] = "oOnN";
    input = tolower(getValidChar(out, in, message, options));
    if(input == 'o') {
        return true;
    }
    return false;
}

std::ostream& UiOutils::printPlaceErrorMessageByStatus(std::ostream& out, StatusEnum status) {
    changeColorToRed();
    switch (status) {
    case OK:
        break;
    case INVALID_SOURCE:
        break;
    case NO_PIECE_IN_HOUSE:
        out << "ERREUR:\nLa piece n'est pas disponible dans la maison du joueur.\n";
        break;
    case INVALID_TARGET:
        out << "ERREUR:\nLa piece est trop petite pour etre placee ici.\n";
        break;
    case INVALID_ENTRY:
        out << "ERREUR:\nEntree incorrecte.\n";
        break;
    }
    resetColor();
    return out;
}

std::ostream& UiOutils::printMoveErrorMessageByStatus(std::ostream& out, StatusEnum status) {
    changeColorToRed();
    switch (status) {
    case OK:
        break;
    case INVALID_SOURCE:
        out << "ERREUR:\nIl n'y a pas de piece a cet endroit\n";
        break;
    case NO_PIECE_IN_HOUSE:
        break;
    case INVALID_TARGET:
        out << "ERREUR:\nLa piece est trop petite pour etre placee ici.\n";
        break;
    case INVALID_ENTRY:
        out << "ERREUR:\nEntree incorrecte.\n";
        break;
    }
    resetColor();
    return out;
}

std::ostream& UiOutils::printWinnerByQuit(std::ostream& out, Player winner, Player looser) {
    out << "Le ";
    changeColorByPlayer(looser);
    printf("Joueur %d", looser);
    resetColor();
    printf(" a abandonne.\n");
    printWinner(out, winner);
    return out;
}

std::ostream& UiOutils::printWinner(std::ostream& out, Player winner) {
    changeColorByPlayer(winner);
    out << "BRAVO Joueur " << winner <<", vous avez GAGNE!\n";
    resetColor();
    return out;
}
