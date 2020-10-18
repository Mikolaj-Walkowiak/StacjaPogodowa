#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include <ESP8266WiFi.h>

namespace constants {
	extern const char ssid[];
	extern const char password[];
	
  extern const char WEATHER_URL[];
  extern const char TIME_URL[];

  extern IPAddress localIP;
  extern IPAddress gateway;
  extern IPAddress subnet;
  extern IPAddress dns1;
  extern IPAddress dns2;
}

#endif
