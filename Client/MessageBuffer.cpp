#include "MessageBuffer.h"

MessageBuffer::MessageBuffer(int size)
    : m_head(0), m_tail(0), m_count(0), m_maxSize(size)
{
    m_buffer.resize(size);
}

void MessageBuffer::push(const QString &message)
{
    if (m_count == m_maxSize)
    {
        qDebug() << "Buffer full! Dropping oldest:" << m_buffer[m_head];
        m_head = (m_head + 1) % m_maxSize;
        m_count--;
    }

    m_buffer[m_tail] = message;
    m_tail = (m_tail + 1) % m_maxSize;
    m_count++;
}

QString MessageBuffer::pop()
{
    if (m_count == 0)
        return QString();

    QString msg = m_buffer[m_head];
    m_head = (m_head + 1) % m_maxSize;
    m_count--;

    return msg;
}

bool MessageBuffer::isEmpty() const
{
    return m_count == 0;
}

void MessageBuffer::clear()
{
    m_head = 0;
    m_tail = 0;
    m_count = 0;
}