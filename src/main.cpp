#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Create an Async web server instance for ESP8266 on port 80
AsyncWebServer server(80);

#include "ota_module.h"

// The following macros are defined via your PlatformIO build_flags using your .env file:
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

// Instantiate the OTA updater
OTAUpdater otaUpdater;

// ? Variables to be defined

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // Set up a simple route to serve a welcome page.
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hello! OTA updates are enabled."); });

  // Initialize the OTA updater and inject its routes into the server.
  otaUpdater.begin(&server);

  // Start the web server.
  server.begin();
  Serial.println("HTTP server started");

  // ? Initialization of tasks
}

void loop()
{
  // Process OTA update tasks (non-blocking).
  otaUpdater.loop();

  // ? Other tasks to be run
}
