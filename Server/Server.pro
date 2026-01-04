QT += core network
QT -= gui

CONFIG += c++17
TARGET = Server
TEMPLATE = app
include(../defaults.pri)
SOURCES += main.cpp Builder.cpp ClientContext.cpp Command.cpp Server.cpp
HEADERS += Builder.h Server.h ClientContext.h Command.h converter.h ICommand.h Extractor.h Handler.h Reader.h Response.h Result.h Validator.h Writer.h