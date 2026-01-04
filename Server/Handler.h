#pragma once
#include <memory>
#include "CommandContext.h"
class ClientContext;
class Handler
{
public:
    virtual ~Handler() = default;

    void setNext(std::unique_ptr<Handler> next)
    {
        next_ = std::move(next);
    }

    void handle(CommandContext &commandCtx, ClientContext *clientCtx)
    {
        process(commandCtx, clientCtx); // ALWAYS called
        if (next_)
            next_->handle(commandCtx, clientCtx);
    }

protected:
    virtual void process(CommandContext &commandCtx, ClientContext *clientCtx) = 0;

private:
    std::unique_ptr<Handler> next_;
};
