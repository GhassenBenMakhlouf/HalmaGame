#include "zug.h"

zug::zug():
    player(6), moves({})
{

}


void zug::setZug(quint8 playerX, std::vector<quint8> movesX)
{
    player=playerX;
    moves=movesX;
};

