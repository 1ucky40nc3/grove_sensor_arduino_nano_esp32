#pragma once

#include <string>

using namespace std;

class IJsonSerializable
{
public:
    virtual string toJson();
    virtual ~IJsonSerializable() = default;
};