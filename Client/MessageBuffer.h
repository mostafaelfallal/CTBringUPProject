#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H

#include <QString>
#include <QVector>
#include <QDebug>

class MessageBuffer {
    public:
    explicit MessageBuffer(int size = 10);
    void push(const QString& message);
    QString pop();
    bool isEmpty() const;
    void clear();

    private:
    QVector<QString> m_buffer;
    int m_head;
    int m_tail;
    int m_count;
    int m_maxSize;
};

#endif // MESSAGEBUFFER_H