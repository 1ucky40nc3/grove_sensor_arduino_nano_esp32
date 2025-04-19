#include <string>
#include "measure.h"

using namespace std;

string HM33XMeasurement::toJson()
{
    const string dataString = "{\"pm_010_spm\":" + to_string(data.pm_010_spm) +
                              ",\"pm_025_spm\":" + to_string(data.pm_025_spm) +
                              ",\"pm_100_spm\":" + to_string(data.pm_100_spm) +
                              ",\"pm_010_ae\":" + to_string(data.pm_010_ae) +
                              ",\"pm_025_ae\":" + to_string(data.pm_025_ae) +
                              ",\"pm_100_ae\":" + to_string(data.pm_100_ae) + "}";
    return "{\"sensor\":\"" + sensor + "\",\"version\":\"" + version + "\",\"data\":" + dataString + "}"; // Placeholder
}