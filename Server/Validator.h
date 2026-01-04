#pragma once

#include "Handler.h"
class ProtocolValidator : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override
    {
        (void)clientCtx; // unused parameter
        if (!commandCtx.result.ok)
            return;

        if (!commandCtx.json.contains("action") || !commandCtx.json["action"].isString())
        {
            commandCtx.result = Result::error(400, "Missing 'action'");
            return;
        }

        if (!commandCtx.json.contains("args") || !commandCtx.json["args"].isArray())
        {
            commandCtx.result = Result::error(400, "Missing 'args'");
            return;
        }
        qDebug() << "> ProtocolValidator : Protocol validation passed.";
    }
};
