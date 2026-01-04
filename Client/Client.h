#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QSocketNotifier>
#include <unistd.h>
#include "MessageBuffer.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer();

public slots:
    void sendData(const QString &text);

private slots:
    void onConnected();
    void onServerResponse();
    void onDisconnected();
    void onUserInput();

signals:
    void disconnected();

private:
    QTcpSocket *socket;

    MessageBuffer m_queue;
    QSocketNotifier *notifier;
};

#endif // CLIENT_H