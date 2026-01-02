#ifndef INPUTWORKER_H
#define INPUTWORKER_H

#include <QObject>
#include <QTextStream>
#include <iostream>

class InputWorker : public QObject
{
    Q_OBJECT
    public slots:
    void process() {
        QTextStream qin(stdin);
        while (true) {
            QString line = qin.readLine();
            if (line.isNull()) break;
            emit userInputReceived(line);
        }
    }

    signals:
    void userInputReceived(const QString& text);
};

#endif // INPUTWORKER_H