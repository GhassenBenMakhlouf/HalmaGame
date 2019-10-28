#include "network.h"

network::network()
{

}


//------Server-------
void network::openServer(int port){
        i=0;
       _server = new QTcpServer(this);
       connect(_server, &QTcpServer::newConnection, this, &network::newConnectionServer);
       qDebug() << "Listening:" << _server->listen(QHostAddress::Any, port);
}


void network::newConnectionServer()
{    if (_server->hasPendingConnections())
        {

            qDebug() << "In newConnectionServer";
            _socket[i] = _server->nextPendingConnection();
            if(AnzahlSpieler-1==i) _server->pauseAccepting();
            mstream[i].setDevice(_socket[i]);
            //emit connectServer();
            qDebug()<<"testiiiing"<<i;
             connect(_socket[i], &QTcpSocket::disconnected, this, &network::disconnectedServer);
             connect(_socket[i], &QTcpSocket::readyRead, this, &network::einlesenServer);
             i++;
           AktSpieler++;
           // qDebug()<<AktSpieler;
        }
}




void network::disconnectedServer()
{   i--;
    AktSpieler--;
    _server->resumeAccepting();
    //verbindung break thegame (aka endTheGame)
    if(isGameActive==true) endTheGame(0xF0);
}



//------Client--------
void test(){
    qDebug()<<"client is connected !";
}

void network::openClient(QString host,int port)
{
    _socket2= new QTcpSocket();
    _socket2->connectToHost(host, port);
    mstream2.setDevice(_socket2);
    //connect(_socket2, &QTcpSocket::readyRead, this, &network::einlesenClient);
    //connect(_socket2, &QTcpSocket::connected, this, test);
}

/*
bool network::connectToHostt(QString host,int port)
{
    _socket2->connectToHost(host, port);
    return _socket2->waitForConnected();
}*/


void network::disconnectedClient()
{
    _socket2->disconnectFromHost();
    qDebug() << "Disconnected!";
}

void network::send()
{
    mstream2<<1<<2;
   mstream2<<3<<4<<5;
    qDebug()<<"sending client";
//    mstream[0]<<1<<2<<3;
//     qDebug()<<"sending server";
}


//---------communication-----------

quint8 network::naechsteStartzacke(int AnzahlSpieler)
                {         static quint8 i=0;
                          switch(AnzahlSpieler)
                          {
                          case 2:
                              if (i==0) (i=3);
                              if (i==3) (i=0);
                          case 3:
                              if (i==0) (i=2);
                              if (i==2) (i=4);
                              if (i==4) (i=0);
                          }
                          return i;
                }


