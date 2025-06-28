
#include "Arduino.h"
#include "Seeed_HM330X.h"
#include "WiFi.h" // For ESP32. If using ESP8266, use <ESP8266WiFi.h>
#include "WiFiClient.h"
#include <measurement.h>
#include <utils.h>
#include <config.h>
#include <secrets.h>

HM330X sensor;
uint8_t buf[30];

void setup()
{
  // Initialize the serial connection
  Serial.begin(SERIAL_BAUD);
  // // wait for Serial to come online (only for testing/development purposes)
  // while (!Serial)
  //   ;
  delay(DELAY_AFTER_SERIAL_INITIALIZED);
  Serial.println("Serial start");

  // Intialize the sensor communication
  if (sensor.init())
  {
    Serial.println("HM330X init failed!!!");
    while (1)
      ;
  }

  // Initialize the Wifi connection
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendMetricsToPushgateway(String metricData)
{
  WiFiClient client;

  Serial.print("\nConnecting to Pushgateway...");

  if (!client.connect(PUSHGATEWAY_HOST, PUSHGATEWAY_PORT))
  {
    Serial.println("Connection failed!");
    return;
  }

  Serial.println("Connected to Pushgateway!");

  String metricsPath = String(PUSHGATEWAY_METRICS_PATH.c_str());
  String pushgatewayHost = String(PUSHGATEWAY_HOST);

  // Construct the HTTP POST request
  String httpRequest = "POST ";
  httpRequest += metricsPath;
  httpRequest += " HTTP/1.1\r\n";
  httpRequest += "Host: ";
  httpRequest += pushgatewayHost;
  httpRequest += "\r\n";
  httpRequest += "Content-Type: text/plain\r\n"; // Important for Prometheus metrics
  httpRequest += "Content-Length: ";
  httpRequest += metricData.length();
  httpRequest += "\r\n";
  httpRequest += "\r\n"; // Empty line to separate headers from body
  httpRequest += metricData;

  Serial.println("Sending HTTP POST request:");
  Serial.println(httpRequest);

  client.print(httpRequest);

  // Read the response from the server
  Serial.println("Waiting for response...");
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000)
    { // 5 second timeout
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println("\n");

  Serial.println("Closing connection.");
  client.stop();
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
      string metrics = convertHm330xMeasurementToMetrics(measurement);

      string serialString = metrics + "\n\n";
      Serial.println(serialString.c_str());
      String pushgatewayString = String(metrics.c_str());
      sendMetricsToPushgateway(pushgatewayString);
    }
    catch (const exception &ex)
    {
      Serial.println(ex.what());
    }
  }

  delay(DELAY_AFTER_LOOP_ITERATION);
}
