#include "drawing.h"
#include "ui_drawing.h"

#define AMP 150
#define MVRIGHT 500
#define MVDOMN  100

drawing::drawing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::drawing)
{
    ui->setupUi(this);
    setWindowTitle("Drawing Petri");
    resize(2000,1000);
    pix=QPixmap(2000,1000);
    pix.fill(Qt::white);
}

drawing::~drawing()
{
    delete ui;
}

void drawing::arrow(QPainter& pai, float x1 ,float y1,float x2,float y2)
{
     //pai.begin(this);
   //设定画笔
    QPen pen;
    pen.setWidth(2);//设置线宽
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    //将画笔交给“画家”
    pai.setPen(pen);
    float l = 10;
    float a = 0.5;
    float x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - x1)) - a);
    float y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - x1)) - a);
    float x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - y1)) - a);
    float y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - y1)) - a);
    pai.drawLine(x2,y2,x3,y3);
    pai.drawLine(x2,y2,x4,y4);
    pai.drawLine(x1,y1,x2,y2);

    //qDebug()<<x1;
    //qDebug()<<y1;
    //qDebug()<<x2;
    //qDebug()<<y2;
}

void drawing::paintEvent(QPaintEvent *)
{
    QPainter pp(this);
    pp.drawPixmap(0,0,pix);
    QPainter pai(&pix);
    QPen pen;
    pen.setWidth(2);//设置线宽
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
     //设定画刷
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    //将画笔交给“画家”
    pai.setPen(pen);
    //将画刷交给“画家”
    pai.setBrush(brush);
    //设置字体
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing,0);
    font.setPointSize(10);
    //将字体交给“画家”
    pai.setFont(font);

    QFile plainfile(plainpath);
    if(!plainfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        pen.setColor(Qt::red);
        pai.setPen(pen);
        pai.drawText(50,50,QStringLiteral("没有数据！"));
    }
    else
    {
         //int pos=0;
         while(!plainfile.atEnd())
         {
            pen.setColor(Qt::black);
            pai.setPen(pen);
            QByteArray array;
            QString thisLine;            
            array=plainfile.readLine();
            thisLine=QString(array);
            //qDebug()<<thisLine;
            if(thisLine[0]=='n')
            {
                QStringList LineData;
                LineData = thisLine.split(QRegExp("[ ]"));
                if(thisLine[5]=='P')
                {
                    float xy_1=LineData[3].toFloat();
                    float xy_2=LineData[2].toFloat();
                    float diameter=LineData[4].toFloat();
                    pai.drawEllipse((xy_1-diameter/2)*AMP+MVRIGHT,(xy_2-diameter/2)*AMP+MVDOMN,diameter*AMP,diameter*AMP);
                    pai.drawText(xy_1 * AMP+MVRIGHT-10, xy_2 * AMP+MVDOMN,LineData[1]);
                }
                else if(thisLine[5]=='T')
                {
                    float xy_1=LineData[3].toFloat();
                    float xy_2=LineData[2].toFloat();
                    float width=LineData[5].toFloat();
                    float height=LineData[4].toFloat();
                    pai.drawRect((xy_1-width/2)*AMP+MVRIGHT,(xy_2-height/2)*AMP+MVDOMN,width*AMP,height*AMP);
                    pai.drawText(xy_1 * AMP+MVRIGHT-10, xy_2 * AMP+MVDOMN,LineData[1]);
                }
            }
            else if(thisLine[0]=='e')
            {
                QStringList LineData;
                QList<float> xy;
                float mid_x;
                float mid_y;
                LineData = thisLine.split(QRegExp("[ ]"));
                int point_num=LineData[3].toInt();
                for(int i=0;i<point_num;i++)
                {
                    xy<<LineData[5+2*i].toFloat();
                    xy<<LineData[4+2*i].toFloat();
                }
                for(int i=0;i<point_num-2;i++)
                {
                    pai.drawLine(xy[2*i]*AMP+MVRIGHT,xy[2*i+1] *AMP+MVDOMN,xy[2*i+2] *AMP+MVRIGHT,xy[2*i+3] *AMP+MVDOMN);
                }
                int xy_num=xy.count();
                arrow(pai,xy[xy_num-4]*AMP+MVRIGHT,xy[xy_num-3]*AMP+MVDOMN,xy[xy_num-2]*AMP+MVRIGHT,xy[xy_num-1]*AMP+MVDOMN);
                mid_x=(xy[xy_num-2]+xy[0])/2;
                mid_y=(xy[xy_num-1]+xy[1])/2;
                //qDebug()<<mid_x<<mid_y;

                pen.setColor(Qt::red);
                pai.setPen(pen);

                QRegExp rx("(\\d+)");
                //int pos=0;
                int placeID;
                int transitionID;
                if(LineData[1][0]=='P')
                {
                    rx.indexIn(LineData[1],0);
                    placeID=rx.cap(0).toInt()-1;
                    rx.indexIn(LineData[2],0);
                    transitionID=rx.cap(0).toInt()-1;
                    //qDebug()<<placeID;
                    //qDebug()<<transitionID;
                    for(int i=0;i<arc_pt.count();i++)
                    {
                        if(arc_pt[i].placeID==placeID&&arc_pt[i].transitionID==transitionID)
                        {
                            for(int j=arc_pt[i].color.count()-1;j>=0;j--)
                            {
                                pai.drawText(mid_x*AMP+MVRIGHT-20, mid_y*AMP+MVDOMN-20*(arc_pt[i].color.count()-1-j)-20,arc_pt[i].color[j]);
                            }
                        }
                    }
                }
                else if(LineData[1][0]=='T')
                {
                    rx.indexIn(LineData[1],0);
                    transitionID=rx.cap(0).toInt()-1;
                    rx.indexIn(LineData[2],0);
                    placeID=rx.cap(0).toInt()-1;
                    for(int i=0;i<arc_tp.count();i++)
                    {
                        if(arc_tp[i].placeID==placeID&&arc_tp[i].transitionID==transitionID)
                        {
                            for(int j=arc_tp[i].color.count()-1;j>=0;j--)
                            {
                                pai.drawText(mid_x*AMP+MVRIGHT-20, mid_y*AMP+MVDOMN-20*(arc_tp[i].color.count()-1-j)-20,arc_tp[i].color[j]);
                            }
                        }
                    }
                    //qDebug()<<transitionID;
                    //qDebug()<<placeID;
                }
            }
         }        
    }
    plainfile.close();
    //qDebug()<<plainpath;
    //qDebug()<<datpath;


}
