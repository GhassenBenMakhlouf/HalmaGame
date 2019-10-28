#include "logik.h"
#include <QDebug>

Logik::Logik(QObject *parent) : QObject(parent)
{

    //initialisation of neighbours:
    _neighbours = {
                 {200,200,200,200,1,2}      ,
                 {200,0,200,2,3,4}          ,{0,200,1,200,4,5},
                 {200,1,200,4,6,7}          ,{1,2,3,5,7,8}            ,{2,200,4,200,8,9}        ,
                 {200,3,200,7,14,15}        ,{3,4,6,8,15,16}          ,{4,5,7,9,16,17}          ,{5,200,8,200,17,18}      ,
                 {200,200,200,11,200,23}    ,{200,200,10,12,23,24}    ,{200,200,11,13,24,25}    ,{200,200,12,14,25,26}    ,{200,6,13,15,26,27}    ,{6,7,14,16,27,28}      ,{7,8,15,17,28,29}      ,{8,9,16,18,29,30}      ,{9,200,17,19,30,31}    ,{200,200,18,20,31,32}  ,{200,200,19,21,32,33}  ,{200,200,20,22,33,34}  ,{200,200,21,200,34,200},
                 {10,11,200,24,200,35}      ,{11,12,23,25,35,36}      ,{12,13,24,26,36,37}      ,{13,14,25,27,37,38}      ,{14,15,26,28,38,39}    ,{15,16,27,29,39,40}    ,{16,17,28,30,40,41}    ,{17,18,29,31,41,42}    ,{18,19,30,32,42,43}    ,{19,20,31,33,43,44}    ,{20,21,32,34,44,45}    ,{21,22,33,200,45,200}  ,
                 {23,24,200,36,200,46}      ,{24,25,35,37,46,47}      ,{25,26,36,38,47,48}      ,{26,27,37,39,48,49}      ,{27,28,38,40,49,50}    ,{28,29,39,41,50,51}    ,{29,30,40,42,51,52}    ,{30,31,41,43,52,53}    ,{31,32,42,44,53,54}    ,{32,33,43,45,54,55}    ,{33,34,44,200,55,200}  ,
                 {35,36,200,47,200,56}      ,{36,37,46,48,56,57}      ,{37,38,47,49,57,58}      ,{38,39,48,50,58,59}      ,{39,40,49,51,59,60}    ,{40,41,50,52,60,61}    ,{41,42,51,53,61,62}    ,{42,43,52,54,62,63}    ,{43,44,53,55,63,64}    ,{44,45,54,200,64,200}  ,
                 {46,47,200,57,65,66}       ,{47,48,56,58,66,67}      ,{48,49,57,59,67,68}      ,{49,50,58,60,68,69}      ,{50,51,59,61,69,70}    ,{51,52,60,62,70,71}    ,{52,53,61,63,71,72}    ,{53,54,62,64,72,73}    ,{54,55,63,200,73,74}   ,
                 {200,56,200,66,75,76}      ,{56,57,65,67,76,77}      ,{57,58,66,68,77,78}      ,{58,59,67,69,78,79}      ,{59,60,68,70,79,80}    ,{60,61,69,71,80,81}    ,{61,62,70,72,81,82}    ,{62,63,71,73,82,83}    ,{63,64,72,74,83,84}    ,{64,200,73,200,84,85}  ,
                 {200,65,200,76,86,87}      ,{65,66,75,77,87,88}      ,{66,67,76,78,88,89}      ,{67,68,77,79,89,90}      ,{68,69,78,80,90,91}    ,{69,70,79,81,91,92}    ,{70,71,80,82,92,93}    ,{71,72,81,83,93,94}    ,{72,73,82,84,94,95}    ,{73,74,83,85,95,96}    ,{74,200,84,200,96,97}  ,
                 {200,75,200,87,98,99}      ,{75,76,86,88,99,100}     ,{76,77,87,89,100,101}    ,{77,78,88,90,101,102}    ,{78,79,89,91,102,103}  ,{79,80,90,92,103,104}  ,{80,81,91,93,104,105}  ,{81,82,92,94,105,106}  ,{82,83,93,95,106,107}  ,{83,84,94,96,107,108}  ,{84,85,95,97,108,109}  ,{85,200,96,200,109,110},
                 {200,86,200,99,200,200}    ,{86,87,98,100,200,200}   ,{87,88,99,101,200,200}   ,{88,89,100,102,200,200}  ,{89,90,101,103,200,111},{90,91,102,104,111,112},{91,92,103,105,112,113},{92,93,104,106,113,114},{93,94,105,107,114,200},{94,95,106,108,200,200},{95,96,107,109,200,200},{96,97,108,110,200,200},{97,200,109,200,200,200},
                 {102,103,200,112,200,115}  ,{103,104,111,113,115,116},{104,105,112,114,116,117},{105,106,113,200,117,200},
                 {111,112,200,116,200,118}  ,{112,113,115,117,118,119},{113,114,116,200,119,200},
                 {115,116,200,119,200,120}  ,{116,117,118,200,120,200},
                 {118,119,200,200,200,200}
                 };

    //initialisation of jumps:
    for (std::vector<quint8> i: _neighbours)
    {
        std::vector<quint8> iVector={};
        quint8 k=0;                     // goes from 0 to 5
        for (quint8 j: i)
        {
            if (j==200){iVector.push_back(200);}
            else {iVector.push_back(_neighbours[j][k]);}
            k++ ;
        }
        _jumpNeighbours.push_back(iVector);

    }

    //initialisation of _positions to Debug:
    _currentPlayer=0;
    for(quint8 i=0; i<=120; i++)
    {
        _positions[i]=6;
    }
    for (quint8 i: start0)_positions[i]=0;





}


