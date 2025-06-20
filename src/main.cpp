
#include "Arduino.h"
#include "Seeed_HM330X.h"
#include <measurement.h>
#include <utils.h>
#include <config.h>

HM330X sensor;
uint8_t buf[30];

void setup()
{
  Serial.begin(SERIAL_BAUD);
  // wait for Serial to come online
  while (!Serial)
    ;
  delay(DELAY_AFTER_SERIAL_INITIALIZED);
  Serial.println("Serial start");
  if (sensor.init())
  {
    Serial.println("HM330X init failed!!!");
    while (1)
      ;
  }
}

void loop()
{
  if (sensor.read_sensor_value(buf, 29))
  {
    Serial.println("HM330X read result failed!!!");
  }
  else
  {
    try
    {
      HM330XMeasurement measurement = parseHm330xMeasurement(buf);
      string json = convertHm330xMeasurementToJson(measurement);
      Serial.println(json.c_str());
    }
    catch (const exception &ex)
    {
      Serial.println(ex.what());
    }
  }

  delay(DELAY_AFTER_LOOP_ITERATION);
}
