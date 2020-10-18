#include "server.h"

#include <FS.h>
#include <ArduinoJson.h>

#include "global.h"

void initializeServer(AsyncWebServer &server) {
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  server.on("/data", HTTP_GET, dataGET);
  server.on("/data", HTTP_POST, 
                [](AsyncWebServerRequest *request){},
                [](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {},
                dataPOSTbody);
  server.on("/config", HTTP_GET, configGET);
  server.on("/config", HTTP_POST, 
                [](AsyncWebServerRequest *request){},
                [](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {},
                configPOSTbody);
	server.onNotFound(notFound);
	server.begin();
}

void dataGET(AsyncWebServerRequest *request) {
  StaticJsonDocument<200> doc;

  doc["weather"]["temp"] = global::weatherData.temperature;
  doc["weather"]["humidity"] = global::weatherData.humidity;
  doc["weather"]["pressure"] = global::weatherData.pressure;
  doc["time"]["hours"] = global::nixieClock.hours;
  doc["time"]["minutes"] = global::nixieClock.minutes;
  doc["time"]["seconds"] = global::nixieClock.seconds;
  
  char *output = new char[200];
  serializeJson(doc, output, 200);
  request->send(200, "application/json", output);
  delete[] output;
}

void dataPOSTbody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  if(!global::config.internetWeather) {
    char* message = new char[len+1];
    strncpy(message, (char*)data, len);
    message[len] = 0;
    StaticJsonDocument<200> doc;
    deserializeJson(doc, message);
    if(doc["weather"]["temp"]) global::weatherData.temperature = doc["weather"]["temp"];
    if(doc["weather"]["humidity"]) global::weatherData.humidity = doc["weather"]["humidity"];
    if(doc["weather"]["pressure"]) global::weatherData.pressure = doc["weather"]["pressure"];
    delete[] message;
  }
  request->send(200, "text/plain", "");
}

void configGET(AsyncWebServerRequest *request) {
  StaticJsonDocument<200> doc;

  doc["weather"]["internet"] = global::config.internetWeather;
  
  char *output = new char[200];
  serializeJson(doc, output, 200);
  request->send(200, "application/json", output);
  delete[] output;
}

void configPOSTbody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  char* message = new char[len+1];
  strncpy(message, (char*)data, len);
  message[len] = 0;
  StaticJsonDocument<200> doc;
  deserializeJson(doc, message);
  if(doc["weather"]["internet"]) {
    global::config.internetWeather = doc["weather"]["internet"];
  }
  request->send(200, "text/plain", "");
  delete[] message;
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
