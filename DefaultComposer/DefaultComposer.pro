#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T13:12:22
#
#-------------------------------------------------

QT       -= gui

TARGET = DefaultComposer
TEMPLATE = lib

DEFINES += DEFAULTCOMPOSER_LIBRARY

SOURCES += defaultcomposer.cpp

HEADERS += defaultcomposer.h\
        defaultcomposer_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

DESTDIR = $$(MYIM_HOME)/mod
