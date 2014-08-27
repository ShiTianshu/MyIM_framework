#-------------------------------------------------
#
# Project created by QtCreator 2014-08-27T16:33:11
#
#-------------------------------------------------

QT       -= gui

TARGET = TableTranslator
TEMPLATE = lib

DEFINES += TABLETRANSLATOR_LIBRARY

SOURCES += tabletranslator.cpp

HEADERS += tabletranslator.h\
        tabletranslator_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

DESTDIR = $$(MYIM_HOME)/mod
