#pragma once

#include <QJsonObject>
#include <QVariant>
#include <QStringList>
#include "ClientContext.h"

// Standardized result structure to separate logic from JSON formatting
struct CommandResult
{
    bool success = true;
    QString message;
    int errorCode = 200;
    QJsonObject data;
    static CommandResult Ok(const QString& msg, const QJsonObject& extra = {}) {
        return { true, msg, 200, extra };
    }
    static CommandResult Error(int code, const QString& msg) {
        return { false, msg, code, {} };
    }
};

class ICommand
{
    public:
    virtual ~ICommand() = default;
    virtual QJsonObject execute(const QJsonObject& cmd) = 0;
};

// Base class handles Auth, Args parsing, and JSON wrapping
class BaseCommand : public ICommand
{
    protected:
    ClientContext* clientContext;

    // Subclasses implement this specific logic
    virtual CommandResult perform(const QStringList& args) = 0;

    // Subclasses can override these configurations
    virtual bool requiresAuth() const { return true; }
    virtual int minArgs() const { return 0; }
    virtual QString argErrorMsg() const { return "Insufficient arguments."; }

    public:
    BaseCommand(ClientContext* ctx) : clientContext(ctx) {}

    QJsonObject execute(const QJsonObject& cmd) override
    {
        QJsonObject response;
        if (requiresAuth() && !clientContext->getIsAuthenticated())
        {
            response["status"] = "ERROR";
            response["code"] = 403;
            response["message"] = "Authentication required.";
            return response;
        }
        QStringList args = cmd["args"].toVariant().toStringList();
        if (args.size() < minArgs())
        {
            response["status"] = "ERROR";
            response["code"] = 400;
            response["message"] = argErrorMsg();
            return response;
        }
        CommandResult result = perform(args);
        response["status"] = result.success ? "OK" : "ERROR";

        if (result.errorCode != 200) response["code"] = result.errorCode;

        response["message"] = result.message;
        for (auto it = result.data.begin(); it != result.data.end(); ++it) {
            response[it.key()] = it.value();
        }

        return response;
    }
};