#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T13:53:43
#
#-------------------------------------------------

QT       -= gui

TARGET = SimpleSrc
TEMPLATE = lib

DEFINES += SIMPLESRC_LIBRARY

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

SOURCES += simplesrc.cpp

HEADERS += simplesrc.h\
        simplesrc_global.h

DESTDIR = $$(MYIM_HOME)/mod

unix {
    target.path = /usr/lib
    INSTALLS += target
}
