#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
#include <QMovie>
#include <QLabel>
namespace Ui {
class widget;
}

class widget : public QDialog
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = 0);
    ~widget();
    QMovie *movie;
    QLabel *label;
private:
    Ui::widget *ui;
};

#endif // WIDGET_H
