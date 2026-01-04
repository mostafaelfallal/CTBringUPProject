#pragma once
#include "Handler.h"
class Reader : public Handler
{
protected:
    void process(CommandContext &commandCtx, ClientContext *clientCtx) override
    {
        QByteArray data = clientCtx->getSocket()->readLine();
        QString msg = QString::fromUtf8(data).trimmed();
        commandCtx.rawText = msg;
        qDebug() << "> Reader : Received message:" << msg;
    }
};
