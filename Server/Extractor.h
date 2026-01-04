#pragma once
#include "Handler.h"
class Extractor : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override
    {
        (void)clientCtx; // unused parameter
        if (!commandCtx.result.ok)
            return;

        commandCtx.action = commandCtx.json["action"].toString();
        commandCtx.args = commandCtx.json["args"].toArray();
        qDebug() << "> Extractor : Extracted action:" << commandCtx.action;
        qDebug() << "> Extractor : Extracted args:" << commandCtx.args;
    }
};
