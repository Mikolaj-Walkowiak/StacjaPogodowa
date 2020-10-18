#include "utils.h"

#include <ArduinoJson.h>

Clock parseTimeJson(String jsonData) {
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, jsonData);
  String timeString = doc["datetime"];
  char year = timeString.substring(2,4).toInt();
  char month = timeString.substring(5,7).toInt();
  char day = timeString.substring(8,10).toInt();
  char hour = timeString.substring(11,13).toInt();
  char minute = timeString.substring(14,16).toInt();
  char second = timeString.substring(17,19).toInt();
  return Clock(hour, minute, second);
}

WeatherData parseWeatherJson(String jsonData) {
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, jsonData);
  return WeatherData(doc["main"]["temp"], doc["main"]["pressure"], doc["main"]["humidity"]);
}

void Clock::increment() {
	++seconds;
	if(seconds >= 60) {
		seconds = 0;
		minutes++;
		if(minutes >= 60) {
			minutes = 0;
			++hours;
			if(hours >= 24) {
				hours = 0;
			}
		}
	}
}

void Clock::set(char hours, char minutes, char seconds) {
	this->seconds = seconds;
	this->minutes = minutes;
	this->hours = hours;
}

char Clock::getSeconds() {
	return seconds;
}

char Clock::getMinutes() {
	return minutes;
}

char Clock::getHours() {
	return hours;
}
