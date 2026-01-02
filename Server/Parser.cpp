#include "Parser.h"
#include <QStringList>
#include <QJsonDocument>

QJsonObject Parser::parseStringToJson(const QString& input) {
    QJsonObject jsonObj;

    // Split the input string into action and arguments
    QStringList parts = input.split(' ', Qt::SkipEmptyParts);
    if (parts.isEmpty()) {
        return jsonObj; // return empty object if input is empty
    }

    QString action = parts[0];
    jsonObj["action"] = action;

    if (parts.size() > 1) {
        QString argsStr = parts[1];
        QStringList argsList = argsStr.split(';', Qt::SkipEmptyParts);
        QJsonArray argsArray;
        for (const QString& arg : argsList) {
            argsArray.append(arg);
        }
        jsonObj["args"] = argsArray;
    }
    else {
        jsonObj["args"] = QJsonArray(); // empty args array
    }

    return jsonObj;
}