#include "halma.h"
#include "ui_halma.h"
#include <QPixmap>
#include <QDebug>

halma::halma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::halma)
{

    ui->setupUi(this);
    QPixmap pix("/home/ge56fiq/Pic_One-01.png");
    ui->label_pic->setPixmap(pix);
    emit initilizePosition();


    const QRegExp re("PB_(\\d+)");
    foreach(QPushButton *button, findChildren<QPushButton*>(re)) {
      (void) re.indexIn(button->objectName());  // we know it matches, but we need the captured text
      const int id = re.cap(1).toInt();
      ui->buttonGroup->setId(button, id); // assuming the button is already in the button group
      connect(ui->buttonGroup->button(id), &QPushButton::clicked, [=](){emit sigBouttonClicked(id);});
      connect(ui->buttonGroup->button(id), &QPushButton::clicked,[=](){ a=id; emit colorB();});
    }

  connect (this,&halma::colorB, this, &halma::buttonAble);

}

halma::~halma()
{
    delete ui;
}

void halma::slotStartGame()
{
    //open the window of the Board

}


void halma::slotSetCurrentPlayer(std::vector<quint8> playerAndPositons )
{

    currentPlayer=playerAndPositons[0]; //->id

    ui->buttonGroup->button(a)->setEnabled(false);// Locks all pushButtons

    if(currentPlayer==ourPlayer) {

            for (int i=0;i<15;i++) {
            ui->buttonGroup->button(playerAndPositons[i])->setDisabled(false); //unlocks players' pushButtons

    } }
}


void halma::slotIsPositionOfCurrentPlayer(quint8 position)
{
    //color the selected button
    buttonAble();

}

void halma::slotIsZugPossible(bool test)
{
    //color the new button and discolor the old button
    if(test==true){
    buttonAble2();}

}

void halma::slotButtonConfirm(bool test)
{
    //enable button confirm or disable it

    if (test==true){
ui->Confirm->setEnabled(true);
    }

}

void halma::slotChangePosition(std::vector<quint8> zug)
{   
    //color the buttons of the zug one after the other then color only the last position in the zug
    quint8 oldButton=zug[0];
    for (int i=1; i<=zug.size();i++)
    {
                         // discolor old button
                         // color button i
       oldButton=zug[i];

    }

}

void halma::slotEndGame(bool test)
{
    //for exemple go back to Window Host/client and write a message with "you loose the game"
}


void halma::buttonAble2(){
    ui->buttonGroup->button(a)->setStyleSheet("QPushButton {   border-style: solid;border-width:1px;border-radius:6px;background-color: gray; }\n"
                                              "QPushButton:enabled { background-color: red; }\n");
}

void halma::buttonAble()
{
ui->buttonGroup->button(a)->setStyleSheet("QPushButton{background-color:transparent;}");
}




