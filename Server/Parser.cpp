#include "Parser.h"
#include <QStringList>
#include <QJsonDocument>

QJsonObject Parser::parseStringToJson(const QString& inputRaw) {
    QJsonObject jsonObj;
    QString input = inputRaw.trimmed();

    int firstSpaceIdx = input.indexOf(' ');
    QString action;
    QString argsStr;

    if (firstSpaceIdx == -1) {
        action = input;
        argsStr = "";
    }
    else {
        action = input.left(firstSpaceIdx);
        argsStr = input.mid(firstSpaceIdx + 1).trimmed();
    }
    jsonObj["action"] = action;
    QStringList argsList;
    if (!argsStr.isEmpty()) {
        argsList = argsStr.split(';', Qt::SkipEmptyParts);
        // for (QString& arg : argsList) {
        //     arg = arg.trimmed();
        // }
        QJsonArray argsArray;
        for (const QString& arg : argsList) {
            argsArray.append(arg);
        }
        jsonObj["args"] = argsArray;
    }
    else {
        jsonObj["args"] = QJsonArray(); // empty array
    }
    return jsonObj;
}

QString Parser::jsonToString(const QJsonObject& jsonObj) {
    QStringList parts;
    parts.append(jsonObj["status"].toString());
    if (jsonObj.contains("code")) {
        parts.append(QString::number(jsonObj["code"].toInt()));
    }
    parts.append(jsonObj["message"].toString());
    return parts.join(' ');
}