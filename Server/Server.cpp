#include "Server.h"
#include "../Common.h"
#include "Builder.h"
#include "Reader.h"
#include "converter.h"
#include "Extractor.h"
#include "Validator.h"
#include "Builder.h"
#include "Command.h"
#include "Writer.h"
#include <QThread>
Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    if (listen(QHostAddress::Any, PORT))
    {
        qDebug() << "Server listening on port" << PORT;
        // Create and Link the chain of responsibility
        std::unique_ptr<Handler> reader = std::make_unique<Reader>();
        std::unique_ptr<Handler> converter = std::make_unique<TextJsonConverter>();
        std::unique_ptr<Handler> extractor = std::make_unique<Extractor>();
        std::unique_ptr<Handler> validator = std::make_unique<ProtocolValidator>();
        std::unique_ptr<Handler> builder = std::make_unique<CommandBuilder>();
        std::unique_ptr<Handler> executor = std::make_unique<CommandExecutor>();
        std::unique_ptr<Handler> objectConverter = std::make_unique<ObjectTextConverter>();
        std::unique_ptr<Handler> writer = std::make_unique<Writer>();
        // link from last to first
        objectConverter->setNext(std::move(writer));
        executor->setNext(std::move(objectConverter));
        builder->setNext(std::move(executor));
        extractor->setNext(std::move(builder));
        validator->setNext(std::move(extractor));
        converter->setNext(std::move(validator));
        reader->setNext(std::move(converter));
        chainHead = std::move(reader);
        qDebug() << "Command processor chain created.";
    }
    else
    {
        qDebug() << "Server failed:" << errorString();
    }
}

void Server::onClientDisconnected()
{
    m_clientCounter--;
    qDebug() << "Client disconnected. Total:" << m_clientCounter;
}
// Override the incomingConnection method to handle new connections
void Server::incomingConnection(qintptr socketDescriptor)
{
    QThread *thread = new QThread(this);
    ClientContext *client = new ClientContext(chainHead, socketDescriptor);
    client->moveToThread(thread);
    // link starting
    connect(thread, &QThread::started, client, &ClientContext::start);
    // link cleanup
    connect(client, &ClientContext::disconnected, thread, &QThread::quit);
    connect(thread, &QThread::finished, client, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
    m_clientCounter++;
    qDebug() << "New Client. Total:" << m_clientCounter;
}
