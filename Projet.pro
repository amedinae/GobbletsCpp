TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        board.cpp \
        cell.cpp \
        main.cpp \
        piece.cpp \
        uioutils.cpp

HEADERS += \
    board.h \
    cell.h \
    config.h \
    piece.h \
    playerenum.h \
    statusEnum.h \
    uioutils.h
