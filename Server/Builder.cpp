#include "Builder.h"

#include "Command.h"
#include <unordered_map>
#include <functional>

void CommandBuilder::process(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    if (!commandCtx.result.ok)
        return;
    auto it = commandMap.find(commandCtx.action);
    if (it != commandMap.end())
    {
        commandCtx.command = it->second();
        qDebug() << "> CommandBuilder : Found Command.";
        return;
    }
    commandCtx.result = Result::error(400, "Unknown command: " + commandCtx.action);
}