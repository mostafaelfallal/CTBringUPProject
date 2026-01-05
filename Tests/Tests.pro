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


SOURCES += main.cpp CommandTest.cpp
           

SOURCES += ../Server/ClientContext.cpp ../Server/server.cpp ../Server/Builder.cpp ../Server/Command.cpp 

HEADERS += ../Server/Handler.h ../Server/Reader.h ../Server/CommandContext.h  ../Server/ClientContext.h ../Server/converter.h ../Server/server.h ../Common.h ../Client/JsonFormatter.h ../Client/Validator.h