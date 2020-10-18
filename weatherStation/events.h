#ifndef __EVENTS_H
#define __EVENTS_H

#include "utils.h"
#include "event.h"
#include "nixie.h"
#include "global.h"

#include <Arduino.h>
#include <asyncHTTPrequest.h>

struct IncrementTimeEvent : public Event {
  unsigned long triggerTime;
  unsigned long defineTime;
  ShiftRegister* reg;
  Clock* clk;

  void callback() {
    clk->increment();
    reg->writeTime(clk->getHours(), clk->getMinutes(), clk->getSeconds());
    defineTime = triggerTime;
    triggerTime = triggerTime+1000000;
  }
  bool condition() {
    return getCurrentTime()-defineTime >= triggerTime-defineTime;
  }

  IncrementTimeEvent(Clock* clk, ShiftRegister* reg) {
    this->clk = clk;
    this->reg = reg;
    defineTime = getCurrentTime();
    triggerTime = (defineTime/1000000)*1000000+1000000;
  }
};

struct WriteToBargraphsEvent : public Event {
  unsigned long triggerTime;
  unsigned long defineTime;
  Bargraph *tempBar;
  Bargraph *presBar;
  Bargraph *humBar;
  WeatherData* wd;

  void callback() {
    tempBar->write((int)((wd->temperature-273.15+20.0)/60.0*1000.0));
    humBar->write(wd->humidity*10);
    presBar->write((wd->pressure-900)*5);
    defineTime = getCurrentTime();
    triggerTime = defineTime+500000;
  }
  bool condition() {
    return getCurrentTime()-defineTime >= triggerTime-defineTime;
  }

  WriteToBargraphsEvent(WeatherData* wd, Bargraph *t, Bargraph *p, Bargraph *h) {
    this->wd = wd;
    tempBar = t;
    presBar = p;
    humBar = h;
    defineTime = getCurrentTime();
    triggerTime = defineTime+500000;
  }
};

struct WriteDataToSerialEvent : public Event {
  unsigned long triggerTime;
  unsigned long defineTime;
  Clock* clk;
  WeatherData* wd;

  void callback() {
    char str[255];
    sprintf(str, "time: %02d:%02d:%02d, temp: %.2lf C, pres: %d hPa, hum: %d%%\n", clk->getHours(), clk->getMinutes(), clk->getSeconds(), wd->temperature-273.15, wd->pressure, wd->humidity);
    Serial.print(str);
    defineTime = getCurrentTime();
    triggerTime = defineTime+5000000;
  }
  bool condition() {
    return getCurrentTime()-defineTime >= triggerTime-defineTime;
  }

  WriteDataToSerialEvent(Clock* clk, WeatherData* wd) {
    this->clk = clk;
    this->wd = wd;
    defineTime = getCurrentTime();
    triggerTime = defineTime+5000000;
  }
};

void requestWeatherDataEventReceiveCallback(void* optParm, asyncHTTPrequest* request, int readyState) {
  if(readyState == 4){
      WeatherData* wd = (WeatherData*)optParm;
      *wd = parseWeatherJson(request->responseText());
  }
}

struct RequestWeatherDataEvent : public Event {
  unsigned long triggerTime;
  unsigned long defineTime;
  WeatherData *weatherData;
  asyncHTTPrequest request;

  void callback() {
    request.onReadyStateChange(requestWeatherDataEventReceiveCallback, weatherData);
    if(request.readyState() == 0 || request.readyState() == 4){
        if(request.open("GET", constants::WEATHER_URL)) request.send();
    }
    defineTime = getCurrentTime();
    triggerTime = defineTime+1000*1000*10;
  }
  bool condition() {
    return (getCurrentTime()-defineTime >= triggerTime-defineTime) && global::config.internetWeather;
  }

  RequestWeatherDataEvent(WeatherData* wd) {
    weatherData = wd;
    defineTime = getCurrentTime();
    triggerTime = defineTime+1000;
  }
};

void requestCurrentTimeEventReceiveCallback(void* optParm, asyncHTTPrequest* request, int readyState) {
  if(readyState == 4){
      Clock* clk = (Clock*)optParm;
      *clk = parseTimeJson(request->responseText());
  }
}

struct RequestCurrentTimeEvent : public Event {
  unsigned long triggerTime;
  unsigned long defineTime;
  Clock* clk;
  asyncHTTPrequest request;

  void callback() {
    request.onReadyStateChange(requestCurrentTimeEventReceiveCallback, clk);
    if(request.readyState() == 0 || request.readyState() == 4){
        if(request.open("GET", constants::TIME_URL)) request.send();
    }
    defineTime = getCurrentTime();
    triggerTime = defineTime+1000*1000*3600;
  }
  
  bool condition() {
    return getCurrentTime()-defineTime >= triggerTime-defineTime;
  }

  RequestCurrentTimeEvent(Clock* c) {
    clk = c;
    defineTime = getCurrentTime();
    triggerTime = defineTime+1000;
  }
};

#endif
