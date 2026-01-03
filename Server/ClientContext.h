#ifndef CLIENTCONTEXT_H
#define CLIENTCONTEXT_H

#include <QObject>
#include <QTcpSocket>

class ClientContext : public QObject
{
    Q_OBJECT
    public:
    explicit ClientContext(QTcpSocket* socket, QObject* parent = nullptr);
    void sendMessage(const QByteArray& message);
    QTcpSocket* getSocket(); // useful for logging
    bool getIsAuthenticated() const;
    void setIsAuthenticated(bool authStatus);

    signals:
    void messageReceived(const QString& message, ClientContext* sender);
    void disconnected(ClientContext* client);

    private slots:
    void onReadyRead();
    void onSocketDisconnected();

    private:
    QTcpSocket* m_socket;
    bool m_isAuthenticated = false;
};

#endif // CLIENTCONTEXT_H