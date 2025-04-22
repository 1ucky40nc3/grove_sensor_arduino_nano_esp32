#pragma once

#include <string>
#include <cstdint>
#include <cassert>
#include "serialize.h"

using namespace std;

struct HM330XData
{
    uint8_t sensor_num;
    uint8_t pm_010_spm;
    uint8_t pm_025_spm;
    uint8_t pm_100_spm;
    uint8_t pm_010_ae;
    uint8_t pm_025_ae;
    uint8_t pm_100_ae;
};

struct Description
{
    string sensor;
    string version;
};

template <typename T>
struct Measurement
{
    Description desc;
    T data;
};

class JsonSerializableHM330XMeasurement : public IJsonSerializable
{
private:
    Measurement<HM330XData> measurement;

public:
    JsonSerializableHM330XMeasurement(Measurement<HM330XData> measurement) : measurement(measurement) {};
    string toJson() override;
};