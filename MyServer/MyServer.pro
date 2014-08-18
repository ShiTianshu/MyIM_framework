#-------------------------------------------------
#
# Project created by QtCreator 2014-08-17T11:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyServer
TEMPLATE = app

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

SOURCES += main.cpp\
        myserver.cpp

HEADERS  += myserver.h

DESTDIR = $$(MYIM_HOME)/bin