void Logik::setPlayer(quint8 numberPlayers)
{

    if (numberPlayers==3)
    {
        for (quint8 i: start0)_positions[i]=0;
        for (quint8 i: start2)_positions[i]=2;
        for (quint8 i: start4)_positions[i]=4;
    }
    else //if(numberPlayers==2)
    {
        for (quint8 i: start0)_positions[i]=0;
        for (quint8 i: start3)_positions[i]=3;
    }

}


void Logik::initializeEverything()
{
   for(quint8 i=0; i<=120; i++)
   {
       _positions[i]=6;
   }

   _winner=6;
   _currentPlayer=6;
   _oldPosition=200;
   _newPosition=200;
   _choosedZug.setZug(6,{});

   _firstPlayer=6;
   _playerNumber=0;
   _playersStartPositions = {};
   _zugToBeChecked.setZug(6,{});

};


std::vector<quint8> Logik::currentPlayerPositions(quint8 player)
{
    std::vector<quint8> positionsVector;
    for(quint8 i=0; i<=120; i++)
    {
        if ( _positions[i]==player ) {positionsVector.push_back(i);}

    }
    return positionsVector;

};

void Logik::updatePositions(zug confirmedZug)
{
    for(quint8 i=0; i<=120; i++)
    {
        _positions[confirmedZug.moves.front()]=6;
        _positions[confirmedZug.moves.back()]=confirmedZug.player;
    }

};

void Logik::checkWinner()
{
    if (_playerNumber==3)
    {
        bool test=true;
        for (quint8 i: start1)
        {
        if ( _positions[i]!=4) {test=false; break;}
        };
        if (test==true) {_winner=4;}

        test=true;
        for (quint8 i: start3)
        {
        if ( _positions[i]!=0) {test=false; break;}
        };
        if (test==true) {_winner=0;}

        test=true;
        for (quint8 i: start5)
        {
        if ( _positions[i]!=2) {test=false; break;}
        };
        if (test==true) {_winner=2;}
    }

    if (_playerNumber==2)
    {
        bool test=true;
        for (quint8 i: start3)
        {
        if ( _positions[i]!=0) {test=false; break;}
        };
        if (test==true) {_winner=0;}

        test=true;
        for (quint8 i: start0)
        {
        if ( _positions[i]!=3) {test=false; break;}
        };
        if (test==true) {_winner=3;}
    }




};



bool Logik::checkZug(zug zugToBeChecked)
{
    bool isZugPossible=false;

    //check if the player who will do the zug is between 0 and 5:
    if (zugToBeChecked.player<0 || zugToBeChecked.player>5 ) return isZugPossible;

    //check if the vector move of the zug is empty:

    if (zugToBeChecked.moves.empty()) return isZugPossible;

    // check if the player is allowed to move this figure:

    bool isPositionOfCurrentPlayer=false;
    for (quint8 i: currentPlayerPositions(zugToBeChecked.player))
    {
        if (zugToBeChecked.moves.front()==i) {isPositionOfCurrentPlayer=true; break;}
    }

    if (!isPositionOfCurrentPlayer)return isZugPossible;


    //check the moves:

    for (uint i=1; i<zugToBeChecked.moves.size(); i++)
    {
        //check if the position is already used:

        if (_positions[zugToBeChecked.moves[i]]!=6) {return isZugPossible; };


        //check if the move is "Ziehen":

        bool isZiehen=false;

        if (zugToBeChecked.moves.size()==2)
        {
            for (quint8 j: _neighbours[zugToBeChecked.moves[i-1]])
            {
            if (zugToBeChecked.moves[i]==j && j!=200) {isZiehen=true; break;}
            }
        }

        //check if the move to neighbour is impossible:

        if (isZiehen && _positions[zugToBeChecked.moves[i]]!=6) {return isZugPossible;}

        //check if the move to neighbour is possible:

        if (isZiehen && _positions[zugToBeChecked.moves[i]]==6) {_zugIsZiehen= true; isZugPossible=true; return isZugPossible;}

        //check if the move is "Sprung":

        bool isSprung=false;
        quint8 k=0;

        for (quint8 j: _jumpNeighbours[zugToBeChecked.moves[i-1]])
        {
        quint8 x=_neighbours[zugToBeChecked.moves[i-1]][k];                            //position between i and i-1
        if (zugToBeChecked.moves[i]==j && _positions[x]!=6 && j!=200) {isSprung=true; break;}
        k++;
        }

        //check if the move to jumpNeighbour is impossible:

        if (isSprung && _positions[zugToBeChecked.moves[i]]!=6) {return isZugPossible;}

        //if it is neither a "Ziehen" nor a "Sprung", Zug is not possible:

        if (isSprung==false && isZiehen==false) {return isZugPossible;}

    }

    //when the zug is sprung:
    _zugIsZiehen=false;
    isZugPossible=true;
    return isZugPossible;

};


