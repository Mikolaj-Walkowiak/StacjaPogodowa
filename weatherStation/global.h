#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "utils.h"
#include "nixie.h"

#include <ESPAsyncWebServer.h>

struct Config {
  bool internetWeather = false;
};

namespace global {
	extern Bargraph tempBar;
  extern Bargraph humBar;
  extern Bargraph presBar;
	extern ShiftRegister shiftRegister;

	extern Clock nixieClock;
	extern WeatherData weatherData;

	extern AsyncWebServer server;

  extern Config config;
}

#endif
