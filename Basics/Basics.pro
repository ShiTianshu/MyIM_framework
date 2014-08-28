#-------------------------------------------------
#
# Project created by QtCreator 2014-08-28T09:23:05
#
#-------------------------------------------------

QT       -= gui

TARGET = Basics
TEMPLATE = lib

DEFINES += BASICS_LIBRARY

SOURCES += basics.cpp

HEADERS += basics.h\
        basics_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

DESTDIR = $$(MYIM_HOME)/mod
