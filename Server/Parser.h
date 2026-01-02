#ifndef PARSER_H
#define PARSER_H

// takes a string input and parses it into JSON format
// <action> arg1;arg2; ...
// using qt
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
class Parser {
    public:
    static QJsonObject parseStringToJson(const QString& input);
};

#endif // PARSER_H