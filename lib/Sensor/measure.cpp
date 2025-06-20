#include <string>
#include "measure.h"

using namespace std;

string JsonSerializableHM330XMeasurement::toJson()
{
    const string descString = "{\"sensor\":\"" + this->measurement.desc.sensor + "\",\"version\":\"" + this->measurement.desc.version + "\"}";
    const string dataString = "{\"pm_010_spm\":" + to_string(this->measurement.data.pm_010_spm) +
                              ",\"pm_025_spm\":" + to_string(this->measurement.data.pm_025_spm) +
                              ",\"pm_100_spm\":" + to_string(this->measurement.data.pm_100_spm) +
                              ",\"pm_010_ae\":" + to_string(this->measurement.data.pm_010_ae) +
                              ",\"pm_025_ae\":" + to_string(this->measurement.data.pm_025_ae) +
                              ",\"pm_100_ae\":" + to_string(this->measurement.data.pm_100_ae) + "}";
    return "{\"desc\":" + descString + ",\"data\":" + dataString + "}";
}