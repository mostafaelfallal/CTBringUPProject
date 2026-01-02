#include <QCoreApplication>
#include <QThread>
#include "Client.h"
#include "InputWorker.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToServer();

    // Setup Threading
    QThread workerThread;
    InputWorker* worker = new InputWorker;
    worker->moveToThread(&workerThread);

    // Connect signals
    QObject::connect(&workerThread, &QThread::started, worker, &InputWorker::process);
    QObject::connect(worker, &InputWorker::userInputReceived, &client, &Client::sendData);

    // Cleanup hooks
    QObject::connect(&a, &QCoreApplication::aboutToQuit, &workerThread, &QThread::quit);
    QObject::connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

    workerThread.start();

    return a.exec();
}