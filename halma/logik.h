#ifndef LOGIK_H
#define LOGIK_H
#include <iostream>
#include <array>
#include <vector>
#include <QObject>
#include "zug.h"


class Logik : public QObject
{
    Q_OBJECT
public:
    explicit Logik(QObject *parent = 0);



private:

//Attribues:
    //quint8 _startPosition = 0;
    std::vector<std::vector<quint8>> _neighbours;
    std::vector<std::vector<quint8>> _jumpNeighbours;
    const std::array< quint8, 6 > _startPositions {{0,22,110,120,98,10}} ;

    //attributes change during the game
    std::array< quint8,121 > _positions ;
    quint8 _winner=6;
    quint8 _currentPlayer=6;
    quint8 _oldPosition=200;
    quint8 _newPosition=200;
    zug _choosedZug;
    bool _zugIsZiehen=false;

    quint8 _firstPlayer=6;
    quint8 _playerNumber=0;
    std::vector<quint8> _playersStartPositions = {};
    zug _zugToBeChecked;




    const std::vector<quint8> start0 = {0,1,2,3,4,5,6,7,8,9,14,15,16,17,18};
    const std::vector<quint8> start1 = {18,19,20,21,22,31,32,33,34,43,44,45,54,55,64};
    const std::vector<quint8> start2 = {64,73,74,83,84,85,94,95,96,97,106,107,108,109,110};
    const std::vector<quint8> start3 = {102,103,104,105,106,111,112,113,114,115,116,117,118,119,120};
    const std::vector<quint8> start4 = {56,65,66,75,76,77,86,87,88,89,98,99,100,101,102};
    const std::vector<quint8> start5 = {10,11,12,13,14,23,24,25,26,35,36,37,46,47,56};

//Methodes:
    /**
     * @brief with this method, we can get the positions of a specific player and it is needed in 2 cases:
     * -to check for evey "Zug" (our "Zug" or other players "Zug" ) if the "Zug" is possible
     * -to check when we choose a figure (when it's our turn), if we are allowed to move it
     * @param player: one of the player in the game
     * @return a vector with 15 positions in our case
     */
    std::vector<quint8> currentPlayerPositions(quint8 player);

    /**
     * @brief set the players in their start Positions after the game start
     * @param numberPlayers
     */
    void setPlayer(quint8 numberPlayers);                           // set the first 15 positions for the player

    /**
     * @brief update the position table when a "Zug" has been done and confirmed by network
     * @param confirmedZug
     */

    void updatePositions(zug confirmedZug);


    /**
     * @brief this method initilize all the attributes in the logik and it needed in 2 cases:
     * - the first time the logik is created
     * - when there is a rematch
     */
    void initializeEverything();                              // initialize table positions with 6 and all the attributes that change




public:
    bool checkZug(zug zugToBeChecked);
    void checkWinner();


signals:

    //signals between gui and Logik:

    //void sigStartGame(std::vector<quint8> infosToStartTheGame);
      void sigStartGame();
    void sigSetCurrentPlayer(std::vector<quint8> playerAndPositions);

    void sigIsPositionOfCurrentPlayer(quint8 position);
    void sigIsZugPossible(bool test);
    void sigButtonConfirm(bool test);
    void sigChangePosition(std::vector<quint8> zug);
    void sigEndGame(bool test);



    //signals between Netz and Logik:
    void sigCheckedZug(bool test);
    void sigLocalZug(std::vector<quint8> localZug);
    void sigCheckWinner(bool test);



public slots:

    //slot between gui and Logik:
    void slotInputClickedPositions(quint8 position);
    void slotButtonConfirmClicked();

    //slot between Netz and Logik:
    void slotStartGame(std::vector<quint8> toLogik);
    void slotZug(std::vector<quint8> indEndfeld);
    void slotConfirmedZug(quint8 next);
    void slotCheckWinner();





};

#endif // LOGIK_H
