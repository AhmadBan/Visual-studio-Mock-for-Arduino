#include "Arduino.h"
#include "../FS/FS.h"
#include "../FS/FakeFs.h"
#include <memory>



static uint8_t pinstate = 0;
static uint8_t modeinput = 0;
static uint8_t modepullup = 0;

void digitalWrite(uint8_t pin, uint8_t val) {
	if (val == LOW)
		pinstate &= ~(1 << pin);
	else
		pinstate |= (1 << pin);
}
int digitalRead(uint8_t pin) {

	if (pinstate & (1 << pin))
		return HIGH;
	else
		return LOW;

}
void pinMode(uint8_t pin, uint8_t mode) {
	switch (mode) {
	case INPUT:
		modeinput |= 1 << pin;
		modepullup &= ~(1 << pin);
		break;
	case INPUT_PULLUP:
		modeinput |= 1 << pin;
		modepullup |= 1 << pin;

		break;
	case OUTPUT:
		modeinput &= ~(1 << pin);
		modepullup &= ~(1 << pin);
		break;
	}

}
uint8_t get_modeinput() {
	return modeinput;
}
uint8_t get_modepullup() {
	return modepullup;
}


static uint32_t counter = 0;
uint32_t millis() {
	counter++;
	return counter;
}

void setMillis(uint32_t time) {
	counter = time;
}

void delayMicroseconds(uint32_t delay) {

}