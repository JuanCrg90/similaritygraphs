#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T10:37:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SimilarityGraphs
TEMPLATE = app

LIBS+= -std=gnu++11


LIBS+= -lboost_regex

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
        mainwindow.cpp \
    corpus.cpp \
    preprocesor.cpp \
    corpora.cpp \
    document.cpp \
    metrics.cpp \
    barcharts.cpp \
    qcustomplot.cpp


HEADERS  += mainwindow.h \
    corpus.h \
    preprocesor.h \
    corpora.h \
    document.h \
    metrics.h \
    barcharts.h \
    qcustomplot.h
    corpus.cpp



FORMS    += mainwindow.ui \
    barcharts.ui

