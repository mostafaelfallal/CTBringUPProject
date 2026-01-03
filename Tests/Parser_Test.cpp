#include <gtest/gtest.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include "Parser.h"

TEST(ParserTests, ParseCommandWithArgs) {
    Parser parser;
    QString input = "AUTH user;password";

    QJsonObject result = parser.parseStringToJson(input);
    EXPECT_EQ(result["action"].toString().toStdString(), "AUTH");
    QJsonArray args = result["args"].toArray();
    ASSERT_EQ(args.size(), 2);
    EXPECT_EQ(args[0].toString().toStdString(), "user");
    EXPECT_EQ(args[1].toString().toStdString(), "password");
}

TEST(ParserTests, ParseCommandNoArgs) {
    Parser parser;
    QString input = "LIST";

    QJsonObject result = parser.parseStringToJson(input);

    EXPECT_EQ(result["action"].toString().toStdString(), "LIST");
    QJsonArray args = result["args"].toArray();
    EXPECT_TRUE(args.isEmpty());
}

TEST(ParserTests, ParseHandlesWhitespaceAndTrimming) {
    Parser parser;
    QString input = "  WRITE   file;  text  ";

    QJsonObject result = parser.parseStringToJson(input);

    EXPECT_EQ(result["action"].toString().toStdString(), "WRITE");
    QJsonArray args = result["args"].toArray();
    ASSERT_EQ(args.size(), 2);
    EXPECT_EQ(args[0].toString().toStdString(), "file");
    EXPECT_EQ(args[1].toString().toStdString(), "  text");
}

TEST(ParserTests, ParseSkipsEmptySemicolons) {
    Parser parser;
    QString input = "WRITE file;;text";

    QJsonObject result = parser.parseStringToJson(input);

    QJsonArray args = result["args"].toArray();
    ASSERT_EQ(args.size(), 2);
    EXPECT_EQ(args[0].toString().toStdString(), "file");
    EXPECT_EQ(args[1].toString().toStdString(), "text");
}


TEST(ParserTests, SerializeWithCode) {
    Parser parser;
    QJsonObject obj;
    obj["status"] = "ERROR";
    obj["code"] = 404;
    obj["message"] = "Not Found";

    QString result = parser.jsonToString(obj);
    EXPECT_EQ(result.toStdString(), "ERROR 404 Not Found");
}

TEST(ParserTests, SerializeWithoutCode) {
    Parser parser;
    QJsonObject obj;
    obj["status"] = "OK";
    obj["message"] = "Success";

    QString result = parser.jsonToString(obj);
    EXPECT_EQ(result.toStdString(), "OK Success");
}