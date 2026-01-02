#include "Server.h"
#include "../Common.h"
#include "Parser.h"
Server::Server(QObject* parent)
    : QObject(parent), server(new QTcpServer(this))
{
    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (server->listen(QHostAddress::Any, PORT)) {
        qDebug() << "Server listening on port" << PORT;
    }
    else {
        qDebug() << "Server failed:" << server->errorString();
    }
}

void Server::onNewConnection()
{
    QTcpSocket* socket = server->nextPendingConnection();
    ClientContext* client = new ClientContext(socket, this);
    m_clients.append(client);

    connect(client, &ClientContext::messageReceived, this, &Server::onClientMessage);
    connect(client, &ClientContext::disconnected, this, &Server::onClientDisconnected);
    qDebug() << "New Client. Total:" << m_clients.size();
}

void Server::onClientMessage(const QString& message, ClientContext* sender)
{
    qDebug() << "Received message from client:" << message;
    // parse the message
    QJsonObject jsonMsg = Parser::parseStringToJson(message);
    qDebug() << "Parsed JSON:" << QJsonDocument(jsonMsg).toJson(QJsonDocument::Compact);
}

void Server::onClientDisconnected(ClientContext* client)
{
    m_clients.removeAll(client);
    client->deleteLater();
    qDebug() << "Client disconnected. Total:" << m_clients.size();
}