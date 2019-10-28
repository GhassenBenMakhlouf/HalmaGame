#include "widget.h"
#include "ui_widget.h"

widget::widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    label=new QLabel(this);
    movie= new QMovie("/home/ge56fiq/gif.gif");
    label->setMovie(movie);
    this->resize(740,580);
    label->resize(640,480);
    label->show();
    movie->start();
}

widget::~widget()
{
    delete ui;
}
