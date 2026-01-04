#pragma once
#include "ICommand.h"
#include "CommandContext.h"
#include "ClientContext.h"
#include "Result.h"
#include "Response.h"

class AuthCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *) override;
    Result execute(CommandContext &commandCtx, ClientContext *) override;
};

class CreateCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *) override;
    Result execute(CommandContext &commandCtx, ClientContext *) override;
};

class WriteCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *clientCtx) override;
    Result execute(CommandContext &commandCtx, ClientContext *clientCtx) override;
};

class ReadCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *clientCtx) override;
    Result execute(CommandContext &commandCtx, ClientContext *clientCtx) override;
};

class AppendCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *clientCtx) override;
    Result execute(CommandContext &commandCtx, ClientContext *clientCtx) override;
};

class DeleteCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *clientCtx) override;
    Result execute(CommandContext &commandCtx, ClientContext *clientCtx) override;
};
class ListCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *clientCtx) override;
    Result execute(CommandContext &commandCtx, ClientContext *clientCtx) override;
};
class RenameCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *clientCtx) override;
    Result execute(CommandContext &commandCtx, ClientContext *clientCtx) override;
};

class InfoCommand : public BaseCommand
{
public:
    using BaseCommand::BaseCommand;
    Result validate(CommandContext &commandCtx, ClientContext *clientCtx) override;
    Result execute(CommandContext &commandCtx, ClientContext *clientCtx) override;
};