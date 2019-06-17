/********************************************************************************
** Form generated from reading UI file 'drawingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWINGWINDOW_H
#define UI_DRAWINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawingWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DrawingWindow)
    {
        if (DrawingWindow->objectName().isEmpty())
            DrawingWindow->setObjectName(QStringLiteral("DrawingWindow"));
        DrawingWindow->resize(800, 600);
        centralwidget = new QWidget(DrawingWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        DrawingWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DrawingWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        DrawingWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DrawingWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DrawingWindow->setStatusBar(statusbar);

        retranslateUi(DrawingWindow);

        QMetaObject::connectSlotsByName(DrawingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DrawingWindow)
    {
        DrawingWindow->setWindowTitle(QApplication::translate("DrawingWindow", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class DrawingWindow: public Ui_DrawingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWINGWINDOW_H
