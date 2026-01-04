#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include "ClientContext.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void onClientDisconnected(ClientContext *client);

private:
    QTcpServer *server;
    QList<ClientContext *> m_clients;
};

#endif // SERVER_H