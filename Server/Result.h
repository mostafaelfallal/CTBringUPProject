#pragma once
#include <QString>

struct Result
{
    bool ok;
    int code;
    QString message;

    static Result success()
    {
        return {true, 200, ""};
    }

    static Result error(int code, QString msg)
    {
        return {false, code, std::move(msg)};
    }
};
