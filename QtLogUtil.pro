#-------------------------------------------------
#
# Project created by QtCreator 2018-02-05T15:56:12
#
#-------------------------------------------------

QT       -= gui

TARGET = QtLogUtil
TEMPLATE = lib

DEFINES += QTLOGUTIL_LIBRARY

SOURCES += qtlogutil.cpp

HEADERS += qtlogutil.h\
        qtlogutil_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
