
#include "Arduino.h"
#include "Seeed_HM330X.h"

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
#define SERIAL Serial
#endif

HM330X sensor;
uint8_t buf[30];

const char *str[] = {
    "sensor num: ",
    "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
    "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
    "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
    "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
    "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
    "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
};

err_t print_result(const char *str, uint16_t value)
{
  if (NULL == str)
    return ERROR_PARAM;
  SERIAL.print(str);
  SERIAL.println(value);
  return NO_ERROR;
}

/*parse buf with 29 u8-data*/
err_t parse_result(uint8_t *data)
{
  uint16_t value = 0;
  err_t NO_ERROR;
  if (NULL == data)
    return ERROR_PARAM;
  for (int i = 1; i < 8; i++)
  {
    value = (uint16_t)data[i * 2] << 8 | data[i * 2 + 1];
    print_result(str[i - 1], value);
  }
}

err_t parse_result_value(uint8_t *data)
{
  if (NULL == data)
    return ERROR_PARAM;
  for (int i = 0; i < 28; i++)
  {
    SERIAL.print(data[i], HEX);
    SERIAL.print("  ");
    if ((0 == (i) % 5) || (0 == i))
    {
      SERIAL.println(" ");
    }
  }
  uint8_t sum = 0;
  for (int i = 0; i < 28; i++)
  {
    sum += data[i];
  }
  if (sum != data[28])
  {
    SERIAL.println("wrong checkSum!!!!");
  }
  SERIAL.println(" ");
  SERIAL.println(" ");
  return NO_ERROR;
}

/*30s*/
void setup()
{
  SERIAL.begin(115200);
  delay(100);
  SERIAL.println("Serial start");
  if (sensor.init())
  {
    SERIAL.println("HM330X init failed!!!");
    while (1)
      ;
  }
}

void loop()
{
  if (sensor.read_sensor_value(buf, 29))
  {
    SERIAL.println("HM330X read result failed!!!");
  }
  parse_result_value(buf);
  parse_result(buf);
  SERIAL.println(" ");
  SERIAL.println(" ");
  SERIAL.println(" ");
  delay(5000);
}
