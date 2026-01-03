#pragma once
#include "ICommand.h"

class AuthCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand; // Use parent constructor
    protected:
    CommandResult perform(const QStringList& args) override;
    bool requiresAuth() const override { return false; } // Auth cmd doesn't need auth
    int minArgs() const override { return 2; }
    QString argErrorMsg() const override { return "Insufficient arguments for AUTH command."; }
};

class CreateCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 1; }
    QString argErrorMsg() const override { return "Insufficient arguments for CREATE command."; }
};

class WriteCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 2; }
    QString argErrorMsg() const override { return "Insufficient arguments for WRITE command."; }
};

class ReadCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 1; }
};

class AppendCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 2; }
};

class DeleteCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 1; }
};

class ListCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 0; }
};

class RenameCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 2; }
};

class InfoCommand : public BaseCommand {
    public:
    using BaseCommand::BaseCommand;
    protected:
    CommandResult perform(const QStringList& args) override;
    int minArgs() const override { return 1; }
};