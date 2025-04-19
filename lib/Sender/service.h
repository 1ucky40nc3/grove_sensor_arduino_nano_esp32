#pragma once

#include <string>

using namespace std;

class AbstractJsonDataSenderService
{
protected:
    string url;

    AbstractJsonDataSenderService(string url) : url(url) {}

public:
    virtual ~AbstractJsonDataSenderService() = default;
    virtual void send(string data) = 0;
};

class JsonDataSenderService : public AbstractJsonDataSenderService
{
public:
    JsonDataSenderService() : AbstractJsonDataSenderService("http://localhost:8080") {}
    void send(string data) override;
};
