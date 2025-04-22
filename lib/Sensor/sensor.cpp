#include <Arduino.h>
#include <Seeed_HM330X.h>
#include "sensor.h"

using namespace std;

bool isHM330XInitSuccess(HM330XErrorCode error)
{
    switch (error)
    {
    case NO_ERROR:
        return true;
    default:
        return false;
    }
}

bool HM330XSensorReader::init()
{
    const HM330XErrorCode error = this->sensor.init();
    return isHM330XInitSuccess(error);
}

err_t HM330XSensorReader::read_measurement()
{
    if (this->sensor.read_sensor_value(this->buf, 29))
    {
        Serial.println("HM330X read result failed!!!");
    }
}

err_t HM330XSensorReader::parse_measurement()
{
    if (NULL == this->buf)
        return ERROR_PARAM;

    auto parse = [](int i, uint8_t *buf)
    { return (uint16_t)buf[i * 2] << 8 | buf[i * 2 + 1]; };

    HM330XData data;
    data.sensor_num = parse(1, this->buf);
    data.pm_010_spm = parse(2, this->buf);
    data.pm_025_spm = parse(3, this->buf);
    data.pm_100_spm = parse(4, this->buf);
    data.pm_010_ae = parse(5, this->buf);
    data.pm_025_ae = parse(6, this->buf);
    data.pm_100_ae = parse(7, this->buf);

    Measurement<HM330XData> measurement;
    measurement.data = data;
    measurement.desc = this->desc;
    this->measurement = measurement;
}

Measurement<HM330XData> HM330XSensorReader::get_measurement()
{
    return this->measurement;
}

IJsonSerializable HM330XSensorReader::get_json_serializable()
{
    JsonSerializableHM330XMeasurement measurement(this->measurement);
    return measurement;
}
