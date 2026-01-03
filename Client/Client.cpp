#include "Client.h"
#include "../Common.h"
Client::Client(QObject* parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
}

void Client::connectToServer()
{
    socket->connectToHost(QHostAddress::LocalHost, PORT);
}

void Client::onConnected()
{
    qDebug() << "Connected to server, sending buffered messages...";
    while (!m_queue.isEmpty()) {
        QString msg = m_queue.pop();
        qDebug() << "Sending buffered: " << msg;
        sendData(msg);
    }
}

void Client::onReadyRead()
{
    qDebug() << "Server:" << socket->readAll();
}

void Client::sendData(const QString& text)
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Server offline. Queuing: " << text;
        m_queue.push(text);
        connectToServer();
    }
    else {
        socket->write((text + "\n").toUtf8());
        socket->flush();

    }
}

void Client::onDisconnected()
{
    qDebug() << "Disconnected from server.";
    emit disconnected();
}