QT += core network
QT -= gui

CONFIG += c++17
TARGET = Client
TEMPLATE = app
include(../defaults.pri)
SOURCES += main.cpp Client.cpp
HEADERS += Client.h InputWorker.h