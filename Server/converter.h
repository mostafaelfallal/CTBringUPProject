#pragma once
#include "Handler.h"
#include <QJsonDocument>
#include "Result.h"
class TextJsonConverter : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override
    {
        (void)clientCtx; // unused parameter
        if (!commandCtx.result.ok)
            return;
        qDebug() << "> TextJsonConverter : Converting text to JSON";

        QJsonParseError err;
        auto doc = QJsonDocument::fromJson(commandCtx.rawText.toUtf8(), &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject())
        {
            commandCtx.result = Result::error(400, "Invalid JSON");
            return;
        }
        qDebug() << "> TextJsonConverter : " << doc.toJson(QJsonDocument::Compact);
        commandCtx.json = doc.object();
    }
};

class ObjectTextConverter : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override
    {
        (void)clientCtx; // unused parameter
        if (commandCtx.result.ok)
        {
            if (commandCtx.response)
            {
                commandCtx.outText = QString("OK : %1").arg(commandCtx.response->toText());
            }
            else
            {
                commandCtx.outText = "OK";
            }
        }
        else
        {
            commandCtx.outText = QString("Error %1: %2")
                                     .arg(commandCtx.result.code)
                                     .arg(commandCtx.result.message);
        }
        qDebug() << "> ObjectTextConverter : Converted object to text:" << commandCtx.outText;
    }
};
