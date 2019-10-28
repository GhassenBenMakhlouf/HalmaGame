#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "graphic/dialog.h"
#include "graphic/halma.h"
#include "graphic/widget.h"
#include "logik.h"
#include "network.h"






class Supervisor : public QObject
{
    Q_OBJECT
public:
    explicit Supervisor(QObject *parent = 0);

    Logik *logik;

    halma *Halma;
    Dialog *dialog;
    widget *Widget;

    network *Network;


signals:

public slots:
};

#endif // SUPERVISOR_H
