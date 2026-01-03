#include "Parser.h"
#include <QStringList>
#include <QJsonDocument>

QJsonObject Parser::parseStringToJson(const QString& input) {
    QJsonObject jsonObj;

    // cmd : <action> arg1;arg2; ... (args may contain spaces but not semicolons)
    // USE index of first space to separate action and args
    int firstSpaceIdx = input.indexOf(' ');
    QString action;
    QString argsStr;
    if (firstSpaceIdx == -1) {
        action = input.trimmed();
        argsStr = "";
    }
    else {
        action = input.left(firstSpaceIdx).trimmed();
        argsStr = input.mid(firstSpaceIdx + 1).trimmed();
    }
    jsonObj["action"] = action;
    QStringList argsList;
    if (!argsStr.isEmpty()) {
        argsList = argsStr.split(';', Qt::SkipEmptyParts);
        for (QString& arg : argsList) {
            arg = arg.trimmed();
        }
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
    // Status + Code (if present) + Message
    QStringList parts;
    parts.append(jsonObj["status"].toString());
    if (jsonObj.contains("code")) {
        parts.append(QString::number(jsonObj["code"].toInt()));
    }
    parts.append(jsonObj["message"].toString());
    return parts.join(' ');
}