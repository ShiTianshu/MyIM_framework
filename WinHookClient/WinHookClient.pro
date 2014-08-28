#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T15:06:46
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WinHookClient
TEMPLATE = app

LIBS += -L $$(MYIM_HOME)/lib -lMyBase

SOURCES += main.cpp\
        hook.cpp \
    socket.cpp \
    sender.cpp

HEADERS  += hook.h \
    socket.h \
    sender.h \
    caret.h

DESTDIR = $$(MYIM_HOME)/bin
