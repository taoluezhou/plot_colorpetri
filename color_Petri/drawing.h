#ifndef DRAWING_H
#define DRAWING_H


#include <QDialog>
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
#include <complex>


extern QString plainpath;
//extern QString datpath;
extern QList<struct arc> arc_pt;
extern QList<struct arc> arc_tp;

struct arc{
    //int ID;
    int placeID;
    int transitionID;
    QStringList color;
};

namespace Ui {
class drawing;
}

class drawing : public QDialog
{
    Q_OBJECT

public:
    explicit drawing(QWidget *parent = 0);
    ~drawing();

private:
    Ui::drawing *ui;
    QPixmap pix;


protected:
    void paintEvent(QPaintEvent *);
    void arrow(QPainter& pai, float x1 ,float y1,float x2,float y2);

};

#endif // DRAWING_H
