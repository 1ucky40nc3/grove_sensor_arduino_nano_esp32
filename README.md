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

### Run Tests

```bash
# Run test locally on your desktop
pio test -e desktop
# Run test on the device
pio test -e arduino_nano_esp32
```

## Documentation

### Software Architecture

Software architecture patterns and principles:

- SOLID principles
- interface pattern
- MVC pattern
- Composition over inheritence

```mermaid
classDiagram
    class IJsonSerializable {
        <<interface>>
        + toJson(): string
    }
    class HM3301V1Data {
        + pm_010_spm: int
        + pm_025_spm: int
        + pm_100_spm: int
        + pm_010_ae: int
        + pm_025_ae: int
        + pm_100_ae: int
        + toJson(): string
    }
    class Measurement~T: IJsonSerializable~{
        + sensor: string
        + version: string
        + data: ~T~
        + toJson(): string
    }
    class IQueue~T~ {
        + add(T): void
        + pop(): T
    }
    class SequentialQueue~T~ {
        + values: T[]
        + add(T): void
        + pop(): T
    }
    class ISensorReader~T~ {
        <<interface>>
        + sensor: string
        + version: string
        + read(): Measurement~T~
    }
    class HM3301V1SensorReader~HM3301V1Data~ {
        + sensor: string
        + version: string
        + read(): Measurement~HM3301V1Data~
    }
    class IJsonDataSender {
        + send(data: string): void
    }
    class JsonDataSenderService {
        + send(data: string): void
    }
    class JsonDataSenderController {
        + send(data: string): void
    }
    class JsonDataSenderAdapter {
        + send(send: IJsonSerializable): void
    }
    HM3301V1Data --|> IJsonSerializable
    Measurement --|> IJsonSerializable
    SequentialQueue --|> IQueue
    HM3301V1SensorReader --|> SensorReader
    JsonDataSenderService --|> IJsonDataSender
    JsonDataSenderController ..> JsonDataSenderService : uses
    JsonDataSenderAdapter ..> JsonDataSenderController
```

The Arduino sketch initializes a system for reading data from an HM3301 Grove - Laser PM 2.5 sensor, queuing these measurements, and sending them as JSON strings to a web service.

```mermaid
sequenceDiagram
    participant Arduino as Arduino Board
    participant SensorReader as HM3301V1SensorReader
    participant Queue as SequentialQueue<Measurement<HM3301V1Data>>
    participant Adapter as JsonDataSenderAdapter
    participant Controller as JsonDataSenderController
    participant Service as JsonDataSenderService
    participant WebService as Web Service

    Note over Arduino: setup()

    Arduino ->> SensorReader: Initialize
    Arduino ->> Queue: Initialize
    Arduino ->> Adapter: Initialize
    Arduino ->> Controller: Initialize (with Service)
    Arduino ->> Service: Initialize

    Note over Arduino: loop()

    Arduino ->> SensorReader: read()
    SensorReader -->> Arduino: Measurement<HM3301V1Data>
    Arduino ->> Queue: add(Measurement<HM3301V1Data>)
    Arduino ->> Queue: pop()
    Queue -->> Arduino: Measurement<HM3301V1Data>
    Arduino ->> Adapter: send(Measurement<HM3301V1Data>)
    Adapter ->> Controller: send(JSON string)
    Controller ->> Service: send(JSON String)
    Service ->> WebService: Send JSON Data
```