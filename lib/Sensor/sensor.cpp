#include <Arduino.h>
#include <Seeed_HM330X.h>
#include "sensor.h"
#include "errno.h"

using namespace std;

err_sensor_t convertHM330XErrorCode(HM330XErrorCode error)
{
    switch (error)
    {
    case NO_ERROR:
        return NO_ERR;
    case ERROR_COMM:
        return ERR_CONN;
    case ERROR_OTHERS:
        return ERR_OTHER;
    default:
        return ERR_UNK;
    }
}

err_sensor_t HM330XSensor::init()
{
    const HM330XErrorCode error = this->sensor.init();
    return convertHM330XErrorCode(error);
}

err_sensor_t HM330XSensor::read_sensor_value(uint8_t *data)
{
    const HM330XErrorCode error = this->sensor.read_sensor_value(data, 29);
    return convertHM330XErrorCode(error);
}

err_sensor_t HM330XSensorReader::init()
{
    const err_sensor_t error = this->sensor.init();
    return error;
}

err_sensor_t HM330XSensorReader::read_measurement()
{
    if (this->sensor.read_sensor_value(this->buf))
    {
        Serial.println("HM330X read result failed!!!");
        return ERR_READ;
    }
    return NO_ERR;
}

err_sensor_t HM330XSensorReader::parse_measurement()
{
    if (NULL == this->buf)
        return ERR_NULL;

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
    return NO_ERR;
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
