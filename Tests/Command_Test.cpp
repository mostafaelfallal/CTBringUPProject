#include <gtest/gtest.h>
#include <QTemporaryDir>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QTcpSocket>

#include "../Server/Command.h"
#include "../Server/Factory.h"
#include "../Server/ClientContext.h"
#include "../Common.h"

class CommandTests : public ::testing::Test {
    protected:
    QTemporaryDir tempDir;
    QString originalPath;
    QTcpSocket* dummySocket;
    ClientContext* context;

    void SetUp() override {
        ASSERT_TRUE(tempDir.isValid()) << "Failed to create temp dir";
        originalPath = QDir::currentPath();
        QDir::setCurrent(tempDir.path());
        dummySocket = new QTcpSocket();
        context = new ClientContext(dummySocket);
    }

    void TearDown() override {
        delete context;
        QDir::setCurrent(originalPath);
    }

    QJsonObject createPayload(const QStringList& args) {
        QJsonObject json;
        QJsonArray jsonArgs;
        for (const QString& arg : args) jsonArgs.append(arg);
        json["args"] = jsonArgs;
        return json;
    }
};

// ==========================================
// 1. Factory Tests
// ==========================================
TEST_F(CommandTests, FactoryCreatesCorrectTypes) {
    auto cmd1 = CommandFactory::createCommand(context, "AUTH");
    EXPECT_NE(dynamic_cast<AuthCommand*>(cmd1.get()), nullptr);

    auto cmd2 = CommandFactory::createCommand(context, "CREATE");
    EXPECT_NE(dynamic_cast<CreateCommand*>(cmd2.get()), nullptr);

    auto cmd3 = CommandFactory::createCommand(context, "UNKNOWN_CMD");
    EXPECT_EQ(cmd3, nullptr);
}

// ==========================================
// 2. Authentication Tests
// ==========================================
TEST_F(CommandTests, AuthSuccessAndFailure) {
    AuthCommand cmd(context);
    QJsonObject badReq = createPayload({ "wrongUser", "wrongPass" });
    QJsonObject badResp = cmd.execute(badReq);

    EXPECT_EQ(badResp["status"].toString().toStdString(), "ERROR");
    EXPECT_EQ(badResp["code"].toInt(), 401);
    EXPECT_FALSE(context->getIsAuthenticated());
    QJsonObject goodReq = createPayload({ USERNAME, PASSWORD });
    QJsonObject goodResp = cmd.execute(goodReq);

    EXPECT_EQ(goodResp["status"].toString().toStdString(), "OK");
    EXPECT_TRUE(context->getIsAuthenticated());
}

// ==========================================
// 3. File Operation Tests (Happy Path)
// ==========================================
TEST_F(CommandTests, FileLifecycle_CreateWriteReadDelete) {
    context->setIsAuthenticated(true);

    QString filename = "testfile.txt";

    CreateCommand createCmd(context);
    QJsonObject resp1 = createCmd.execute(createPayload({ filename }));
    EXPECT_EQ(resp1["status"].toString().toStdString(), "OK");
    EXPECT_TRUE(QFile::exists(filename));
    WriteCommand writeCmd(context);
    QString content = "Hello World";
    QJsonObject resp2 = writeCmd.execute(createPayload({ filename, content }));
    EXPECT_EQ(resp2["status"].toString().toStdString(), "OK");


    ReadCommand readCmd(context);
    QJsonObject resp3 = readCmd.execute(createPayload({ filename }));
    EXPECT_EQ(resp3["status"].toString().toStdString(), "OK");
    EXPECT_EQ(resp3["message"].toString().toStdString(), content.toStdString());


    DeleteCommand delCmd(context);
    QJsonObject resp4 = delCmd.execute(createPayload({ filename }));
    EXPECT_EQ(resp4["status"].toString().toStdString(), "OK");
    EXPECT_FALSE(QFile::exists(filename));
}

// ==========================================
// 4. Permission & Validation Tests
// ==========================================
TEST_F(CommandTests, CreateFailsWithoutAuth) {
    CreateCommand cmd(context);

    QJsonObject req = createPayload({ "hacker.txt" });
    QJsonObject resp = cmd.execute(req);

    EXPECT_EQ(resp["status"].toString().toStdString(), "ERROR");
    EXPECT_EQ(resp["code"].toInt(), 403);
    EXPECT_EQ(resp["message"].toString().toStdString(), "Authentication required.");
}

TEST_F(CommandTests, PreventPathTraversal) {
    context->setIsAuthenticated(true);
    CreateCommand cmd(context);

    QJsonObject req = createPayload({ "../badfile.txt" });
    QJsonObject resp = cmd.execute(req);

    EXPECT_EQ(resp["status"].toString().toStdString(), "ERROR");
    EXPECT_EQ(resp["code"].toInt(), 400);
}

TEST_F(CommandTests, WriteFailsIfFileMissing) {
    context->setIsAuthenticated(true);
    WriteCommand cmd(context);

    QJsonObject req = createPayload({ "ghost.txt", "data" });
    QJsonObject resp = cmd.execute(req);

    EXPECT_EQ(resp["code"].toInt(), 404);
}

// ==========================================
// 5. Append & Rename Tests
// ==========================================
TEST_F(CommandTests, AppendAndRename) {
    context->setIsAuthenticated(true);
    QString fname = "log.txt";


    CreateCommand(context).execute(createPayload({ fname }));
    WriteCommand(context).execute(createPayload({ fname, "Line1;" }));

    AppendCommand appendCmd(context);
    appendCmd.execute(createPayload({ fname, "Line2;" }));

    ReadCommand readCmd(context);
    QJsonObject readResp = readCmd.execute(createPayload({ fname }));
    EXPECT_EQ(readResp["message"].toString().toStdString(), "Line1;Line2;");


    RenameCommand renameCmd(context);
    QString newName = "old_log.txt";
    QJsonObject renameResp = renameCmd.execute(createPayload({ fname, newName }));

    EXPECT_EQ(renameResp["status"].toString().toStdString(), "OK");
    EXPECT_FALSE(QFile::exists(fname));
    EXPECT_TRUE(QFile::exists(newName));
}