typedef enum
{
    /** There is no error. */
    NO_ERR = 0,
    /** An error during the sensor read. */
    ERR_READ = -1,
    /** The data read from the sensor has a null value (maps to ERROR_PARAM of HM330XErrorCode). */
    ERR_NULL = -2,
    /** Some error happened during the communication with the sensor (maps to ERROR_COMM of HM330XErrorCode). */
    ERR_CONN = -3,
    /** Some other error happened (maps to ERROR_OTHERS of HM330XErrorCode). */
    ERR_OTHER = -4,
    /** Some unknown error occured. */
    ERR_UNK = -5
} err_sensor_t;