void Logik::slotInputClickedPositions(quint8 position)
{
    qDebug()<<"clicked position  "<<position;
    qDebug()<<"old position  "<<_oldPosition;
    qDebug()<<"new position  "<<_newPosition;
    qDebug()<<"current player  "<<_currentPlayer;



    //check if the figure of the player is:

    bool isPositionOfCurrentPlayer=false;
    for (quint8 i: currentPlayerPositions(_currentPlayer))
    {
        if (i==position) {isPositionOfCurrentPlayer=true; break;}
    }

    // save this position and send a signal:

    if (_oldPosition==200 && isPositionOfCurrentPlayer )
    {
        _oldPosition=position;
        emit sigIsPositionOfCurrentPlayer(position);
        qDebug()<<"clicked 1. position  "<<position;
    }

    //if the player wants to make the first move, check it :

    else if (_oldPosition!=200 && _newPosition==200 && _oldPosition!=position)
            {
                zug partialZug;
                partialZug.setZug(_currentPlayer, {_oldPosition,position});

                if (checkZug(partialZug))
                {
                    _newPosition=position;
                    _choosedZug.setZug(_currentPlayer, {_oldPosition,_newPosition});
                    bool test=true;
                    emit sigIsZugPossible(test);
                    emit sigButtonConfirm(test);
                    qDebug()<<"clicked 2. position and saved  "<<position;
                }
                else
                {
                    bool test=false;
                    emit sigIsZugPossible(test);
                    qDebug()<<"clicked 2. position and not saved  "<<position;

                };

            }

//    // if the player wants to make more moves:

        else if (_oldPosition!=200 && _newPosition!=200 && _newPosition!=position )
                {
                    zug partialZug;
                    partialZug.setZug(_currentPlayer,{_newPosition,position});
                    if (checkZug(partialZug))
                    {
                        _oldPosition=_newPosition;
                        _newPosition=position;
                        _choosedZug.moves.push_back(_newPosition);
                        bool test=true;
                        emit sigIsZugPossible(test);
                        qDebug()<<"clicked x. position and saved "<<position;
                    }
                    else
                    {
                        bool test=false;
                        emit sigIsZugPossible(test);
                        qDebug()<<"clicked x. position and not saved "<<position;
                    };


                }


    qDebug()<<"------------------------------------------------------------------------------------------";


}

void Logik::slotStartGame(std::vector<quint8> toLogik)
{
    //initilize everything:
    initializeEverything();

    //get the informations from toLogik in variables:

    _firstPlayer=toLogik[0];
    _playerNumber=toLogik[1];

    for (quint8 i=2; i<toLogik.size(); i++ )
    {
        _playersStartPositions.push_back(toLogik[i]);
    }

    //emit sigStartGame(toLogik);
    emit sigStartGame();



}

void Logik::slotZug(std::vector<quint8> indEndfeld)
{

    _zugToBeChecked.setZug(_currentPlayer,indEndfeld);
    bool test=checkZug(_zugToBeChecked);
    emit sigCheckedZug(test);
}

void Logik::slotConfirmedZug(quint8 next)
{
    //do an update in positions:

    updatePositions(_zugToBeChecked);
    _zugToBeChecked.setZug(6,{});

    //change current player:
    _currentPlayer=next;

    //emit to gui:

    emit sigChangePosition(_zugToBeChecked.moves);
}


void Logik::slotCheckWinner()
{
    checkWinner();

    if (_winner>=0 && _winner<=5 )
    {
        emit sigCheckWinner(true);
    }
    else emit sigCheckWinner(false);

}

void Logik::slotButtonConfirmClicked()
{

    std::vector<quint8> vectorToBeSenT={};

    quint8 zugTyp=0;
    if (!_zugIsZiehen) {zugTyp=_choosedZug.moves.size();}

    for(quint8 i:_choosedZug.moves)
    {
        vectorToBeSenT.push_back(i);
    }

    emit sigLocalZug(vectorToBeSenT);

    _choosedZug={};
}









