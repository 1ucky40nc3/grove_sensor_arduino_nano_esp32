#pragma once

#include <string>
#include <cstdint>
#include <cassert>
#include "serialize.h"

using namespace std;

struct HM330XData
{
    uint8_t pm_010_spm;
    uint8_t pm_025_spm;
    uint8_t pm_100_spm;
    uint8_t pm_010_ae;
    uint8_t pm_025_ae;
    uint8_t pm_100_ae;
};

template <typename T>
class AbstractMeasurement : public IJsonSerializable
{
protected:
    string sensor;
    string version;

    T data;

    AbstractMeasurement(string sensor, string version, T data) : sensor(sensor), version(version), data(data)
    {
    }

public:
    virtual string toJson() = 0;
    virtual ~AbstractMeasurement() = default;
};

class HM33XMeasurement : public AbstractMeasurement<HM330XData>
{
public:
    HM33XMeasurement(HM330XData data) : AbstractMeasurement("HM33X", "v1.0", data) {} // Define sensor and version here
    string toJson() override;
};