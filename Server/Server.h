#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include "ClientContext.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private slots:
    void onClientDisconnected();

private:
    uint32_t m_clientCounter = 0;
    std::shared_ptr<Handler> chainHead;

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H