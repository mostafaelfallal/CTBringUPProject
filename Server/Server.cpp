#include "Server.h"
#include "../Common.h"
#include "Parser.h"
#include "Factory.h"

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
    qDebug() << "Parsed JSON:" << QJsonDocument(jsonMsg).toJson(QJsonDocument::Indented);
    // Factorty Pattern to get the appropriate Command object could be used here
    std::unique_ptr<ICommand> command = CommandFactory::createCommand(sender, jsonMsg["action"].toString());
    QJsonObject response;
    if (command) {
        response = command->execute(jsonMsg);
    }
    else {
        response["status"] = "ERROR";
        response["code"] = 400;
        response["message"] = "Unknown command.";
    }
    qDebug() << "Response JSON:" << QJsonDocument(response).toJson(QJsonDocument::Indented);
    QString responseStr = Parser::jsonToString(response) + "\n";
    sender->sendMessage(responseStr.toUtf8());
}

void Server::onClientDisconnected(ClientContext* client)
{
    m_clients.removeAll(client);
    client->deleteLater();
    qDebug() << "Client disconnected. Total:" << m_clients.size();
}