#include "Arduino.h"
#include "nixie.h"

void ShiftRegister::init() {
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	digitalWrite(latchPin, LOW);
	digitalWrite(clockPin, LOW);
}

void ShiftRegister::writeTime(char hours, char minutes, char seconds) {
	shiftOut(dataPin, clockPin, MSBFIRST, (cathodeMap[(seconds/10)%10] << 4) + cathodeMap[seconds%10]);
	shiftOut(dataPin, clockPin, MSBFIRST, (cathodeMap[(minutes/10)%10] << 4) + cathodeMap[minutes%10]);
	shiftOut(dataPin, clockPin, MSBFIRST, (cathodeMap[(hours/10)%10] << 4) + cathodeMap[hours%10]);
	digitalWrite(latchPin, LOW);
	digitalWrite(latchPin, HIGH);
}

void Bargraph::init() {
  pinMode(pin, OUTPUT);
	analogWrite(pin, 128);
}

void Bargraph::write(int value) {
	analogWrite(pin, value);
}
