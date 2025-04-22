#pragma once

#include <string>
#include <memory>
#include <Arduino.h>
#include <Seeed_HM330X.h>
#include "measure.h"

using namespace std;

template <typename T, typename S>
class AbstractSensorReader
{
protected:
    Description desc;
    S sensor;
    AbstractSensorReader(S sensor, Description desc) : sensor(sensor), desc(desc) {}

public:
    virtual bool init() = 0;
    virtual err_t read_measurement() = 0;
    virtual err_t parse_measurement() = 0;
    virtual Measurement<T> get_measurement() = 0;
    virtual IJsonSerializable get_json_serializable() = 0;
    virtual ~AbstractSensorReader() = default;
};

class HM330XSensorReader : public AbstractSensorReader<HM330XData, HM330X>
{
private:
    uint8_t buf[30];
    Measurement<HM330XData> measurement;

public:
    HM330XSensorReader(HM330X sensor) : AbstractSensorReader(sensor, {"HM330X", "v1"}) {};
    bool init() override;
    err_t parse_measurement() override;
    err_t read_measurement() override;
    Measurement<HM330XData> get_measurement() override;
    IJsonSerializable get_json_serializable() override;
};