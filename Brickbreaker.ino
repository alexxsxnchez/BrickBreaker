#include "headers.h"

unsigned long timeSinceRefresh; // measured in milliseconds

void setupPins() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BTN1, INPUT);
    pinMode(BTN2, INPUT);
}

// init functions found in the hardware file
void init() {
    wireInit();
    deviceInit();
    delay(100);
    acceleroInit();
    storageInit();
    programInit();
}
void setup() {
    setupPins();
    init();
    timeSinceRefresh = millis();
}

void loop() {
    switch(gameMode) {
        case MENU:
            if(digitalRead(BTN1) == HIGH) {
                newMode(STATS);
            }
            else if(digitalRead(BTN2) == HIGH) {
                newMode(GAME);
            }
            break;
        case GAME:
            // check for motion changes in y axis
            checkForMotion();
            // draws on screen IF time passed has surpassed threshold (allows animation to be done without delay() function)
            timeSinceRefresh = refreshScreen(timeSinceRefresh);
            break;
        case STATS:
            if(digitalRead(BTN1) == HIGH) {
                newMode(MENU);
            }
            else if(digitalRead(BTN2) == HIGH) {
                resetStats();
            }
            break;
    }
}
