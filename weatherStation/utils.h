#ifndef __UTILS_H
#define __UTILS_H

#include <Arduino.h>

struct WeatherData {
	double temperature;
	int pressure;
	int humidity;
	
	WeatherData(double temp, int pres, int hum) : temperature(temp), pressure(pres), humidity(hum) {}
	WeatherData() {}
};

struct Clock {
	char seconds, minutes, hours;
	
	void increment();
	void set(char seconds, char minutes, char hours);
	char getSeconds();
	char getMinutes();
	char getHours();
	
	Clock(char hours, char minutes, char seconds) { set(hours, minutes, seconds); }
	Clock() {}
};

Clock parseTimeJson(String jsonData);
WeatherData parseWeatherJson(String jsonData);

#endif
