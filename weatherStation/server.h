#ifndef __SERVER_H
#define __SERVER_H

#include <ESPAsyncWebServer.h>

void initializeServer(AsyncWebServer &server);
void dataGET(AsyncWebServerRequest *request);
void dataPOSTbody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void configGET(AsyncWebServerRequest *request);
void configPOSTbody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void notFound(AsyncWebServerRequest *request);

#endif
