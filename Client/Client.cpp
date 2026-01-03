#include "Client.h"
#include "../Common.h"
Client::Client(QObject* parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, [this]() {
        onDisconnected();
            });
}

void Client::connectToServer()
{
    socket->connectToHost(QHostAddress::LocalHost, PORT);
}

void Client::onConnected()
{
    qDebug() << "Connected to server.";
}

void Client::onReadyRead()
{
    qDebug() << "Server:" << socket->readAll();
}

void Client::sendData(const QString& text)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(text.toUtf8());
        socket->flush();
    }
    else {
        qDebug() << "Not connected, trying to reconnect...";
        connectToServer();
    }
}

void Client::onDisconnected()
{
    qDebug() << "Disconnected from server.";
    emit disconnected();
}