#ifndef OTA_MODULE_H
#define OTA_MODULE_H

#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

// This class encapsulates OTA update functionality.
class OTAUpdater
{
public:
  OTAUpdater() {}

  // Initialize OTA by injecting its routes into the provided server.
  void begin(AsyncWebServer *server)
  {
    ElegantOTA.begin(server);
  }

  // Call this in loop() to handle OTA update processing.
  void loop()
  {
    ElegantOTA.loop();
  }
};

#endif // OTA_MODULE_H
