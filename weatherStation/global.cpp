#include "global.h"

namespace global {
  extern Bargraph tempBar = Bargraph(5);
  extern Bargraph humBar = Bargraph(4);
  extern Bargraph presBar = Bargraph(0);
	extern ShiftRegister shiftRegister = ShiftRegister();

	extern Clock nixieClock = Clock();
	extern WeatherData weatherData = WeatherData();

	extern AsyncWebServer server(80);
  extern Config config = Config();
}
