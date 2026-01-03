#ifndef INPUTWORKER_H
#define INPUTWORKER_H

#include <QObject>
#include <QTextStream>
#include <QSocketNotifier>
#include <unistd.h>

class InputWorker : public QObject
{
    Q_OBJECT
    public:
    explicit InputWorker(QObject* parent = nullptr) : QObject(parent), notifier(nullptr) {}

    public slots:
    void process() {
        notifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
        connect(notifier, &QSocketNotifier::activated, this, &InputWorker::onReadyRead);
    }

    private slots:
    void onReadyRead() {
        QTextStream qin(stdin);
        QString line = qin.readLine();
        if (line.isNull()) {
            notifier->setEnabled(false);
            return;
        }

        emit userInputReceived(line);
    }

    signals:
    void userInputReceived(const QString& text);

    private:
    QSocketNotifier* notifier;
};

#endif // INPUTWORKER_H