#pragma once

#include <QString>
class IResponse
{
public:
    virtual ~IResponse() = default;
    virtual QString toText() const = 0;
};

class ReadResponse : public IResponse
{
public:
    ReadResponse(const QString &content) : content_(content) {}
    QString toText() const override
    {
        return content_;
    }

private:
    QString content_;
};
class InfoResponse : public IResponse
{
private:
    // size , last modified
    qint64 size_;
    QString lastModified_;

public:
    InfoResponse(qint64 size, const QString &lastModified)
        : size_(size), lastModified_(lastModified) {}
    QString toText() const override
    {
        return QString("size=%1 modified=%2").arg(size_).arg(lastModified_);
    }
};

class ListResponse : public IResponse
{
private:
    QStringList content_;

public:
    ListResponse(const QStringList &content) : content_(content) {}
    QString toText() const override
    {
        return content_.join(" ");
    }
};

class CreateResponse : public IResponse
{
public:
    QString toText() const override
    {
        return "Created";
    }
};
class AuthResponse : public IResponse
{
public:
    QString toText() const override
    {
        return "Authenticated";
    }
};

class DeleteResponse : public IResponse
{
public:
    QString toText() const override
    {
        return "Deleted";
    }
};

class AppendResponse : public IResponse
{
public:
    QString toText() const override
    {
        return "Appended";
    }
};
class WriteResponse : public IResponse
{
public:
    QString toText() const override
    {
        return "Written";
    }
};

class RenameResponse : public IResponse
{
public:
    QString toText() const override
    {
        return "Renamed";
    }
};