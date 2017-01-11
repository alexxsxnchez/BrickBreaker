#ifndef PROGRAM_H
#define PROGRAM_H

    #define LED_FLASH_AMOUNT 40
    #define STATE_DELAY 1000 // the delay before switching between some game states
    #define DEBOUNCE_DELAY 200
   
    static enum state{
        MENU = 0,
        GAME = 1,
        GAME_OVER = 2,
        GAME_WIN = 3,
        STATS = 4,
    } gameMode = MENU;

    void programInit();
    void newMode(state);
    void menuInit();
    void gameOverInit();
    void gameWinInit();
    void statsInit();
    void resetStats();
    void drawInt(uint32_t, int y);
    int getDigits(int);
#endif
