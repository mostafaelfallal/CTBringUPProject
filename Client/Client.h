#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
    public:
    explicit Client(QObject* parent = nullptr);
    void connectToServer();

    public slots:
    void sendData(const QString& text);

    private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

    signals:
    void disconnected();
    private:
    QTcpSocket* socket;
};

#endif // CLIENT_H