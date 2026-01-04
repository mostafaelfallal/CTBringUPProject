#ifndef COMMANDCONTEXT_H
#define COMMANDCONTEXT_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <memory>
#include "Response.h"
#include "Result.h"
struct CommandContext
{
    // Input
    QString rawText;

    // Transport
    QJsonObject json;
    QString action;
    QJsonArray args;

    // Domain
    std::unique_ptr<class ICommand> command;

    // Output
    std::unique_ptr<IResponse> response;
    QString outText;

    // Flow control
    Result result = Result::success();
};

#endif // COMMANDCONTEXT_H