
#include "Arduino.h"
#include "Seeed_HM330X.h"

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
  Serial.print(str);
  Serial.println(value);
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
    Serial.print(data[i], HEX);
    Serial.print("  ");
    if ((0 == (i) % 5) || (0 == i))
    {
      Serial.println(" ");
    }
  }
  uint8_t sum = 0;
  for (int i = 0; i < 28; i++)
  {
    sum += data[i];
  }
  if (sum != data[28])
  {
    Serial.println("wrong checkSum!!!!");
  }
  Serial.println(" ");
  Serial.println(" ");
  return NO_ERROR;
}

/*30s*/
void setup()
{
  Serial.begin(115200);
  // wait for Serial to come online
  while (!Serial)
    ;
  delay(100);
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
  parse_result_value(buf);
  parse_result(buf);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  delay(5000);
}
