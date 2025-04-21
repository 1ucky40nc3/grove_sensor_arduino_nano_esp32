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
    S sensor;
    AbstractSensorReader(S sensor) : sensor(sensor) {}

public:
    virtual bool init() = 0;
    virtual std::unique_ptr<AbstractMeasurement<T>> read() = 0;
    virtual ~AbstractSensorReader() = default;
};

class HM330XSensorReader : public AbstractSensorReader<HM330XData, HM330X>
{
public:
    HM330XSensorReader(HM330X sensor) : AbstractSensorReader(sensor) {};
    bool init() override;
    std::unique_ptr<AbstractMeasurement<HM330XData>> read() override;
};