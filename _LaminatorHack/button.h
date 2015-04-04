#ifndef ARDUINO_LIB
#define ARDUINO_LIB
#include <Arduino.h>
#endif

#ifndef BUTTON
#define BUTTON

struct Button{
    uint8_t state;
    uint8_t prevstate;
    uint8_t toggle;
    uint8_t pin;
    //debouncing stuff
    // the following variables are long's because the time, measured in miliseconds,
    // will quickly become a bigger number than can be stored in an int.
    long lastDebounceTime;  // the last time the output pin was toggled
    long debounceDelay;    // the debounce time; increase if the output flickers
};

void btnInit(Button * btn, uint8_t pin, long debounce_delay = 50)
{

    btn->pin = pin;
    btn->prevstate = 0;
    btn->state = 0;
    btn->toggle = 0;

    //debouncing
    btn->debounceDelay = debounce_delay;
    btn->lastDebounceTime = 0;

    //Activate input and pull up resistor
    pinMode(btn->pin, INPUT);
    digitalWrite(btn->pin, HIGH);

}

void btnToggle(Button * btn)
{
    btn->toggle = !btn->toggle;
}

void btnChanged(Button * btn, void callback(uint8_t, Button*))
{
    uint8_t reading   = digitalRead(btn->pin);
    uint8_t prevstate = btn->prevstate;

    if(reading != prevstate)
    {
        btn->lastDebounceTime = millis();
    }

    if ((millis() - btn->lastDebounceTime) > btn->debounceDelay) {
        if (reading != btn->state) {
          btn->state = reading;
          //if using internal pull up resistor
          if (btn->state == LOW){
              btnToggle(btn);
          }

          callback(btn->state, btn);

        }
    }
    btn->prevstate = reading;

}

#endif // BUTTON

