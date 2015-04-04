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
unsigned int intervalMillis = 250;

unsigned long previousMillis = 0;
int ledState = LOW;
int startBlink = 1;


void onButtonStartStateChanged(uint8_t btn_event, Button * btn)
{
    if (btn_event == BUTTON_NORMAL_TO_HOLD)
    {
        startMillis = millis();
        digitalWrite(MOTOR_PIN, HIGH);
        startBlink = 0;
    }

    if (btn_event == BUTTON_HOLD_TO_RELEASE)
    {
        ledState = LOW;
        digitalWrite(MOTOR_PIN, LOW);
        startBlink = 1;
        intervalMillis = millis() - startMillis;
    }
}

void loop()
{
    btnChanged(&btStart, onButtonStartStateChanged);


    if (startBlink == 1)
    {
        unsigned long currentMillis = millis();
        if(currentMillis - previousMillis > intervalMillis) {
          // save the last time you blinked the LED
          previousMillis = currentMillis;

          // if the LED is off turn it on and vice-versa:
          if (ledState == LOW)
            ledState = HIGH;
          else
            ledState = LOW;

          // set the LED with the ledState of the variable:
          digitalWrite(MOTOR_PIN, ledState);
        }
    }



}

