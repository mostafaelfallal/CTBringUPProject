#pragma once

#include <memory>

#include "Command.h"

class CommandFactory
{
    public:
    static std::unique_ptr<ICommand> createCommand(ClientContext* clientContext, const QString& action);
};