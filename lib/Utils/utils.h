#pragma once
#include <measurement.h>

/**
 * @brief Validates the checksum of a HM330X sensor data buffer.
 *
 * This function calculates the checksum of the provided buffer and compares it
 * to the checksum byte included in the buffer itself.
 *
 * @param buf A pointer to the uint8_t array containing the HM330X sensor data.
 * The buffer is expected to contain the full sensor output, including
 * the checksum byte.
 * @return True if the calculated checksum matches the buffer's checksum, false otherwise.
 */
bool isValidHm330xBufferChecksum(uint8_t *buf);

/**
 * @brief Parses a raw HM330X sensor data buffer into a structured measurement.
 *
 * This function takes a raw byte buffer from an HM330X sensor and
 * extracts the relevant particulate matter concentration data, populating
 * an `HM330XMeasurement` struct. It is assumed that the buffer has already
 * passed a checksum validation.
 *
 * @param buf A pointer to the uint8_t array containing the HM330X sensor data.
 * The buffer should be validated for checksum prior to calling this function.
 * @return An `HM330XMeasurement` struct containing the parsed sensor data.
 * @throws BufferNulptrException If the input buffer is a null pointer.
 * @throws ChecksumException If the checksum of the buffer turns out to be invalid.
 */
HM330XMeasurement parseHm330xMeasurement(uint8_t *buf);

/**
 * @brief Converts an HM330XMeasurement struct into a JSON string.
 *
 * This function serializes the data contained within an `HM330XMeasurement`
 * struct into a JSON formatted string. The JSON string will include all fields
 * from the `Description` and `HM330XData` sub-structures.
 *
 * @param measurement A reference to an `HM330XMeasurement` struct to be converted.
 * @return A std::string containing the JSON representation of the measurement data.
 */
string convertHm330xMeasurementToJson(HM330XMeasurement &measurement);
