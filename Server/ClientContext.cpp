#include "ClientContext.h"
#include <QDebug>
#include "Reader.h"
#include "converter.h"
#include "Extractor.h"
#include "Validator.h"
#include "Builder.h"
#include "Command.h"
#include "Writer.h"
ClientContext::ClientContext(QTcpSocket *socket, QObject *parent)
    : QObject(parent), m_socket(socket)
{
    m_socket->setParent(this);
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
    validator->setNext(std::move(builder));
    extractor->setNext(std::move(validator));
    converter->setNext(std::move(extractor));
    reader->setNext(std::move(converter));

    chainHead = std::move(reader);

    connect(m_socket, &QTcpSocket::readyRead, this, &ClientContext::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientContext::onSocketDisconnected);
}

void ClientContext::sendMessage(const QByteArray &message)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState)
    {
        m_socket->write(message);
        m_socket->flush();
    }
}

QTcpSocket *ClientContext::getSocket()
{
    return m_socket;
}

void ClientContext::onReadyRead()
{
    while (m_socket->canReadLine())
    {
        qDebug() << "Received message from client";
        qDebug() << "Creating command processor chain.";
        // Create and Link the chain of responsibility

        CommandContext commandCtx;
        chainHead->handle(commandCtx, this);
    }
}
void ClientContext::onSocketDisconnected()
{
    emit disconnected(this);
}
bool ClientContext::getIsAuthenticated() const
{
    return m_isAuthenticated;
}
void ClientContext::setIsAuthenticated(bool authStatus)
{
    m_isAuthenticated = authStatus;
}