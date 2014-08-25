#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T13:46:30
#
#-------------------------------------------------

QT += core gui widgets

TARGET = SimpleUI
TEMPLATE = lib

DEFINES += SIMPLEUI_LIBRARY

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

SOURCES += simpleui.cpp \
    candidate.cpp

HEADERS += simpleui.h\
        simpleui_global.h \
    candidate.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $$(MYIM_HOME)/mod
