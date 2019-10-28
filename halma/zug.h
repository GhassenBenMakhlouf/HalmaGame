#ifndef ZUG_H
#define ZUG_H
#include <QObject>

class zug
{
public:

    zug();

    quint8 player;
    std::vector<quint8> moves;

    void setZug(quint8 playerX, std::vector<quint8> movesX);



};

#endif // ZUG_H
