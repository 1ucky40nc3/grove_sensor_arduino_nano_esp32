#pragma once

#include <string>

using namespace std;

class IJsonSerializeable
{
public:
    virtual string toJson();
};
