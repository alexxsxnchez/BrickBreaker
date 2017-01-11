#ifndef GAME_H
#define GAME_H

    #define INIT_LIVES 3
    #define MAX_LIVES 6
    #define REFRESH_RATE 50 //50 in milliseconds; used as a minimum value (rate may be slightly longer)
    #define GAME_START_DELAY 500
    
    void gameInit();
    void loseLife();
    void extraLife();
    void drawLifeCounter();
    void respawn();
    void draw();
    unsigned long refreshScreen(unsigned long);
#endif
