#include "Client.h"
#include "../Common.h"
#include "JsonFormatter.h"
#include "Validator.h"
Client::Client(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this)), notifier(nullptr)
{
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onServerResponse);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    notifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
    connect(notifier, &QSocketNotifier::activated, this, &Client::onUserInput);
}

void Client::connectToServer()
{
    socket->connectToHost(QHostAddress::LocalHost, PORT);
}

void Client::onConnected()
{
    qDebug() << "Connected to server, sending buffered messages...";
    while (!m_queue.isEmpty())
    {
        QString msg = m_queue.pop();
        qDebug() << "Sending buffered: " << msg;
        sendData(msg);
    }
}

void Client::onServerResponse()
{
    qDebug() << ">> " << socket->readAll();
}

void Client::sendData(const QString &text)
{
    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "Server offline. Queuing: " << text;
        m_queue.push(text);
        connectToServer();
    }
    else
    {
        socket->write((text + "\n").toUtf8());
        socket->flush();
    }
}

void Client::onDisconnected()
{
    qDebug() << "Disconnected from server.";
    emit disconnected();
}
void Client::onUserInput()
{
    QTextStream qin(stdin);
    QString line = qin.readLine();
    if (line.isNull())
    {
        notifier->setEnabled(false);
        return;
    }
    QString action;
    QStringList args;
    if (!Validator::validateCommand(line, action, args))
    {
        qDebug() << "Invalid command format.";
        return;
    }
    QJsonDocument doc = JsonFormatter::toJsonDoc(action, args);
    sendData(doc.toJson(QJsonDocument::Compact));
}