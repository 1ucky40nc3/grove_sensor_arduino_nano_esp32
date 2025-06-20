/**
 * @brief The baud rate for serial communication.
 *
 * This constant sets the data transfer rate for the serial port,
 */
const unsigned long SERIAL_BAUD = 115200;

/**
 * @brief The delay in milliseconds after serial communication is initialized.
 *
 * This delay provides a brief pause after setting up the serial port,
 * allowing the serial connection to stabilize before any data transmission begins.
 * It can be useful to ensure that the connected device is ready to receive commands or data.
 */
const unsigned long DELAY_AFTER_SERIAL_INITIALIZED = 100;

/**
 * @brief The delay in milliseconds after each loop iteration.
 *
 * This constant defines the pause duration at the end of each main program loop cycle.
 * It's used to control the frequency of operations, such as sensor readings
 * or data logging, and to prevent overwhelming the system or connected devices.
 */
const unsigned long DELAY_AFTER_LOOP_ITERATION = 5000;

/**
 * @brief The name of the sensor as metadata for the `HM330XMeasurement` struct creation.
 *
 * This constant is used to output metadata about the HM330X sensor used to do the particulate measurements.
 */
const string MEASUREMENT_SENSOR = "HM330X";

/**
 * @brief The version of the sensor/setup as metadata for the `HM330XMeasurement` struct creation.
 *
 * This constant is used to output metadata about the the version/setup used to do the particulate measurements.
 */
const string MEASUREMENT_VERSION = "v1.0";