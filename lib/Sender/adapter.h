#pragma once

#include <string>
#include "controller.h"
#include "serialize.h"

using namespace std;

class JsonSerializableDataSenderAdapter
{
private:
    JsonDataSenderController controller;

public:
    JsonSerializableDataSenderAdapter(JsonDataSenderController controller);
    void send(IJsonSerializable data);
};