#pragma once

#include <string>
#include "service.h"

using namespace std;

class JsonDataSenderController
{
private:
    JsonDataSenderService service;

public:
    JsonDataSenderController(JsonDataSenderService service);
    void send(string data);
};