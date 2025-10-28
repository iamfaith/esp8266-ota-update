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

#define LED_PIN 2  // ESP32 DevKit v1 板载 LED 通常连接在 GPIO2

void setup_update() {

  pinMode(LED_PIN, OUTPUT);
}

void loop_update() {
  digitalWrite(LED_PIN, HIGH);  // 点亮 LED
  delay(500);                   // 延时 500 毫秒
  digitalWrite(LED_PIN, LOW);   // 熄灭 LED
  delay(500);                   // 延时 500 毫秒
}

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
  setup_update();
}

void loop()
{
  // Process OTA update tasks (non-blocking).
  otaUpdater.loop();

  loop_update();
  // ? Other tasks to be run
}
