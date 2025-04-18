#include <string>
#include "measure.h"

using namespace std;

HM330XData::HM330XData(uint8_t pm010_spm, uint8_t pm025_spm, uint8_t pm100_spm,
                       uint8_t pm010_ae, uint8_t pm025_ae, uint8_t pm100_ae)
    : pm_010_spm(pm010_spm), pm_025_spm(pm025_spm), pm_100_spm(pm100_spm),
      pm_010_ae(pm010_ae), pm_025_ae(pm025_ae), pm_100_ae(pm100_ae)
{
}

string HM330XData::toJson()
{
    {
        return "{ \"pm_010_spm\": " + to_string(pm_010_spm) +
               ", \"pm_025_spm\": " + to_string(pm_025_spm) +
               ", \"pm_100_spm\": " + to_string(pm_100_spm) +
               ", \"pm_010_ae\": " + to_string(pm_010_ae) +
               ", \"pm_025_ae\": " + to_string(pm_025_ae) +
               ", \"pm_100_ae\": " + to_string(pm_100_ae) + " }";
    }
}
