#include "supervisor.h"

Supervisor::Supervisor(QObject *parent) : QObject(parent), Halma(new halma), logik(new Logik), dialog (new Dialog), Widget(new widget), Network(new network)
{


    Halma->show();
    dialog->show();
    Widget->show();



    // connect between logik and gui:

    connect(logik, &Logik::sigStartGame, Halma , &halma::slotStartGame);
    connect(logik, &Logik::sigSetCurrentPlayer, Halma , &halma::slotSetCurrentPlayer);
    connect(Halma, &halma::sigBouttonClicked, logik, &Logik::slotInputClickedPositions);
    connect(logik, &Logik::sigIsPositionOfCurrentPlayer, Halma , &halma::slotIsPositionOfCurrentPlayer);
    connect(logik, &Logik::sigIsZugPossible, Halma , &halma::slotIsZugPossible );
    connect(logik, &Logik::sigButtonConfirm, Halma , &halma::slotButtonConfirm );
    //connect(Halma, &halma::sigButtonConfirmClicked, logik, &Logik::slotButtonConfirmClicked);
    connect(logik, &Logik::sigChangePosition, Halma , &halma::slotChangePosition );
    connect(logik, &Logik::sigEndGame, Halma , &halma::slotEndGame );



    // connect between logik and Netz:

    connect(Network, &network::sigStartGame, logik, &Logik::slotStartGame);
    connect(Network, &network::sigZug, logik, &Logik::slotZug);
    connect(logik, &Logik::sigCheckedZug, Network , &network::slotCheckedZug);
    connect(Network, &network::sigConfirmedZug, logik, &Logik::slotConfirmedZug);
    connect(logik, &Logik::sigLocalZug, Network , &network::slotLocalZug);
    //connect(Network, &network::sigCheckWinner, logik, &Logik::slotCheckWinner);
    connect(logik, &Logik::sigCheckWinner, Network , &network::slotCheckWinner);

















}

