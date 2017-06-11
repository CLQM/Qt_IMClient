#-------------------------------------------------
#
# Project created by QtCreator 2016-07-21T10:34:22
#
#-------------------------------------------------

QT       += core gui  sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IMclient_1
TEMPLATE = app

INCLUDEPATH += $$PWD/include
include(common/common.pri)
include(wlogin/wlogin.pri)
include(network/network.pri)
include(protocol/protocol.pri)
include(wchat/wchat.pri)


SOURCES += main.cpp \
    logiclayer.cpp

HEADERS  += \
    logiclayer.h

FORMS    +=
