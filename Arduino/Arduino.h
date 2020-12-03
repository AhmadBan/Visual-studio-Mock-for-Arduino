#pragma once
#include <cstdint>
#include<iostream>
#include<stdio.h>

#define DEBUGV printf

#define boolean bool
#define String std::string

#include "stdint.h"
#define HIGH 0x1
#define LOW  0x0


#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2 

void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
void pinMode(uint8_t pin, uint8_t mode);

uint32_t millis();
void setMillis(uint32_t time);
void delayMicroseconds(uint32_t delay);