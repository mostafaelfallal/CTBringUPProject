#ifndef CLIENTCONTEXT_H
#define CLIENTCONTEXT_H

#include <QObject>
#include <QTcpSocket>
#include "Handler.h"
class ClientContext : public QObject
{
    Q_OBJECT
public:
    explicit ClientContext(QTcpSocket *socket, QObject *parent = nullptr);
    void sendMessage(const QByteArray &message);
    QTcpSocket *getSocket();
    bool getIsAuthenticated() const;
    void setIsAuthenticated(bool authStatus);

signals:
    void messageReceived(const QString &message, ClientContext *sender);
    void disconnected(ClientContext *client);

private slots:
    void onReadyRead();
    void onSocketDisconnected();

private:
    QTcpSocket *m_socket;
    bool m_isAuthenticated = false;
    std::unique_ptr<Handler> chainHead;
};

#endif // CLIENTCONTEXT_H