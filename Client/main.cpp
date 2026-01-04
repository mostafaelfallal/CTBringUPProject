#include <QCoreApplication>
#include <QThread>
#include "Client.h"
#include "InputWorker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToServer();

    // // Setup Threading
    // QThread workerThread;
    // InputWorker* worker = new InputWorker;
    // worker->moveToThread(&workerThread);

    // Connect signals
    // QObject::connect(&workerThread, &QThread::started, worker, &InputWorker::process);
    // QObject::connect(worker, &InputWorker::userInputReceived, &client, &Client::sendData);

    // Cleanup hooks
    // QObject::connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    QObject::connect(&client, &Client::disconnected, &a, &QCoreApplication::quit);
    a.exec();
    // workerThread.start();

    // int result = a.exec();
    // workerThread.quit();
    // workerThread.wait();
    // return result;
}