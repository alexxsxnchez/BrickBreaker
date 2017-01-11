#ifndef HARDWARE_H
#define HARDWARE_H

    #define OLED_WIDTH 128
    #define OLED_HEIGHT 32
    #define LED_TOGGLE_RATE 40 // in milliseconds
    #define BTN1 PD_2
    #define BTN2 PE_0
    #define LIVES_LOST_ADDRESS 0
    #define BRICKS_BROKEN_ADDRESS 0x100
    #define GAMES_WON_ADDRESS 0x200
    #define MAX_DIGITS 3
    
//=====================
// Orbit Booster Pack
    void deviceInit();
//=====================
// Wire for connection to accelerometer
    void wireInit();
    void wireWriteByte(int, uint8_t);
    void wireWriteRegister(int, uint8_t, uint8_t);
    void wireRequestArray(uint8_t, uint32_t, uint8_t);
//=====================
// Accelerometer
    void acceleroInit();
    void checkForMotion();
    int getMotionDir();
//=====================
// LED
    void flashLED(int, int);
//=====================
// EEPROM storage device
    void storageInit();
    void updateValue(uint32_t, uint32_t);
    uint32_t getValue(uint32_t);
#endif
