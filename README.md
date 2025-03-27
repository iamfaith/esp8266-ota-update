# ESP8266 ElegantOTA Updater

This project demonstrates an over-the-air (OTA) firmware updater for the ESP8266 using the [ElegantOTA](https://github.com/ayushsharma82/ElegantOTA) library. The firmware connects to a Wi‑Fi network, sets up an HTTP web server, and enables firmware updates via OTA—without needing a physical USB connection.

## Features

- **Wi‑Fi Connectivity:** Connects to a specified SSID and obtains an IP address.
- **Web Server:** Runs an HTTP server on port 80 with a basic endpoint (`/`) for testing.
- **ElegantOTA Integration:** Leverages ElegantOTA for secure and easy OTA updates.
- **Serial Debugging:** Prints connection status and IP address details to the serial monitor.
- **PlatformIO & Arduino Framework:** Configured for rapid prototyping.
- **Environment Variable Support:** Wi‑Fi credentials are read from a `.env` file (handled in the build process).

## Requirements

- An ESP8266 board (e.g., ESP-12F)
- [PlatformIO](https://platformio.org/) installed on your development machine **with the ESP8266 board package**.
- A Wi‑Fi network (ensure the credentials in the code match your network).
- Python with the [`python-dotenv`](https://pypi.org/project/python-dotenv/) package installed in PlatformIO’s virtual environment.

> **Note:** The ESP8266 board package is provided via PlatformIO—it includes all necessary libraries, headers, and toolchain support to compile and flash firmware for the ESP8266.

## Getting Started

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/noiz-x/esp8266-ota-update
   cd esp8266-ota-update
   ```

2. **Configure Wi‑Fi Credentials:**

   Create a `.env` file in the project root with your network credentials:

   ```ini
   WIFI_SSID=YourSSID
   WIFI_PASSWORD=YourPassword
   ```

   The build process uses an extra script to read these values and pass them as build flags to your source code.

3. **PlatformIO Configuration:**

   Ensure your `platformio.ini` includes the necessary build flags and extra script:

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

   > **Tip:** Make sure the `python-dotenv` module is installed in PlatformIO’s environment by running:  
   > `~/.platformio/penv/bin/pip install python-dotenv`

4. **Build and Upload:**

   Use PlatformIO to build and flash the firmware onto your ESP8266:

   ```bash
   pio run --target upload
   ```

5. **Monitor Serial Output:**

   Open the serial monitor to view connection status and IP address details:

   ```bash
   pio device monitor --monitor_speed 115200
   ```

6. **OTA Update:**

   Once connected, the ElegantOTA interface will be available via the web server running on the ESP8266’s IP address. Open a browser, enter the printed IP address, and follow the prompts to perform OTA updates.

## Troubleshooting

- **Wi‑Fi Connection Issues:** Verify that the SSID and password in your `.env` file are correct. For an open network, consider using `WiFi.begin(ssid);` without a password.
- **Serial Monitor Issues:** Ensure your board is connected and that the baud rate is set to 115200. If no output appears, try pressing the reset button on your ESP8266.
- **ModuleNotFoundError:** If you see an error regarding `dotenv`, ensure you have installed `python-dotenv` in PlatformIO’s environment using:  
  `~/.platformio/penv/bin/pip install python-dotenv`
- **OTA Not Initiating:** Confirm that the web server is running (check for the "HTTP server started" message in the serial output) and then access the ElegantOTA interface via the ESP8266’s IP address in your browser.

## License

This project is licensed under the [MIT License](LICENSE).