#include <QCoreApplication>
#include <QThread>
#include "Client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToServer();
    QObject::connect(&client, &Client::disconnected, &a, &QCoreApplication::quit);
    a.exec();
}