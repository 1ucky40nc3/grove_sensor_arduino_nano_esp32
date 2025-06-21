#include <string>
#include <cassert>
#include "utils.h"
#include "ChecksumException.h"
#include "BufferNullptfException.h"
#include "measurement.h"
#include "config.h"

using namespace std;

bool isValidHm330xBufferChecksum(uint8_t *buf)
{

    uint8_t sum = 0;
    for (int i = 0; i < 28; i++)
    {
        sum += buf[i];
    }
    return sum == buf[28];
}

HM330XMeasurement parseHm330xMeasurement(uint8_t *buf) noexcept(false)
{
    // The buffer can't be undefined here
    if (buf == nullptr)
    {
        throw BufferNulptrException("The buffer can't be a nullptr!");
    }
    // Make sure we only process valid buffers below
    if (!isValidHm330xBufferChecksum(buf))
    {
        throw ChecksumException("The checksum of the HM330X sensor buffer is not valid!");
    }

    // Parse two `uint8_t` values in the buffer into a single `uint16_t`
    auto parse = [](int i, uint8_t *buf) -> uint16_t
    { return (uint16_t)buf[i * 2] << 8 | buf[i * 2 + 1]; };

    HM330XData data;
    data.sensor_num = parse(1, buf);
    data.pm_010_spm = parse(2, buf);
    data.pm_025_spm = parse(3, buf);
    data.pm_100_spm = parse(4, buf);
    data.pm_010_ae = parse(5, buf);
    data.pm_025_ae = parse(6, buf);
    data.pm_100_ae = parse(7, buf);

    Description desc = {MEASUREMENT_SENSOR, MEASUREMENT_VERSION};
    HM330XMeasurement measurement;
    measurement.data = data;
    measurement.desc = desc;
    return measurement;
}

string convertHm330xMeasurementToJson(HM330XMeasurement &measurement)
{
    const string descString = "{\"sensor\":\"" + measurement.desc.sensor + "\",\"version\":\"" + measurement.desc.version + "\"}";
    const string dataString = "{\"pm_010_spm\":" + to_string(measurement.data.pm_010_spm) +
                              ",\"pm_025_spm\":" + to_string(measurement.data.pm_025_spm) +
                              ",\"pm_100_spm\":" + to_string(measurement.data.pm_100_spm) +
                              ",\"pm_010_ae\":" + to_string(measurement.data.pm_010_ae) +
                              ",\"pm_025_ae\":" + to_string(measurement.data.pm_025_ae) +
                              ",\"pm_100_ae\":" + to_string(measurement.data.pm_100_ae) + "}";
    return "{\"desc\":" + descString + ",\"data\":" + dataString + "}";
}