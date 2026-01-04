#include "Command.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include "../Common.h"
// --- Helper for File Operations (Further reduces code duplication) ---
CommandResult withFile(const QString &filename, QIODevice::OpenMode mode, std::function<CommandResult(QFile &)> action)
{
    QFile file(filename);
    if (!file.exists() && !(mode & QIODevice::WriteOnly))
    {
        return CommandResult::Error(404, "File not found.");
    }

    if (!file.open(mode))
    {
        return CommandResult::Error(500, "Failed to open file.");
    }

    CommandResult res = action(file);
    file.close();
    return res;
}
bool isValidFilename(const QString &filename)
{
    if (filename.contains("/") || filename.contains("..") || filename.startsWith("/") || filename.startsWith(".") || filename.contains("~"))
    {
        return false;
    }
    return true;
}
// --- Command Implementations ---

CommandResult AuthCommand::perform(const QStringList &args)
{
    QString username = args[0];
    QString password = args[1];
    if (clientContext->getIsAuthenticated())
    {
        return CommandResult::Ok("Already authenticated.");
    }
    if (username == USERNAME && password == PASSWORD)
    {
        clientContext->setIsAuthenticated(true);
        return CommandResult::Ok("Authentication successful.");
    }

    clientContext->setIsAuthenticated(false);
    return CommandResult::Error(401, "Invalid username or password.");
}

CommandResult CreateCommand::perform(const QStringList &args)
{
    QString filename = args[0];
    if (!isValidFilename(filename))
    {
        return CommandResult::Error(400, "Invalid filename.");
    }

    QFile file(filename);
    if (file.exists())
    {
        return CommandResult::Error(409, "File already exists.");
    }

    if (!file.open(QIODevice::WriteOnly))
    {
        return CommandResult::Error(500, "Failed to create file.");
    }
    file.close();
    return CommandResult::Ok("Create command executed.");
}

CommandResult WriteCommand::perform(const QStringList &args)
{
    QFile file(args[0]);
    if (isValidFilename(args[0]) == false)
    {
        return CommandResult::Error(400, "Invalid filename.");
    }
    if (!file.exists())
        return CommandResult::Error(404, "File not found.");

    return withFile(args[0], QIODevice::WriteOnly | QIODevice::Truncate, [&](QFile &file)
                    {
        QTextStream out(&file);
        out << args[1];
        return CommandResult::Ok("Write command executed."); });
}

CommandResult ReadCommand::perform(const QStringList &args)
{
    if (isValidFilename(args[0]) == false)
    {
        return CommandResult::Error(400, "Invalid filename.");
    }
    return withFile(args[0], QIODevice::ReadOnly, [&](QFile &file)
                    {
        QTextStream in(&file);
        QString content = in.readAll();

        QJsonObject extra;
        extra["length"] = content.length();
        return CommandResult::Ok(content, extra); });
}

CommandResult AppendCommand::perform(const QStringList &args)
{
    if (isValidFilename(args[0]) == false)
    {
        return CommandResult::Error(400, "Invalid filename.");
    }
    QFile file(args[0]);
    if (!file.exists())
        return CommandResult::Error(404, "File not found.");

    return withFile(args[0], QIODevice::Append, [&](QFile &file)
                    {
        QTextStream out(&file);
        out << args[1];
        return CommandResult::Ok("Append command executed."); });
}

CommandResult DeleteCommand::perform(const QStringList &args)
{
    if (isValidFilename(args[0]) == false)
    {
        return CommandResult::Error(400, "Invalid filename.");
    }
    QFile file(args[0]);
    if (!file.exists())
        return CommandResult::Error(404, "File not found.");

    if (!file.remove())
        return CommandResult::Error(500, "Failed to delete file.");

    return CommandResult::Ok("Delete command executed.");
}

CommandResult ListCommand::perform(const QStringList &args)
{
    (void)args; // To avoid unused parameter warning
    QDir dir(QDir::currentPath());
    QStringList files = dir.entryList(QDir::Files);
    return CommandResult::Ok(files.join(" - "));
}

CommandResult RenameCommand::perform(const QStringList &args)
{
    if (isValidFilename(args[0]) == false)
    {
        return CommandResult::Error(400, "Invalid filename.");
    }
    QFile file(args[0]);
    if (!file.exists())
        return CommandResult::Error(404, "File not found.");

    if (!file.rename(args[1]))
        return CommandResult::Error(500, "Failed to rename file.");

    return CommandResult::Ok("Rename command executed.");
}

CommandResult InfoCommand::perform(const QStringList &args)
{
    if (isValidFilename(args[0]) == false)
    {
        return CommandResult::Error(400, "Invalid filename.");
    }
    QFile file(args[0]);
    if (!file.exists())
        return CommandResult::Error(404, "File not found.");

    QFileInfo fileInfo(file);
    QString msg = QString("size=%1 modified=%2")
                      .arg(fileInfo.size())
                      .arg(fileInfo.lastModified().toString(Qt::ISODate));

    return CommandResult::Ok(msg);
}