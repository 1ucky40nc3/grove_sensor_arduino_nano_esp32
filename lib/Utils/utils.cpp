#include <string>
#include "utils.h"
#include "measurement.h"

using namespace std;

HM330XMeasurement parseHm330xMeasurement(uint8_t *buf)
{
    // if (NULL == buf)
    //     return ERR_NULL;

    auto parse = [](int i, uint8_t *buf)
    { return (uint16_t)buf[i * 2] << 8 | buf[i * 2 + 1]; };

    HM330XData data;
    data.sensor_num = parse(1, buf);
    data.pm_010_spm = parse(2, buf);
    data.pm_025_spm = parse(3, buf);
    data.pm_100_spm = parse(4, buf);
    data.pm_010_ae = parse(5, buf);
    data.pm_025_ae = parse(6, buf);
    data.pm_100_ae = parse(7, buf);

    Description desc = {"HM330X", "v1.0"};
    Measurement<HM330XData> measurement;
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