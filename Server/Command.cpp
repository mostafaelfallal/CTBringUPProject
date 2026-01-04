#include "Command.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include "../Common.h"
// --- Helper for File Operations ---
bool isValidFilename(const QString &filename)
{
    if (filename.contains("/") || filename.contains("..") || filename.startsWith("/") || filename.startsWith(".") || filename.contains("~"))
    {
        return false;
    }
    return true;
}
// --- Command Implementations ---

Result AuthCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    if (clientCtx->getIsAuthenticated())
    {
        return Result::success();
    }
    if (commandCtx.args.size() < 2)
    {
        return Result::error(400, "Missing username or password.");
    }
    return Result::success();
}

Result AuthCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    QString username = commandCtx.args[0].toString();
    QString password = commandCtx.args[1].toString();

    if (username == USERNAME && password == PASSWORD)
    {
        clientCtx->setIsAuthenticated(true);
        return Result::success();
    }

    clientCtx->setIsAuthenticated(false);
    return Result::error(401, "Authentication failed.");
}
Result CreateCommand::validate(CommandContext &commandCtx, ClientContext *)
{
    (void)commandCtx; // unused parameter
    if (commandCtx.args.size() < 1)
    {
        return Result::error(400, "Missing filename.");
    }
    if (!isValidFilename(commandCtx.args[0].toString()))
    {
        return Result::error(400, "Invalid filename.");
    }
    return Result::success();
}
Result CreateCommand::execute(CommandContext &commandCtx, ClientContext *)
{
    (void)commandCtx; // unused parameter
    QString filename = commandCtx.args[0].toString();
    QFile file(filename);
    if (file.exists())
    {
        return Result::error(409, "File already exists.");
    }
    if (!file.open(QIODevice::WriteOnly))
    {
        return Result::error(500, "Failed to create file.");
    }
    file.close();
    return Result::success();
}

Result WriteCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    if (commandCtx.args.size() < 2)
    {
        return Result::error(400, "Missing filename or content.");
    }
    if (!isValidFilename(commandCtx.args[0].toString()))
    {
        return Result::error(400, "Invalid filename.");
    }
    return Result::success();
}

Result WriteCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    QFile file(commandCtx.args[0].toString());
    if (!file.exists())
        return Result::error(404, "File not found.");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return Result::error(500, "Failed to open file for writing.");
    }

    QTextStream out(&file);
    out << commandCtx.args[1].toString();
    file.close();
    return Result::success();
}
Result ReadCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    if (commandCtx.args.size() < 1)
    {
        return Result::error(400, "Missing filename.");
    }
    if (!isValidFilename(commandCtx.args[0].toString()))
    {
        return Result::error(400, "Invalid filename.");
    }
    return Result::success();
}
Result ReadCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    QFile file(commandCtx.args[0].toString());
    if (!file.exists())
        return Result::error(404, "File not found.");

    if (!file.open(QIODevice::ReadOnly))
    {
        return Result::error(500, "Failed to open file for reading.");
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    commandCtx.response = std::make_unique<ReadResponse>(content);

    return Result::success();
}

Result AppendCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    if (commandCtx.args.size() < 2)
    {
        return Result::error(400, "Missing filename or content.");
    }
    if (!isValidFilename(commandCtx.args[0].toString()))
    {
        return Result::error(400, "Invalid filename.");
    }
    return Result::success();
}
Result AppendCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    QFile file(commandCtx.args[0].toString());
    if (!file.exists())
        return Result::error(404, "File not found.");

    if (!file.open(QIODevice::Append))
    {
        return Result::error(500, "Failed to open file for appending.");
    }

    QTextStream out(&file);
    out << commandCtx.args[1].toString();
    file.close();
    return Result::success();
}
Result DeleteCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    if (commandCtx.args.size() < 1)
    {
        return Result::error(400, "Missing filename.");
    }
    if (!isValidFilename(commandCtx.args[0].toString()))
    {
        return Result::error(400, "Invalid filename.");
    }
    return Result::success();
}
Result DeleteCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    QFile file(commandCtx.args[0].toString());
    if (!file.exists())
        return Result::error(404, "File not found.");

    if (!file.remove())
        return Result::error(500, "Failed to delete file.");

    return Result::success();
}

Result ListCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx;  // unused parameter
    (void)commandCtx; // unused parameter
    return Result::success();
}
Result ListCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    QDir dir(QDir::currentPath());
    QStringList files = dir.entryList(QDir::Files);
    commandCtx.response = std::make_unique<ListResponse>(files);
    return Result::success();
}

Result RenameCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    if (commandCtx.args.size() < 2)
    {
        return Result::error(400, "Missing old or new filename.");
    }
    if (!isValidFilename(commandCtx.args[0].toString()))
    {
        return Result::error(400, "Invalid old filename.");
    }
    if (!isValidFilename(commandCtx.args[1].toString()))
    {
        return Result::error(400, "Invalid new filename.");
    }
    return Result::success();
}
Result RenameCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    QFile file(commandCtx.args[0].toString());
    if (!file.exists())
        return Result::error(404, "File not found.");

    if (!file.rename(commandCtx.args[1].toString()))
        return Result::error(500, "Failed to rename file.");

    return Result::success();
}
Result InfoCommand::validate(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    if (commandCtx.args.size() < 1)
    {
        return Result::error(400, "Missing filename.");
    }
    if (!isValidFilename(commandCtx.args[0].toString()))
    {
        return Result::error(400, "Invalid filename.");
    }
    return Result::success();
}
Result InfoCommand::execute(CommandContext &commandCtx, ClientContext *clientCtx)
{
    (void)clientCtx; // unused parameter
    QFile file(commandCtx.args[0].toString());
    if (!file.exists())
        return Result::error(404, "File not found.");

    QFileInfo fileInfo(file);
    qint64 size = fileInfo.size();
    QString lastModified = fileInfo.lastModified().toString(Qt::ISODate);

    commandCtx.response = std::make_unique<InfoResponse>(size, lastModified);
    return Result::success();
}