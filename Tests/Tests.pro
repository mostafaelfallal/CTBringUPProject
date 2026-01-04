TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core network
QT -= gui
LIBS += -lgtest -lgtest_main -lpthread 
include(../defaults.pri)
INCLUDEPATH += $$PWD/../Server \
               $$PWD/../Client \
               $$PWD/..


SOURCES += main.cpp 
           

SOURCES += 

HEADERS += 