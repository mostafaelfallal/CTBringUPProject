#pragma once
#include "Handler.h"
#include <QJsonDocument>
class Writer : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override
    {
        if (clientCtx->getSocket()->state() == QAbstractSocket::ConnectedState)
        {
            clientCtx->getSocket()->write(commandCtx.outText.toUtf8());
            clientCtx->getSocket()->flush();
            qDebug() << "> Writer : Sent message to client:" << commandCtx.outText;
        }
    }
};
