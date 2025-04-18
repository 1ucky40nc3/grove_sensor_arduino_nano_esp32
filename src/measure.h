#pragma once

#include <string>
#include "serialize.h"

using namespace std;

class HM330XData : public IJsonSerializeable
{
private:
    uint8_t pm_010_spm;
    uint8_t pm_025_spm;
    uint8_t pm_100_spm;
    uint8_t pm_010_ae;
    uint8_t pm_025_ae;
    uint8_t pm_100_ae;

public:
    // Constructor declaration
    HM330XData(uint8_t pm010_spm, uint8_t pm025_spm, uint8_t pm100_spm,
               uint8_t pm010_ae, uint8_t pm025_ae, uint8_t pm100_ae);
    string toJson();
};

template <typename Data>
class Measurement : public IJsonSerializeable
{
public:
    string sensor;
    string version;
    Data data;
    string toJson();
};
