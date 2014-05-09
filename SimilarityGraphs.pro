#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T10:37:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimilarityGraphs
TEMPLATE = app


LIBS+= -lboost_regex

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
        mainwindow.cpp \
    corpus.cpp \
    preprocesor.cpp


HEADERS  += mainwindow.h \
    corpus.h \
    preprocesor.h

FORMS    += mainwindow.ui

