#-------------------------------------------------
#
# Project created by QtCreator 2014-09-14T16:47:54
#
#-------------------------------------------------

QT       -= gui

TARGET = TextService
TEMPLATE = lib

DEFINES += TEXTSERVICE_LIBRARY

SOURCES += textservice.cpp

HEADERS += textservice.h\
        textservice_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
