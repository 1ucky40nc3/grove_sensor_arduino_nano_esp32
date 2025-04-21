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