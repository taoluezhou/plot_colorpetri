#include "mainwindow.h"
#include "ui_mainwindow.h"

QString plainpath;
QList<struct arc> arc_pt;
QList<struct arc> arc_tp;
//QString datpath;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->gvfiletext->hide();
    //datflag=false;
    //plainflag=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatfile(QString filePath,QString fileName)
{
    QDir tempDir;
    QString currentDir = tempDir.currentPath();
    qDebug()<<currentDir;
    if(!tempDir.exists(filePath))
    {
        //qDebug()<<QObject::tr("不存在该路径")<<endl;
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    tempDir.setCurrent(filePath);
    qDebug()<<tempDir.currentPath();
    if(tempFile->exists(fileName))
    {
        //qDebug()<<QObject::tr("文件存在");
        return ;
    }
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        //qDebug()<<QObject::tr("打开失败");
    }
    tempFile->close();
    tempDir.setCurrent(currentDir);
    //qDebug()<<tempDir.currentPath();
}

/*void MainWindow::creat_arclist(int sum)
{
    if(sum!=0)
    {
        for(int i=0;i<sum;++i)
        {
            struct arc newarc;
            newarc.id = arclist.count();
            newarc.id_of_place = 0;
            newarc.id_of_transition = 0;
            newarc.id_of_color = 0;
            newarc.direction = -1;
            newarc.maxsize = 0;
            newarc.num = 0;
            //newarc.next = NULL;
            arclist<<newarc;
        }
    }
    return;
}

void MainWindow::creat_placelist(int row)
{
    if(row!=0)
    {
        for(int i=0;i<row;++i)
        {
            struct place newplace;
            newplace.id = placelist.count();
            newplace.number_of_color = 0;
            newplace.number_of_prearcs = 0;
            newplace.number_of_postarcs = 0;
            //newplace.place_token_num = 0;
            for(int j=0;j<Max_color_num_ofplace;++j)
            {
                newplace.size[j] = Default_Maxsize_token;
                newplace.init_number[j] = 0;
                newplace.num_of_transition_conflict[j] = 0;
                for(int k=0;k<Max_inout_num;++k)
                {
                    newplace.id_of_transition_conflict[j][k] = 0;
                    newplace.id_of_transition_rule_conflict[j][k] = 0;
                }
            }
            for(int j=0;j<Max_inout_num;++j)
            {
            newplace.id_of_prearcs[j] = 0;
            newplace.inc_from_prearcs[j] = 0;
            newplace.id_of_postarcs[j] = 0;
            newplace.dec_from_postarcs[j] = 0;
            }
            placelist<<newplace;
        }
    }
    return;
}

void MainWindow::creat_transitionlist(int column)
{
    if(column!=0)
    {
        for(int i=0;i<column;++i)
        {
            struct transition newtransition;
            newtransition.id = transitionlist.count();
            newtransition.number_of_rules = 0;
            for(int j=0;j<Max_rule_num;++j)
            {
                newtransition.number_of_prearcs[j] = 0;
                newtransition.number_of_postarcs[j] = 0;
            }
            for(int j=0;j<Max_rule_num;++j){
                for(int k=0;k<Max_color_num_inrule;++k)
                {
                    newtransition.id_of_prearcs[i][j] =0;
                    newtransition.id_of_postarcs[i][j] =0;
                    newtransition.dec_to_prearcs[i][j] =0;
                    newtransition.inc_to_postarcs[i][j] =0;
                    newtransition.maxsize_of_prearcs[i][j] =0;
                    newtransition.maxsize_of_postarcs[i][j] =0;
                }
            }
            transitionlist<<newtransition;
        }
    }
    return;
}
*/
void MainWindow::on_pushButton_clicked() //解析dat文件
{
    datpath = QFileDialog::getOpenFileName(this,"选择.dat文件","../","TXT(*.dat)");
    QFile file(datpath);
    QByteArray array;
    QString thisLine;
    int pos=0;
    int places_number;
    int transitions_number;
    int transition_rules_number[Max];
    int transition_rules_number_max;
    //int place_colors_number[Max];
    int p_to_t[Max][Max];
    for(int i=0;i<Max;i++)
        for(int j=0;j<Max;j++)
        {
            p_to_t[i][j]=0;
        }
    int t_to_p[Max][Max];
    for(int i=0;i<Max;i++)
        for(int j=0;j<Max;j++)
        {
            t_to_p[i][j]=0;
        }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->gvfiletext->setText("没有数据！");
    }
    else
    {
        //datflag=true;
        array=file.readLine(); //第一行忽略
        array=file.readLine(); //第二行取出place和transition数量
        thisLine=QString(array);
        QRegExp rx("(\\d+)");
        pos=0;
        pos = rx.indexIn(thisLine, pos);
        places_number=rx.cap(0).toInt();
        pos += rx.matchedLength();
        pos = rx.indexIn(thisLine, pos);
        transitions_number=rx.cap(0).toInt();
        //creat_placelist(places_number);
        //creat_transitionlist(transitions_number);
        //qDebug()<<placelist.count();
        //qDebug()<<transitionlist.count();
        array=file.readLine();//第3行忽略
        array=file.readLine();//第4行忽略
        array=file.readLine();//第五行取出每个变迁的颜色数
        thisLine=QString(array);
        pos=0;
        transition_rules_number_max=0;
        for(int i=0;i<transitions_number;i++)
        {
            pos = rx.indexIn(thisLine, pos);
            transition_rules_number[i]=rx.cap(0).toInt();
            if(transition_rules_number[i]>transition_rules_number_max)
            {
                transition_rules_number_max=transition_rules_number[i];
            }
            pos += rx.matchedLength();
        }
        //qDebug()<<transition_rules_number_max;
        array=file.readLine();//第6行忽略
        array=file.readLine();//第7行忽略
        array=file.readLine();//第八行取出每个库所颜色数
        thisLine=QString(array);
        pos=0;
        for(int i=0;i<places_number;i++)
        {
            pos = rx.indexIn(thisLine, pos);
            //place_colors_number[i]=rx.cap(0).toInt();
            pos += rx.matchedLength();
        }
        array=file.readLine();//第9行忽略
        array=file.readLine();//第10行忽略
        for(int i=0;i<places_number;i++)//往下读取places_number*（transition_rules_number_max+1）行
        {            
            array=file.readLine();//忽略一行
            for(int j=0;j<transition_rules_number_max;j++)
            {                               
                array=file.readLine();
                thisLine=QString(array);
                for(int k=0;k<transitions_number;k++)
                {
                    bool flag=false;
                    struct arc newarc;
                    newarc.placeID=i;
                    newarc.transitionID=k;
                    QString str=thisLine.section(' ',k+1,k+1).trimmed();//取出矩阵中每个元素
                    if(str[0]!='0')
                    {
                        p_to_t[i][k]++;
                        int l=0;
                        for(l=0;l<arc_pt.count();l++)
                        {
                            if(arc_pt[l].placeID==newarc.placeID&&arc_pt[l].transitionID==newarc.transitionID)
                            {
                                flag=true;
                                break;
                            }
                        }
                        if(flag==false)
                        {
                            newarc.color<<str;
                            arc_pt<<newarc;
                        }
                        else if(flag==true)
                        {
                            arc_pt[l].color<<str;
                        }
                    }
                }
            }
        }
        //qDebug()<<arc_pt[0].color;
        //qDebug()<<arc_pt[1].color;
        //qDebug()<<arc_pt[2].color;
        //qDebug()<<arc_pt[3].color;
        //qDebug()<<arc_pt[4].color;
        //qDebug()<<arc_pt[5].color;
        array=file.readLine();
        array=file.readLine();//忽略两行
        for(int i=0;i<places_number;i++)//往下读取places_number*（transition_rules_number_max+1）行
        {            
            array=file.readLine();//忽略一行
            for(int j=0;j<transition_rules_number_max;j++)
            {                
                array=file.readLine();
                thisLine=QString(array);
                for(int k=0;k<transitions_number;k++)
                {
                    bool flag=false;
                    struct arc newarc;
                    newarc.placeID=i;
                    newarc.transitionID=k;
                    QString str=thisLine.section(' ',k+1,k+1).trimmed();//取出矩阵中每个元素
                    if(str[0]!='0')
                    {
                        t_to_p[i][k]++;
                        int l=0;
                        for(l=0;l<arc_tp.count();l++)
                        {
                            if(arc_tp[l].placeID==newarc.placeID&&arc_tp[l].transitionID==newarc.transitionID)
                            {
                                flag=true;
                                break;
                            }
                        }
                        if(flag==false)
                        {
                            newarc.color<<str;
                            arc_tp<<newarc;
                        }
                        else if(flag==true)
                        {
                            arc_tp[l].color<<str;
                        }
                    }

                }
            }
        }
        //qDebug()<<arc_tp[0].color;
        //qDebug()<<arc_tp[1].color;
        //qDebug()<<arc_tp[2].color;
        //qDebug()<<arc_tp[3].color;


        QByteArray gv_array;
        //QString gv_str="";
        gv_array="digraph petri{\n";
        gv_array+="rankdir=BT\n";

        for(int i=0;i<places_number;i++)
        {
            gv_array+=("P"+QString::number(i+1).toUtf8()+"[label=P"+QString::number(i+1).toUtf8()+",shape=circle]\n");
        }
        for(int i=0;i<transitions_number;i++)
        {
            gv_array+=("T"+QString::number(i+1).toUtf8()+"[label=T"+QString::number(i+1).toUtf8()+",shape=box]\n");
        }
        for(int i=0;i<places_number;i++)
        {
            for(int k=0;k<transitions_number;k++)
            {
                if(p_to_t[i][k]!=0)
                {
                    gv_array+=("P"+QString::number(i+1).toUtf8()+"->T"+QString::number(k+1).toUtf8()+"\n");
                }
            }
        }
        for(int i=0;i<places_number;i++)
        {
            for(int k=0;k<transitions_number;k++)
            {
                if(t_to_p[i][k]!=0)
                {
                    gv_array+=("T"+QString::number(k+1).toUtf8()+"->P"+QString::number(i+1).toUtf8()+"\n");
                }
            }
        }
        gv_array+="}";
        //QDir tempDir;
        //QString path="..//";
        //creatfile(path,"petri.gv");
        ui->gvfiletext->setText(gv_array);
        QString gvpath="..//petri.gv";
        QFile gvFile(gvpath);
        bool gvfileisOK=gvFile.open(QIODevice::WriteOnly);
        if(gvfileisOK==true)
        {
            gvFile.write(ui->gvfiletext->toPlainText().toUtf8());
        }
        /*for(int i=0;i<places_number;i++)
        {
            for(int k=0;k<transitions_number;k++)
            {
                qDebug()<<t_to_p[i][k];
            }
        }*/
        //qDebug()<<gv_array;
        gvFile.close();


    }
    file.close();
}

void MainWindow::on_openPlain_clicked()
{
    plainpath = QFileDialog::getOpenFileName(this,"选择.plain文件","../","TXT(*.plain)");
    QFile plainfile(plainpath);
    if(!plainfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->plainfiletext->setText("没有数据！");
    }
    else
    {
        //plainflag=true;
        QByteArray plainarray;
        while(plainfile.atEnd()==false)
        {
            plainarray+=plainfile.readLine();
        }
        ui->plainfiletext->setText(plainarray);
        plainfile.close();
    }
}

void MainWindow::on_drawPetri_clicked()
{
     if(plainpath==NULL&&datpath==NULL)
        //qDebug()<<"没有dat和plain文件！";
        QMessageBox::critical(this,QString("无法绘制！"),QString("请打开dat和plain文件！"),QMessageBox::Yes);
     else if(plainpath==NULL)
        QMessageBox::critical(this,QString("无法绘制！"),QString("请打开plain文件！"),QMessageBox::Yes);
     else if(datpath==NULL)
        QMessageBox::critical(this,QString("无法绘制！"),QString("请打开dat文件！"),QMessageBox::Yes);
     else
     {
        drawingwindow_01.setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint);
        drawingwindow_01.show();
     }
}



