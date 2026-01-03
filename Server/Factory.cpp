#include "Factory.h"

std::unique_ptr<ICommand> CommandFactory::createCommand(ClientContext* clientContext, const QString& action)
{

    // AUTH CREATE WRITE READ APPEND DELETE LIST RENAME INFO
    if (action == "AUTH")
    {
        return std::make_unique<AuthCommand>(clientContext);
    }
    else if (action == "CREATE")
    {
        return std::make_unique<CreateCommand>(clientContext);
    }
    else if (action == "WRITE")
    {
        return std::make_unique<WriteCommand>(clientContext);
    }
    else if (action == "READ")
    {
        return std::make_unique<ReadCommand>(clientContext);
    }
    else if (action == "APPEND")
    {
        return std::make_unique<AppendCommand>(clientContext);
    }
    else if (action == "DELETE")
    {
        return std::make_unique<DeleteCommand>(clientContext);
    }
    else if (action == "LIST")
    {
        return std::make_unique<ListCommand>(clientContext);
    }
    else if (action == "RENAME")
    {
        return std::make_unique<RenameCommand>(clientContext);
    }
    else if (action == "INFO")
    {
        return std::make_unique<InfoCommand>(clientContext);
    }
    return nullptr;
}