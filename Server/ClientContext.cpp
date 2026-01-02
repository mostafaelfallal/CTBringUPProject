#include "ClientContext.h"

ClientContext::ClientContext(QTcpSocket* socket, QObject* parent)
    : QObject(parent), m_socket(socket)
{
    m_socket->setParent(this); // Ensure socket is deleted with ClientContext
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientContext::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientContext::onSocketDisconnected);
}

void ClientContext::sendMessage(const QByteArray& message)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(message);
        m_socket->flush();
    }
}

QTcpSocket* ClientContext::getSocket()
{
    return m_socket;
}

void ClientContext::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    QString msg = QString::fromUtf8(data).trimmed();
    if (!msg.isEmpty()) emit messageReceived(msg, this);
}

void ClientContext::onSocketDisconnected()
{
    emit disconnected(this);
}