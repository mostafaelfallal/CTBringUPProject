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
// TEST(CommandTest, AUTHTest)
// {
//     Server server;
//     QTcpSocket client;
//     client.connectToHost(QHostAddress::LocalHost, PORT);
//     ASSERT_TRUE(client.waitForConnected(1000));
//     QString line = "AUTH admin;admin";
//     QString action;
//     QStringList args;
//     ASSERT_TRUE(Validator::validateCommand(line, action, args));
//     QJsonDocument doc = JsonFormatter::toJsonDoc(action, args);
//     client.write(QString(doc.toJson(QJsonDocument::Compact) + "\n").toUtf8());
//     client.flush();
//     ASSERT_TRUE(client.waitForReadyRead(1000));
//     EXPECT_EQ(client.readAll(), QByteArray("pong"));
// }