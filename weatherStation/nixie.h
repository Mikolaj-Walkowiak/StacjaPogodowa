#ifndef __NIXIE_H
#define __NIXIE_H

const int cathodeMap[10]  = {1,12,14,6,2,10,8,0,4,9};

struct ShiftRegister {
	//Pin connected to DS of 74HC595 -> 14
	int dataPin;
	//Pin connected to MR of 74HC595 ->10
	int resetPin;
	//Pin connected to SH_CP of 74HC595 ->11
	int clockPin;
	//Pin connected to ST_CP of 74HC595 ->12
	int latchPin;
	
	ShiftRegister() : dataPin(14), resetPin(12), clockPin(13), latchPin(15) { init(); }
	ShiftRegister(int dataPin, int resetPin, int clockPin, int latchPin) : dataPin(dataPin), resetPin(resetPin), clockPin(clockPin), latchPin(latchPin) { init(); }
	
	void init();
	void writeTime(char hours, char minutes, char seconds);
};

struct Bargraph {
	
	int pin;
	
	Bargraph(int pin) : pin(pin) { init(); }
	
	void init();
	void write(int value);
};

#endif
