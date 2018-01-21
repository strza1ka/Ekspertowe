#-------------------------------------------------
#
# Project created by QtCreator 2018-01-13T17:54:37
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ekspertowe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cloth.cpp \
    network.cpp \
    trainingdata.cpp \
    neuron.cpp \
    net.cpp \
    filecsv.cpp

HEADERS  += mainwindow.h \
    cloth.h \
    trainingdata.h \
    neuron.h \
    net.h \
    connection.h \
    filecsv.h

FORMS    += mainwindow.ui
