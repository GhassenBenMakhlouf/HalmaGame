#ifndef HALMA_H
#define HALMA_H


#include <QDialog>

namespace Ui {
class halma;
}

class halma : public QDialog
{
    Q_OBJECT

public:
    explicit halma(QWidget *parent = 0);
    ~halma();
    void buttonGroup(bool);
    quint8 currentPlayer=6;
    int a;
    quint8 ourPlayer;


private slots:



void buttonAble ();
void buttonAble2();

void on_Confirm_clicked();

void on_Confirm_clicked(bool checked);

private:
    Ui::halma *ui;

signals:
   void initilizePosition();
   void sigBouttonClicked(int i);
   void colorB();




public slots:
    void slotStartGame();
    void slotSetCurrentPlayer(std::vector<quint8> playerAndPositons );
    void slotIsPositionOfCurrentPlayer(quint8 position);
    void slotIsZugPossible(bool test);
    void slotButtonConfirm(bool test);
    void slotChangePosition(std::vector<quint8> zug);
    void slotEndGame(bool test);


};


#endif // HALMA_H
