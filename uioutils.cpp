#include "uioutils.h"
#include <iostream>
#include "config.h"
#include "piece.h"
#include "statusEnum.h"
#include <string>
#include <cctype>

std::ostream& UiOutils::changeColorByPlayer(std::ostream& stream, Player player) {
    if (!USE_COLORS){
        return stream;
    }
    switch (player) {
    case NO_PLAYER:
        resetColor(stream);
        break;
    case PLAYER_1:
        stream << "\033[0;33m";   // yellow
        break;
    case PLAYER_2:
        stream << "\033[0;34m";   // bold blue
        break;
    }
    return stream;
}

std::ostream& UiOutils::changeColorToRed(std::ostream& stream) {
    return stream << "\033[0;31m";   // red
}

std::ostream& UiOutils::resetColor(std::ostream& stream) {
    if (!USE_COLORS){
        return stream;
    }
    stream << "\033[0m";
    return stream;
}

std::ostream& UiOutils::printSeparator(std::ostream& stream) {
    stream << "-------------------------------------\n";
    return stream;
}

std::ostream& UiOutils::printPlayerTurn(std::ostream& stream, Player player) {
    changeColorByPlayer(stream,player);
    stream << "Joueur " << player;
    resetColor(stream);
    stream << ", à vous de jouer :\n\n";
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

char UiOutils::getValidChar(std::ostream& out, std::istream& in, const std::string &message, const char *validChars) {
    std::string c;
    while (true) {
        out << message;
        in >> c;
        if ((c.length() == 1) && (std::strchr(validChars, c[0]) != nullptr)) {
            return c[0];
        } else {
            printInputErrorMessage(out);
        }
    }
}

std::ostream& UiOutils::printInputErrorMessage(std::ostream& stream) {
    changeColorToRed(stream);
    stream << "ERREUR:\nEntrée incorrecte\n";
    resetColor(stream);
    return stream;
}

char UiOutils::selectAction(std::ostream& out, std::istream& in) {
    char input;
    std::string message = "Voulez-vous ajouter (0) ou déplacer (1) une pièce? (q pour quitter): ";
    char options[] = "01qQ";
    input = getValidChar(out, in, message, options);
    return input;
}

Size UiOutils::selectSize(std::ostream& out, std::istream& in) {
    char input;
    std::string message = "Quelle taille de pièce voulez-vous ajouter?\n(1: petit, 2: moyen, 3: grand) ";
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
    changeColorToRed(out);
    switch (status) {
    case OK:
        break;
    case INVALID_SOURCE:
        break;
    case NO_PIECE_IN_HOUSE:
        out << "ERREUR:\nLa pièce n'est pas disponible dans la maison du joueur.\n";
        break;
    case INVALID_TARGET:
        out << "ERREUR:\nLa pièce est trop petite pour être placée ici.\n";
        break;
    case INVALID_ENTRY:
        out << "ERREUR:\nEntrée incorrecte.\n";
        break;
    }
    resetColor(out);
    return out;
}

std::ostream& UiOutils::printMoveErrorMessageByStatus(std::ostream& out, StatusEnum status) {
    changeColorToRed(out);
    switch (status) {
    case OK:
        break;
    case INVALID_SOURCE:
        out << "ERREUR:\nIl n'y a pas de pièce à cet endroit\n";
        break;
    case NO_PIECE_IN_HOUSE:
        break;
    case INVALID_TARGET:
        out << "ERREUR:\nLa pièce est trop petite pour être placée ici.\n";
        break;
    case INVALID_ENTRY:
        out << "ERREUR:\nEntrée incorrecte.\n";
        break;
    }
    resetColor(out);
    return out;
}

std::ostream& UiOutils::printWinnerByQuit(std::ostream& out, Player winner, Player looser) {
    out << "Le ";
    changeColorByPlayer(out, looser);
    printf("Joueur %d", looser);
    resetColor(out);
    printf(" a abandonné.\n");
    changeColorByPlayer(out, winner);
    printf("BRAVO Joueur %d, vous avez GAGNÉ!", winner);
    resetColor(out);
    return out;
}
