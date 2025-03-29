# ESP8266 ElegantOTA Updater

This project demonstrates an over‑the‑air (OTA) firmware updater for the ESP8266 using the [ElegantOTA](https://github.com/ayushsharma82/ElegantOTA) library—now refactored to decouple the OTA update logic from the web server code. The firmware connects to a Wi‑Fi network (with credentials injected via an environment file), sets up an asynchronous HTTP web server, and enables OTA firmware updates without needing a USB connection.

---

## Features

- **Decoupled OTA Module:**  
  OTA update functionality is encapsulated in its own module (`OTAUpdater`), allowing integration with any web server instance.
  
- **Wi‑Fi Connectivity via Environment Variables:**  
  Wi‑Fi credentials (SSID and password) are injected at build time from a `.env` file using PlatformIO build flags.
  
- **Asynchronous Web Server:**  
  Utilizes ESPAsyncWebServer (and ESPAsyncTCP/AsyncTCP) to run a non‑blocking HTTP server on port 80.
  
- **ElegantOTA Integration:**  
  Provides a secure OTA update interface accessible at the `/update` route.
  
- **PlatformIO & Arduino Framework:**  
  Configured for rapid prototyping with automated build flag injection and dependency management.

---

## Requirements

- An ESP8266 board (e.g., ESP‑12F)
- [PlatformIO](https://platformio.org/) installed with the ESP8266 board package.
- A Wi‑Fi network (ensure your credentials in the `.env` file are correct).
- Python with the [`python-dotenv`](https://pypi.org/project/python-dotenv/) package installed in PlatformIO’s virtual environment.

> **Note:** The PlatformIO environment automatically injects Wi‑Fi credentials into your code via build flags. Ensure a `.env` file exists in the project root.

---

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/noiz-x/esp8266-ota-update
cd esp8266-ota-update
```

### 2. Configure Wi‑Fi Credentials

Create a `.env` file in the project root with your network credentials:

```ini
WIFI_SSID=YourSSID
WIFI_PASSWORD=YourPassword
```

The provided build script reads these values and passes them as build flags.

### 3. PlatformIO Configuration

Ensure your `platformio.ini` includes the necessary settings, build flags, and extra scripts. For example:

```ini
[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino
monitor_speed = 115200
lib_deps = ayushsharma82/ElegantOTA@^3.1.7
lib_compat_mode = strict
build_flags = -DELEGANTOTA_USE_ASYNC_WEBSERVER=1
extra_scripts = pre:get_details.py
```

> **Tip:** Make sure the `python-dotenv` module is installed in PlatformIO’s environment:
> 
> ```bash
> ~/.platformio/penv/bin/pip install python-dotenv
> ```

### 4. Project Structure Overview

- **OTA Module:**  
  The OTA update functionality is encapsulated in a separate module (`ota_module.h`) which contains the `OTAUpdater` class. This class exposes methods to initialize and process OTA updates independently of the web server code.

- **Main Application:**  
  The main application (`main.cpp`) sets up Wi‑Fi using credentials injected via build flags, initializes the asynchronous web server with a basic route, and integrates the OTA updater by calling its `begin()` method in `setup()` and its `loop()` method in `loop()`.

### 5. Build and Upload

Use PlatformIO to build and flash the firmware onto your ESP8266:

```bash
pio run --target upload
```

### 6. Monitor Serial Output

Open the serial monitor to view connection status and IP details:

```bash
pio device monitor --monitor_speed 115200
```

### 7. OTA Update Process

Once the device is connected, the ElegantOTA interface will be available via your web server at the ESP8266’s IP address:
- Open your browser and enter the printed IP address.
- Navigate to `/update` to access the OTA update interface.
- **Note:** Only upload the `firmware.bin` file generated in the build folder. Do not upload any other files.

---

## Troubleshooting

- **Wi‑Fi Connection:**  
  Verify that your `.env` file contains the correct `WIFI_SSID` and `WIFI_PASSWORD`.

- **Library Errors:**  
  Ensure the required libraries (`ESPAsyncWebServer` and `ESPAsyncTCP`/`AsyncTCP`) are installed as specified in your `platformio.ini`.

- **Serial Monitor:**  
  Confirm your board is connected and that the baud rate is set to 115200.

- **OTA Not Initiating:**  
  Check for the "HTTP server started" message in the serial output and verify that the `/update` route is accessible in your browser.

---

## License

This project is licensed under the [MIT License](LICENSE).
