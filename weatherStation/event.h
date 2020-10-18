#ifndef __EVENT_H
#define __EVENT_H

struct Event {
  virtual void callback() = 0;
  virtual bool condition() = 0;

  bool del = false;
	Event* nextEvent = NULL;
  Event* prevEvent = NULL;
};

struct EventList {
	Event* head = NULL;
	
	void addEvent(Event* newEvent);
	void triggerEvents();
};

unsigned long getCurrentTime();
void registerEvent(Event* newEvent);
void triggerEvents();

#endif
