#pragma once
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
// From Text to JSON Object and vice versa
// text : <action> <arg1>;<arg2>;... -> JSON { "action": <action>, "args": [<arg1>, <arg2>, ...] }
// JSON : {"status" : string, "code" : int,"message":string} -> text : "OK : <message>" or "Error <code> : <message>"
class JsonFormatter
{
public:
    static QJsonDocument toJsonDoc(const QString &action, const QStringList &args)
    {
        QJsonObject obj;
        obj["action"] = action;
        QJsonArray argsArray;
        for (const QString &arg : args)
        {
            argsArray.append(arg);
        }
        obj["args"] = argsArray;
        QJsonDocument doc(obj);
        return doc;
    }
    static bool fromJsonString(const QString &jsonString, QString &action, QStringList &args)
    {

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject())
        {
            return false;
        }

        QJsonObject obj = doc.object();
        action = obj["action"].toString();
        QJsonArray argsArray = obj["args"].toArray();
        args.clear();
        for (const QJsonValue &val : argsArray)
        {
            args.append(val.toString());
        }
        return true;
    }
};