#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T22:16:45
#
#-------------------------------------------------

QT       -= gui

TARGET = TableSrc
TEMPLATE = lib

DEFINES += TABLESRC_LIBRARY

SOURCES += tablesrc.cpp \
    tablecursor.cpp

HEADERS += tablesrc.h\
        tablesrc_global.h \
    tablecursor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

DESTDIR = $$(MYIM_HOME)/mod
