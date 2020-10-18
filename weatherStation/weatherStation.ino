#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <FS.h>

#include "constants.h"
#include "events.h"
#include "nixie.h"
#include "utils.h"
#include "server.h"
#include "global.h"

void setup() {
  analogWriteFreq(100000);
  
  Serial.begin(115200);
  Serial.print("\n");

  SPIFFS.begin();

  WiFi.disconnect();
  WiFi.config(constants::localIP, constants::gateway, constants::subnet, constants::dns1, constants::dns2);
  WiFi.begin(constants::ssid, constants::password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }

  registerEvent(new IncrementTimeEvent(&global::nixieClock, &global::shiftRegister));
  registerEvent(new WriteToBargraphsEvent(&global::weatherData, &global::tempBar, &global::presBar, &global::humBar));
  registerEvent(new RequestWeatherDataEvent(&global::weatherData));
  registerEvent(new RequestCurrentTimeEvent(&global::nixieClock));

  initializeServer(global::server);
}

void loop() {
  triggerEvents();
}
