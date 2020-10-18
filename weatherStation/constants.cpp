#include "constants.h"

namespace constants {
	extern const char ssid[] = "SKOSZTUJ";
	extern const char password[] = "ZamknijDrzwiOdZewnatrz2137";
	
  extern const char WEATHER_URL[] = "http://api.openweathermap.org/data/2.5/weather?appid=6cff5df79ef73a316cfc5e65b1bd3992&id=7530858";
  extern const char TIME_URL[] = "http://worldtimeapi.org/api/ip";

  extern IPAddress localIP(192,168,1,222);
  extern IPAddress gateway(192,168,1,1);
  extern IPAddress subnet(255,255,255,0);
  extern IPAddress dns1(8,8,8,8);
  extern IPAddress dns2(192,168,1,1);
}
