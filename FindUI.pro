#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T19:52:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FindUI
TEMPLATE = app

DESTDIR = $$PWD\

SOURCES += main.cpp\
        mainwindow.cpp\
        datareader.cpp \
        findmanager.cpp

HEADERS  += mainwindow.h\
            chaptor.h \
            datareader.h \
            findmanager.h

FORMS    += mainwindow.ui