void network::einlesenServer(){

     //QObject *QObject::sender();



/*

    quint8 cmd=0;
    quint8 length=0;
    mstream[i]>>cmd;
    mstream[i]>>length;
        //einlesen 0x01 und 0x02 Antworten
        if (cmd==static_cast<quint8>(0x01))
        {
            quint8 gruppenr;
            mstream[i]>>gruppenr;
            switch(AnzahlSpieler){
            case 2:
            {
                if(AnzahlSpieler>AktSpieler)
                {Spieler[0]=0;Spieler[1]=-1;mstream[i]<<0x02<<0x03<<0x00<<0x00<<0x04;}
                else mstream[i]<<0x02<<0x01<<0x01;

                break;
            }
            case 3:
                if(i==0)
                {
                    if(AnzahlSpieler>AktSpieler)
                        {Spieler[0]=0;Spieler[1]=-1;mstream[i]<<0x02<<0x03<<0x00<<0x00<<0x04;}
                    else mstream[i]<<0x02<<0x01<<0x01;

                }
                if(i==1)
                {
                    if(AnzahlSpieler>AktSpieler)
                        mstream[i]<<0x02<<0x03<<0x00<<0x04<<0x04;
                    else mstream[i]<<0x02<<0x01<<0x01;
                    Spieler[2]=1;
                }
                break;
            }

            if(AnzahlSpieler==AktSpieler){
                std::vector<quint8> toLogik={};
                isGameActive=true;
                //emit to gui or logik to start game
                switch(AnzahlSpieler){
                case 2:
                    toLogik.push_back(0x00);
                    toLogik.push_back(0x02);
                    toLogik.push_back(0x00);
                    toLogik.push_back(0x03);
                    emit sigStartGame(toLogik);
                    mstream[0]<<0x04<<0x04<<0x00<<0x02<<0x00<<0x03;
                    break;
                case 3:
                    toLogik.push_back(0x00);
                    toLogik.push_back(0x03);
                    toLogik.push_back(0x00);
                    toLogik.push_back(0x04);
                    toLogik.push_back(0x02);
                    emit sigStartGame(toLogik);
                    mstream[0]<<0x04<<0x05<<0x00<<0x03<<0x00<<0x04<<0x02;
                    mstream[1]<<0x04<<0x05<<0x00<<0x03<<0x00<<0x04<<0x02;
                    break;
                }
            }


         }




               //einlesen Zug von Clients
        if (cmd==static_cast<quint8>(0x05))
        {
            quint8 zugTyp;mstream[i]>>zugTyp;
            quint8 indStartfeld;mstream[i]>>indStartfeld;
            std::vector<quint8> indEndfeld={}; indEndfeld.push_back(indStartfeld);



            if (zugTyp==0x00){

                quint8 currentStream;
                mstream[i]>>currentStream;
                indEndfeld.push_back(currentStream);
                //emit zu logik von Server über den Zug!
                emit sigZug(indEndfeld);
                //send to other clients
            }
            else{
                for (quint8 iter=0;iter<zugTyp;iter++)
                {
                    quint8 currentStream;
                    mstream[i]>>currentStream;
                    indEndfeld.push_back(currentStream);
                }
                //emit zu logik von Server über den Zug!
                emit sigZug(indEndfeld);
            }
            //if status ok emit to client status ok ?(slot unten slotCheckZug)
       }

        //status OK?
        if (cmd==static_cast<quint8>(0x07)){
            quint8 status;
            mstream[i]>>status;

            if (status==static_cast<quint8>(0x01)) //emit logik to pop a specefic error and to break the game(aka endTheGame)
                    endTheGame(0xF1);
            if (status==static_cast<quint8>(0x00)) {
            static int rundeOkZahl=0;
            if (rundeOkZahl==AnzahlSpieler-1) {rundeOkZahl=0;

                                                //emit to logik cool mach weiter
                                                   emit sigConfirmedZug(next);

//                                                quint8 next=naechsteStartzacke(AnzahlSpieler);
//                                                for(int iter;iter!=AnzahlSpieler-2;iter++)
//                                                mstream[iter]<<0x08<<0x01<<next;

                                              }
            else rundeOkZahl++;
            }
        }


        if(cmd==static_cast<quint8>(0x0A))
        {
            quint8 status;
            mstream[i]>>status;

            if (status==static_cast<quint8>(0x00)) emit sigRematch(true);
            if (status==static_cast<quint8>(0x01)) emit sigRematch(false);

        }
*/


}




void network::startGame(){
/*
    if (AnzahlSpieler==2)
        mstream[0]<<0x04<<0x04<<0x00<<0x02<<0x00<<0x02;
    if (AnzahlSpieler==3)
        {
        mstream[0]<<0x04<<0x05<<0x00<<0x03<<0x00<<0x04<<0x02;
        mstream[1]<<0x04<<0x05<<0x00<<0x03<<0x00<<0x04<<0x02;
        }
        */
}


