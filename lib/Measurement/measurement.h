#pragma once

#include <string>
#include <cstdint>
#include <cassert>

using namespace std;

/**
 * @brief Represents particulate matter sensor data from the HM330X series.
 *
 * This struct holds various measurements related to particulate matter
 * concentration, including standard and atmospheric environment readings.
 *
 * Fields:
 * - @p sensor_num: Sensor number (corresponds to "sensor num" in device output).
 * - @p pm_010_spm: PM1.0 concentration (Standard particulate matter, unit: ug/m3).
 * - @p pm_025_spm: PM2.5 concentration (Standard particulate matter, unit: ug/m3).
 * - @p pm_100_spm: PM10 concentration (Standard particulate matter, unit: ug/m3).
 * - @p pm_010_ae: PM1.0 concentration (Atmospheric environment, unit: ug/m3).
 * - @p pm_025_ae: PM2.5 concentration (Atmospheric environment, unit: ug/m3).
 * - @p pm_100_ae: PM10 concentration (Atmospheric environment, unit: ug/m3).
 */
struct HM330XData
{
    uint16_t sensor_num;
    uint16_t pm_010_spm;
    uint16_t pm_025_spm;
    uint16_t pm_100_spm;
    uint16_t pm_010_ae;
    uint16_t pm_025_ae;
    uint16_t pm_100_ae;
};

/**
 * @brief Represents description metadata for a measurement.
 *
 * Field:
 * - @p sensor: The name of the sensor used to create the measurement.
 * - @p version: The version of the sensor or measurement setup.
 */
struct Description
{
    string sensor;
    string version;
};

/**
 * @brief A generic struct representing a measurement.
 *
 * This template struct combines descriptive metadata with the actual measurement data.
 *
 * @tparam T The type of the measurement data.
 *
 * Fields:
 * - @p desc: A @ref Description struct containing metadata about the measurement.
 * - @p data: The actual measurement data, whose type is determined by the template parameter `T`.
 */
template <typename T>
struct Measurement
{
    Description desc;
    T data;
};

/**
 * @brief A type definition for a HM330X particulate matter measurement.
 *
 * This typedef creates a specific @ref Measurement type for @ref HM330XData,
 * making it easier to declare measurements from HM330X sensors.
 */
typedef Measurement<HM330XData> HM330XMeasurement;