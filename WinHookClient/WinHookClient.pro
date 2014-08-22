#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T15:06:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WinHookClient
TEMPLATE = app


SOURCES += main.cpp\
        hook.cpp

HEADERS  += hook.h

DESTDIR = $$(MYIM_HOME)/bin