void network::einlesenClient(){
//    quint8 cmd=0;
//    quint8 length=0;
//    quint8 indexStart=0;
//    quint8 startzackeBeginner=0;
//    quint8 zugTyp=0;
//    quint8 spielErgebnis=0;
//    quint8 indexStartfeld=0;
//    quint8 status=0;
//    quint8 startzackeNaechste=0;
//    quint8 startzackeZiehnder=0;
//    quint8 anzahlSpieler=0;
//    quint8 rematch=0;
//    std::vector<quint8> startZacken={};
//    std::vector<quint8> zug={};


//    mstream2>>cmd;
//    mstream2>>length;
//    switch(cmd)
//    {
//        case(static_cast<quint8>(0x02)):
//                    if (length==1)
//                        qDebug()<<"couldn't connect!";// emit sth to show that you couldn't connect!
//                        else{
//                        qDebug()<<"connected";
//                        mstream2>>indexStart;
//                        mstream2>>indexStart;
//                        //another emit maybe ?
//                        }
//                        break;
//        case(static_cast<quint8>(0x04)):{
//                    mstream2>>startzackeBeginner;
//                    mstream2>>anzahlSpieler;
//                    std::vector<quint8> toLogik={};
//                    toLogik.push_back(startzackeBeginner);
//                    toLogik.push_back(anzahlSpieler);

//                    quint8 currentStream;
//                    if (length==4)
//                    {
//                        mstream2>>currentStream;
//                        startZacken.push_back(currentStream);
//                        toLogik.push_back(currentStream);
//                        mstream2>>currentStream;
//                        startZacken.push_back(currentStream);
//                        toLogik.push_back(currentStream);
//                    }
//                    if (length==5)
//                    {
//                        mstream2>>currentStream;
//                        startZacken.push_back(currentStream);
//                        toLogik.push_back(currentStream);
//                        mstream2>>currentStream;
//                        startZacken.push_back(currentStream);
//                        toLogik.push_back(currentStream);
//                        mstream2>>currentStream;
//                        startZacken.push_back(currentStream);
//                        toLogik.push_back(currentStream);
//                    }
//                    emit sigStartGame(toLogik);
//                    //emit to logik
//                    break;}
//        case(static_cast<quint8>(0x06)):
//                    mstream2>>startzackeZiehnder;
//                    mstream2>>zugTyp;
//                    mstream2>>indexStartfeld;
//                    zug.push_back(indexStartfeld);
//                    quint8 currentStream;
//                    mstream2>>currentStream;
//                    zug.push_back(currentStream);

//                    if(zugTyp!=static_cast<quint8>(0x00))
//                    for (quint8 iter=1;iter<zugTyp;iter++)
//                    {mstream2>>currentStream;
//                    zug.push_back(currentStream);
//                    }
//                    break;
//                    //emit to logik the move
//        case(static_cast<quint8>(0x07)):
//                    mstream2>>status;
//                    if (status==static_cast<quint8>(0x01))
//                        //emit to gui, u did a mistake
//                    break;
//        case(static_cast<quint8>(0x08)):
//                    mstream2>>startzackeNaechste;
//                    //go next round, emit
//                    break;
//        case(static_cast<quint8>(0x09)):
//                    mstream2>>spielErgebnis;
//                    //take a decision with it, emit
//                    mstream2>>rematch;
//                    //take a decision with it, emit
//                    break;

//    }
}

void network::schreiben(int spieler,qint8 cmd,qint8 length, qint8 var[]){

/*
     for (int i=0;i!=(AnzahlSpieler-2);i++)
     {
         if (i!=spieler) {
             mstream2[i] << cmd;
             mstream2[i] << length;
             
             int j=0;
             while (j<length) {mstream2[i]<<var[j]; j++;}
         }    
     }
*/
}


void network::slotCheckedZug(bool test){

    //send to clients if true else end the game
}

void network::endTheGame(quint8 reason){
    //send 0x09 to players
    emit sigEndTheGame(reason);
    if(reason>=0&&reason<=5){}
        //0x09<<0x02<<reason<<0x00
    else{}
        //0x09<<0x02<<reason<<0x01
}
void network::slotLocalZug(std::vector<quint8>){
   //send broadcast to all clients
}
void network::slotCheckWinner(bool t){
    if (t){
        quint8 reason;
        //currentPlayer...
        endTheGame(reason);
    }
    else{
        quint8 next=naechsteStartzacke(AnzahlSpieler);
        for(int iter;iter!=AnzahlSpieler-2;iter++)
        mstream[iter]<<0x08<<0x01<<next;
       }

}

