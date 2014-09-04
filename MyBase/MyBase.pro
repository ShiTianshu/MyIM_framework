#-------------------------------------------------
#
# Project created by QtCreator 2014-08-17T11:18:08
#
#-------------------------------------------------

QT       -= gui

TARGET = MyBase
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $(MYIM_HOME)/lib

SOURCES += \
    imod.cpp \
    iact.cpp \
    iproc.cpp \
    global.cpp \
    isrc.cpp \
    iactgroup.cpp \
    inputcontext.cpp \
    iext.cpp

HEADERS += \
    imod.h \
    iact.h \
    iproc.h \
    global.h \
    isrc.h \
    iactgroup.h \
    inputcontext.h \
    iext.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
