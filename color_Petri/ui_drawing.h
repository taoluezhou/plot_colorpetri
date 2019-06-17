/********************************************************************************
** Form generated from reading UI file 'drawing.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWING_H
#define UI_DRAWING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_drawing
{
public:
    QWidget *widget;

    void setupUi(QDialog *drawing)
    {
        if (drawing->objectName().isEmpty())
            drawing->setObjectName(QStringLiteral("drawing"));
        drawing->resize(400, 300);
        widget = new QWidget(drawing);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 30, 321, 201));

        retranslateUi(drawing);

        QMetaObject::connectSlotsByName(drawing);
    } // setupUi

    void retranslateUi(QDialog *drawing)
    {
        drawing->setWindowTitle(QApplication::translate("drawing", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class drawing: public Ui_drawing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWING_H
