#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

const char *ssid = "Retr0";
const char *password = "d4a2992f58bb";

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hi! I am ESP8266."); });

  // Initialize ElegantOTA in async mode (now enabled via build_flags)
  ElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  ElegantOTA.loop();
}
