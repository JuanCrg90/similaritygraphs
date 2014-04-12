#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T10:37:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimilarityGraphs
TEMPLATE = app

LIBS+= -std=gnu++11


SOURCES += main.cpp\
        mainwindow.cpp \
    corpus.cpp

HEADERS  += mainwindow.h \
    corpus.h

FORMS    += mainwindow.ui

