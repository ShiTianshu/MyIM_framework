#-------------------------------------------------
#
# Project created by QtCreator 2014-08-17T11:39:33
#
#-------------------------------------------------

QT       -= gui

TARGET = MyCore
TEMPLATE = lib

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

DEFINES += MYCORE_LIBRARY

SOURCES += mycore.cpp \
    myengine.cpp

HEADERS += mycore.h\
        mycore_global.h \
    myengine.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $$(MYIM_HOME)/mod
