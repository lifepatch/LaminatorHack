#ifndef ARDUINO_LIB
#define ARDUINO_LIB
#include <Arduino.h>
#endif

#ifndef BUTTON
#define BUTTON

#define BUTTON_NORMAL 0
#define BUTTON_PRESS 1
#define BUTTON_RELEASE 2
#define BUTTON_HOLD 3
#define BUTTON_HOLD_TO_RELEASE 4
#define BUTTON_NORMAL_TO_PRESS 5
#define BUTTON_NORMAL_TO_HOLD 6

struct Button{
    uint8_t state;
    uint8_t prevstate;
    uint8_t toggle;
    uint8_t pin;
    uint8_t event;

    //debouncing stuff
    // the following variables are long's because the time, measured in miliseconds,
    // will quickly become a bigger number than can be stored in an int.
    unsigned long lastDebounceTime;  // the last time the output pin was toggled
    unsigned int debounceDelay;    // the debounce time; increase if the output flickers
};

void btnInit(Button * btn, uint8_t pin, unsigned int debounce_delay = 50)
{

    btn->pin = pin;
    btn->prevstate = 1;
    btn->state = 1;
    btn->toggle = 0;
    btn->event = BUTTON_NORMAL;
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

void btnChanged(Button * btn, void func_state_changed(uint8_t, Button*) = NULL)
{
    uint8_t currentstate = digitalRead(btn->pin);
    uint8_t prevstate = btn->prevstate;
    uint8_t btn_event = BUTTON_NORMAL;

    if(currentstate != prevstate)
    {
        btn->lastDebounceTime = millis();
    }

    if ((millis() - btn->lastDebounceTime) > btn->debounceDelay) {


         //using internal pull up resistor btn state is reversed

        if ( btn->state != currentstate && currentstate == HIGH ) //from LOW to HIGH = RELEASE
        {
            btn_event   = BUTTON_RELEASE;
        }else if( btn->state != currentstate && currentstate == LOW  ) //from HIGH to LOW = PRESS
        {
            btn_event   = BUTTON_PRESS;
            btnToggle(btn);
        }else if (btn->state == currentstate && currentstate == LOW)
        {
            btn_event   = BUTTON_HOLD;
        }else{
            btn_event   = BUTTON_NORMAL;
        }

        if (btn->state != currentstate) {
            btn->state = currentstate;
        }

        if (btn_event != btn->event)
        {

            if(btn->event == BUTTON_HOLD && btn_event == BUTTON_RELEASE)
            {
                btn_event = BUTTON_HOLD_TO_RELEASE;
            }else if(btn->event == BUTTON_NORMAL && btn_event == BUTTON_PRESS)
            {
                btn_event = BUTTON_NORMAL_TO_PRESS;
            }else if (btn->event == BUTTON_NORMAL_TO_PRESS && btn_event == BUTTON_HOLD)
            {
                btn_event = BUTTON_NORMAL_TO_HOLD;
            }

            btn->event = btn_event;
            func_state_changed(btn_event, btn);
        }

    }

    btn->prevstate = currentstate;

}

#endif // BUTTON

