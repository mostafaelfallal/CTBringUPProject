#pragma once

#include <QString>
#include <QStringList>
class Validator
{
public:
    static bool validateCommand(const QString &command, QString &action, QStringList &args)
    {
        QString trimmedCommand = command.trimmed();
        if (trimmedCommand.isEmpty())
        {
            return false;
        }
        int firstSpaceIndex = trimmedCommand.indexOf(' ');
        if (firstSpaceIndex == -1)
        {
            action = trimmedCommand;
            args.clear();
        }
        else
        {
            action = trimmedCommand.left(firstSpaceIndex);
            QString argsString = trimmedCommand.mid(firstSpaceIndex + 1);
            args = argsString.trimmed().split(';', Qt::SkipEmptyParts);
        }
        return true;
    }
};