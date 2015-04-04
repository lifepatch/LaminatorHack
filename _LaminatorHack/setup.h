#ifndef SETUP
#define SETUP

// constants won't change. Used here to set a pin number :


Button btStart; //start recording pcb height

void setupPin()
{
    //pinMode(BTN_START_PIN, INPUT);
    pinMode(MOTOR_PIN, OUTPUT);
}

void setupButton()
{
    btnInit(&btStart, BTN_START_PIN, 50);
}

void setup() {
    setupPin();
    setupButton();
}


#endif // SETUP

