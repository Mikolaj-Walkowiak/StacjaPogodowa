#include "Arduino.h"
#include "event.h"

EventList eventList;

unsigned long getCurrentTime() {
  return micros() - 10000000;
}

void registerEvent(Event* newEvent) {
  eventList.addEvent(newEvent);
}

void triggerEvents() {
  eventList.triggerEvents();
}

void EventList::addEvent(Event* newEvent) {
  newEvent->nextEvent = head;
  if(head) head->prevEvent = newEvent;
  head = newEvent;
}
	
void EventList::triggerEvents() {
  Event* cur = head;
	while(cur) {
    if(cur->condition()) {
      cur->callback();
      if(cur->del) {
        Event* tmp = cur;
        cur = cur->nextEvent;
        if(tmp->prevEvent) tmp->prevEvent->nextEvent = tmp->nextEvent;
        else head = tmp->nextEvent;
        if(tmp->nextEvent) tmp->nextEvent->prevEvent = tmp->prevEvent;
        delete tmp;
      }
      else cur = cur->nextEvent;
    }
    else cur = cur->nextEvent;
	}
}
