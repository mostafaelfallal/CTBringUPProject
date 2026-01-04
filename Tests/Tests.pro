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


SOURCES += main.cpp \
           Parser_Test.cpp \
           Command_Test.cpp

SOURCES += $$PWD/../Server/Parser.cpp \
           $$PWD/../Server/Command.cpp \
           $$PWD/../Server/ClientContext.cpp \
           $$PWD/../Server/Factory.cpp \
           $$PWD/../Server/Server.cpp 

HEADERS += $$PWD/../Server/Parser.h \
           $$PWD/../Server/Command.h \
           $$PWD/../Server/ClientContext.h \
           $$PWD/../Server/Factory.h \
           $$PWD/../Server/Server.h \
           $$PWD/../Server/ICommand.h \