QT += core network
QT -= gui

CONFIG += c++17
TARGET = Server
TEMPLATE = app
include(../defaults.pri)
SOURCES += main.cpp Server.cpp ClientContext.cpp Parser.cpp
HEADERS += Server.h ClientContext.h Parser.h