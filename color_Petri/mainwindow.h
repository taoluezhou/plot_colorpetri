#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "petri.h"
#include "drawing.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QByteArray>
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDirModel>
#include <QMessageBox>

//定义存放Petri网信息的文档
#define FILE_NAME "matrix_of_petrinet.dat"

//定义库所最大扇入扇出单色弧个数
#define Max_inout_num 100

//定义库所变迁数量最大各100个
#define Max 100
//每个库所颜色个数的最大值
#define Max_color_num_ofplace 10
//变迁发生规则的最大个数
#define Max_rule_num  10
//每个变迁发生规则中条件个数的最大值
#define Max_color_num_inrule 10
//定义默认托肯容量
#define Default_Maxsize_token 15

#define Error 1
#define fuckrignt 0
#define OK 0
#define FError 2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




private slots:
    void on_pushButton_clicked();

    void on_openPlain_clicked();

    void on_drawPetri_clicked();

private:
    Ui::MainWindow *ui;
    //bool datflag;
    //bool plainflag;
    QString datpath;
    //QList<struct arc> arclist;
    //QList<struct place> placelist;
    //QList<struct transition> transitionlist;

protected:
    //void creat_arclist(int);
    //void creat_placelist(int);
    //void creat_transitionlist(int);
    void creatfile(QString filePath,QString fileName);
    drawing drawingwindow_01;


};

#endif // MAINWINDOW_H
