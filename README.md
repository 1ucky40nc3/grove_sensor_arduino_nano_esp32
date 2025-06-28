# grove_sensor_arduino_nano_esp32

Testing the Grove  - Laser PM2.5 Sensor with an Arduino Nano ESP32

## Getting Started

### Install the PlatformIO IDE VSCode Extension

Install the PlatformIO IDE extension from the VSCode extension marketplace (see workspace recommendations). You may be asked to install Python. You may follow the instructions [here](https://docs.platformio.org/en/latest/faq/install-python.html).

### Initialize the Project

In this example a PlatformIO project has already been created. The project configuration can be inspected in the [platformio.ini](./platformio.ini) file.

The `platformio` (or `pio`) command-line interface should be installed along the the extension. For the local development purposes you need to intialize the  command-line interface. Execute the following commands in the command-line:

```bash
pio project init
```

Note: The command-line has to be a PlatformIO terminal. You can create a new PlatformIO termincal by pressing the `PlatformIO: New Terminal` buttom in the bottom left of your VSCode window.

Run the `pio check` command to do a static code analysis to check if everything is setup correctly.

### Set up Configuration and Secrets

You can find sections below on how to handle [configuration](#configuration) and [secrets](#secrets) down below. Make to follow the instructions and you should be good to go.

### Connect the Hardware

For the project you need to have a:

- [Grove - Laser PM2.5 Sensor (HM3301)](https://wiki.seeedstudio.com/Grove-Laser_PM2.5_Sensor-HM3301/)
- [Ardunino Nano ESP32](https://docs.arduino.cc/tutorials/nano-esp32/cheat-sheet/)

Connect the Grove laser sensor according to the [offical instructions](https://wiki.seeedstudio.com/Grove-Laser_PM2.5_Sensor-HM3301/) to the Arduino Nano ESP32:

| Arduino Nano ESP32 | Grove Cable | Grove - Laser PM2.5 Sensor (HM3301) |
|--------------------|-------------|-------------------------------------|
| GND                | Black       | GND                                 |
| 3.3V               | Red         | VCC                                 |
| A4                 | White       | SDA                                 |
| A5                 | Yellow      | SCL                                 |

You may want to check the [Ardunino Nano ESP32 cheat sheet](https://docs.arduino.cc/tutorials/nano-esp32/cheat-sheet/) for the correct [power output](https://docs.arduino.cc/tutorials/nano-esp32/cheat-sheet/#power-considerations) and [I2C](https://docs.arduino.cc/tutorials/nano-esp32/cheat-sheet/#i2c) pins.

### Build and Upload the Code to a Arduino Nano ESP32

After installation and initialization you may build and upload the code to your device. Connect the Ardunino Nano ESP32 via USB. Then run the following commands (in a PlatformIO terminal):

```bash
# Check if your device can be detected
pio device list
# Build the code
pio run -e arduino_nano_esp32 -t build
# Upload the build
pio run -e arduino_nano_esp32 -t upload
```

As an alternative to the command you can also use the PlatformIO buttons in VSCode. You can find the buttons below. Make szre to select the correct (`arduino_nano_esp32`) environment for the upload.

### Run Tests

```bash
# Run test locally on your desktop
pio test -e desktop
# Run test on the device
pio test -e arduino_nano_esp32
```

#### Debug Tests

If you are using VSCode (which is recommended), use the following steps to debug your test runs:

1. Select the `desktop` environment to select your local machine as the build target
2. Open the testing module [test_desktop_main.cpp](test/test_desktop/test_desktop_main.cpp) in your editor
3. Go to the debug tab in VSCode
4. Launch the code with the `PIO Debug` configuration


This will automatically attach a gdb debugger and enable VSCode debugging.

## Documentation

### Configuration

Set the configuration in the [config.h](lib/Config/config.h) header file. Use the provided constants as they are used in the code.

### Secrets

Provide the secrets in the [secrets.h](lib/Config/secrets.h) header file. This file provides constants which are used in the code. As part of the setup you have to create the [secrets.h](lib/Config/secrets.h) file at the `lib/Config/secrets.h` path. Use the following template to create the file

```cpp
/**
 * @brief The WIFI SSID for a Wifi client.
 *
 * This Wifi SSID is used together with the `WIFI_PASSWORD` to connect to a Wifi network.
 */
const char *WIFI_SSID = "INSERT_YOUR_WIFI_SSID_HERE";

/**
 * @brief The Wifi password a Wifi client.
 *
 * This Wifi üassword is used together with the `WIFI_SSID` to connect to a Wifi network.
 */
const char *WIFI_PASSWORD = "INSERT_YOUR_WIFI_PASSWORD_HERE";

/**
 * @brief The hostname of a Prometheus Pushgateway server.
 *
 * We send our metrics data to this Prometheus Pushgateway server.
 */
const char *PUSHGATEWAY_HOST = "INSERT_YOUR_PUSHGATEWAY_HOST_HERE"; // Or the IP address of your Pushgateway

/**
 * @brief The PORT of a Prometheus Pushgateway server.
 *
 * We send our metrics data to this Prometheus Pushgateway server.
 */
const int PUSHGATEWAY_PORT = 30003;
```

## Troubleshooting

### Reset the Arduino Nano ESP32

Follow this [tutorial](https://support.arduino.cc/hc/en-us/articles/9810414060188-Reset-the-Arduino-bootloader-on-the-Nano-ESP32) to reset the bootloader of the Arduino Nano ESP32.