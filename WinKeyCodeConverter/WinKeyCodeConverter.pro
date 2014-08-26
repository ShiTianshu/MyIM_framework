#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T14:46:23
#
#-------------------------------------------------

QT       -= gui

TARGET = WinKeyCodeConverter
TEMPLATE = lib

DEFINES += WINKEYCODECONVERTER_LIBRARY

SOURCES += winkeycodeconverter.cpp

HEADERS += winkeycodeconverter.h\
        winkeycodeconverter_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

DESTDIR = $$(MYIM_HOME)/mod
