#include <gtest/gtest.h>

#include "../Server/converter.h"
#include "../Common.h"
#include "../Server/Server.h"
#include "../Client/Validator.h"
#include "../Client/JsonFormatter.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QJsonDocument>
TEST(CommandTest, AcceptsConnections)
{
    Server server;
    QTcpSocket client;
    client.connectToHost(QHostAddress::LocalHost, PORT);

    ASSERT_TRUE(client.waitForConnected(1000));
}