// Access to the Arduino Libraries
#ifndef ARDUINO_LIB
#define ARDUINO_LIB
#include <Arduino.h>
#endif

#define BTN_START_PIN 3
#define MOTOR_PIN 1

//User Library
#include "button.h"
#include "setup.h"

unsigned long startMillis = 0;
unsigned long stopMillis = 0;

void btStartCallback(uint8_t state, Button * btn)
{
     digitalWrite(MOTOR_PIN, btn->state);
}

void loop()
{
    btnChanged(&btStart, btStartCallback);
}

