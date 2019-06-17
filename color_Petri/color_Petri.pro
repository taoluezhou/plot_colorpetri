#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T20:42:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = color_Petri
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawing.cpp

HEADERS  += mainwindow.h \
    petri.h \
    drawing.h

FORMS    += mainwindow.ui \
    drawing.ui
