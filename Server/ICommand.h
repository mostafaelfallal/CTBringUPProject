#pragma once
#include <QJsonObject>
#include "ClientContext.h"
#include "CommandContext.h"
#include "Result.h"
#include "Handler.h"
class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual Result validate(CommandContext &commandCtx, ClientContext *) = 0;
    virtual Result execute(CommandContext &commandCtx, ClientContext *) = 0;
    virtual Result run(CommandContext &commandCtx, ClientContext *) = 0;
};

// Base class handles Auth, Args parsing, and JSON wrapping
class BaseCommand : public ICommand
{
public:
    BaseCommand() = default;
    Result run(CommandContext &commandCtx, ClientContext *clientCtx) final
    {
        commandCtx.result = validate(commandCtx, clientCtx);
        qDebug() << "> BaseCommand : Validation result:" << (commandCtx.result.ok ? "OK" : "Error");
        if (!commandCtx.result.ok)
            return commandCtx.result;
        return execute(commandCtx, clientCtx);
    }
};

class CommandExecutor : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override
    {
        qDebug() << "> CommandExecutor : Executing command.";
        if (!commandCtx.result.ok || !commandCtx.command)
        {
            qDebug() << "> CommandExecutor : Skipping execution due to previous error.";
            return;
        }

        commandCtx.result = commandCtx.command->run(commandCtx, clientCtx);
    }
};