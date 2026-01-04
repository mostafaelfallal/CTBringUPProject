#pragma once

#include "Handler.h"
#include "Command.h"
class CommandBuilder : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override;

private:
    // command that inherit from ICommand take QJsonArray as args not ClientContext
    using CommandFactory = std::function<std::unique_ptr<ICommand>()>;

    const std::unordered_map<QString, CommandFactory> commandMap = {
        {"AUTH", []()
         { return std::make_unique<AuthCommand>(); }},
        {"CREATE", []()
         { return std::make_unique<CreateCommand>(); }},
        {"WRITE", []()
         { return std::make_unique<WriteCommand>(); }},
        {"READ", []()
         { return std::make_unique<ReadCommand>(); }},
        {"APPEND", []()
         { return std::make_unique<AppendCommand>(); }},
        {"DELETE", []()
         { return std::make_unique<DeleteCommand>(); }},
        {"LIST", []()
         { return std::make_unique<ListCommand>(); }},
        {"RENAME", []()
         { return std::make_unique<RenameCommand>(); }},
        {"INFO", []()
         { return std::make_unique<InfoCommand>(); }}};
};