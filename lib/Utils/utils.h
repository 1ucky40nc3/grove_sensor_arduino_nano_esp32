#pragma once
#include <measurement.h>

HM330XMeasurement parseHm330xMeasurement(uint8_t *buf);

string convertHm330xMeasurementToJson(HM330XMeasurement &measurement);
