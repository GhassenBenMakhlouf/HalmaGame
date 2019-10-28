#ifndef NETWORK_H
#define NETWORK_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>
#include <QObject>
#include <array>
#include <iostream>
#include <vector>



/**
 * @brief The Network class - Netzwerk-Klasse
 */
class network : public QObject
{
    Q_OBJECT
public:
    network();
        void openServer(int port);
        void openClient(QString host,int port);
        void startGame();
        quint8 naechsteStartzacke(int AnzahlSpieler);
        int AnzahlSpieler=5; //brauche ich von GUI wenn als server ausgeführt
        int AktSpieler=1;
        int i=0;
        void endTheGame(quint8 reason);
        bool isGameActive=false;
public slots:
        //bool connectToHostt(QString host,int port);
        void newConnectionServer();
        void disconnectedServer();
        void disconnectedClient();
        void einlesenClient();
        void einlesenServer();
        void schreiben(int spieler,qint8 cmd,qint8 length, qint8 var[]);
        void send();
        void slotCheckedZug(bool test);
        void slotLocalZug(std::vector<quint8>);
        void slotCheckWinner(bool t);
signals:
    void sigStartGame(std::vector<quint8> toLogik);
    void sigZug(std::vector<quint8> indEndfeld);
    void sigEndTheGame(quint8 reason);
    void sigConfirmedZug(quint8 next);
    void sigRematch(bool t);

private:
        std::array<QTcpSocket*,4> _socket;
        QTcpSocket *_socket2;

        std::array<QDataStream,4> mstream;
        QDataStream mstream2;

        QTcpServer *_server;
        std::array<int,4> Spieler;

        QString IpS; //your ip!
        QString IpC; //chosen ip to connect to
        int PortS;  //chosen port as a server
        int PortC; //chosen port as a joiner




};

#endif // NETWORK_H
