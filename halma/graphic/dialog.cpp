#include "dialog.h"
#include "ui_dialog.h"
#include <QPixmap>
#include "secdialog.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tB->append("asdfasdfasdfasd");
    ui->LE->setText("variable");
    ui->LE->setReadOnly(1);
    QPixmap pix("/home/ge56fiq/login.png");
    ui->label_pic2_2->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    SecDialog object;
    object.setModal(true);
    object.exec();
}

void Dialog::on_radioButton_clicked(bool checked)
{ui->lineEdit_2->setDisabled(true);
    ui->label_3->setDisabled(true);
    ui->lineEdit->setDisabled(true);
    ui->label_2->setDisabled(true);
    ui->Join->setDisabled(true);
        ui->LE->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->sB->setEnabled(true);
        ui->Host->setEnabled(true);
        ui->label_7->setEnabled(true);
        ui->label_4->setEnabled(true);
}

void Dialog::on_radioButton_2_clicked(bool checked)
{

    if (checked)
   {ui->LE->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->sB->setDisabled(true);
    ui->Host->setDisabled(true);
    ui->label_7->setDisabled(true);
    ui->label_4->setDisabled(true);
            ui->lineEdit_2->setEnabled(true);
            ui->label_3->setEnabled(true);
            ui->lineEdit->setEnabled(true);
            ui->label_2->setEnabled(true);
            ui->Join->setEnabled(true);
    }
}
