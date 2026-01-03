#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
class Parser {
    public:
    static QJsonObject parseStringToJson(const QString& input);
    static QString jsonToString(const QJsonObject& jsonObj);
};

#endif // PARSER_H