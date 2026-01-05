#include "ClientContext.h"
#include <QDebug>
#include "Command.h"
ClientContext::ClientContext(std::shared_ptr<Handler> chainHead, qintptr socketDescriptor)
    : m_socketDescriptor(socketDescriptor), chainHead(chainHead)
{
}
void ClientContext::start()
{
    m_socket = new QTcpSocket(); // created in worker thread
    if (!m_socket->setSocketDescriptor(m_socketDescriptor))
    {
        emit disconnected();
        return;
    }
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
    emit disconnected();
}
bool ClientContext::getIsAuthenticated() const
{
    return m_isAuthenticated;
}
void ClientContext::setIsAuthenticated(bool authStatus)
{
    m_isAuthenticated = authStatus;
}
