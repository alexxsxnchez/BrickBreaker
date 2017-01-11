void programInit() {
    newMode(MENU);
}

void newMode(state newMode){
    OrbitOledClear();
    gameMode = newMode;
    switch(gameMode) {
        case MENU:
            menuInit();
            break;
        case GAME:
            gameInit();
            break;
        case GAME_OVER:
            gameOverInit();
            break;
        case GAME_WIN:
            gameWinInit();
            break;
        case STATS:
            statsInit();
            break;
    }
}

void menuInit() {
    OrbitOledMoveTo(50, 10);
    OrbitOledDrawString("PLAY");
    OrbitOledMoveTo(46, 21);
    OrbitOledDrawString("STATS");
    OrbitOledUpdate();
    delay(DEBOUNCE_DELAY);
}

void gameOverInit() {
    OrbitOledMoveTo(50, 10);
    OrbitOledDrawString("GAME");
    OrbitOledMoveTo(50, 20);
    OrbitOledDrawString("OVER");
    OrbitOledUpdate();
    flashLED(RED_LED, LED_FLASH_AMOUNT);
    delay(STATE_DELAY);
    newMode(MENU);
}

void gameWinInit() {
    OrbitOledMoveTo(40, 10);
    OrbitOledDrawString("YOU WIN!");
    OrbitOledUpdate();
    flashLED(GREEN_LED, LED_FLASH_AMOUNT);
    delay(STATE_DELAY);
    uint32_t currentGamesWon = getValue(GAMES_WON_ADDRESS);
    currentGamesWon++;
    updateValue(currentGamesWon, GAMES_WON_ADDRESS); // update the stats stored in the EEPROM
    newMode(MENU);
}

// helper function for drawInt
int getDigits(int n) {
    if(n == 0) {
        return 1;
    }
    int digits = 0;
    while(n > 0) {
        n /= 10;
        digits++;
    }
    return digits;
}

void drawInt(uint32_t num, int y) {
        if(num > 999) {
            num = 999;  // cap the stat at three digits
        }
        char str[MAX_DIGITS];
        char *string = itoa(num, str, 10);
        if(num == 0) {
            OrbitOledMoveTo(OLED_WIDTH - 7, y);
            OrbitOledDrawChar(string[0]);
            return;
        }
        //bool havePrintedNonZero = false;
        int digits = getDigits(num);
        for(int i = 1; i <= digits; i++) {
            OrbitOledMoveTo(OLED_WIDTH - 7 * i, y); // right Justified Print
            char digit = string[digits - i];
            OrbitOledDrawChar(digit);
        }
}

void statsInit() {
    uint32_t livesLost = getValue(LIVES_LOST_ADDRESS);
    uint32_t gamesWon = getValue(GAMES_WON_ADDRESS);
    uint32_t bricksBroken = getValue(BRICKS_BROKEN_ADDRESS);
    
    OrbitOledMoveTo(0, 3);
    OrbitOledDrawString("Lives Lost:");
    drawInt(livesLost, 3);
    
    OrbitOledMoveTo(0, 13);
    OrbitOledDrawString("Games Won:");
    drawInt(gamesWon, 13);
    
    OrbitOledMoveTo(0, 23);
    OrbitOledDrawString("Bricks Broke:");
    drawInt(bricksBroken, 23);
    
    OrbitOledUpdate();
    delay(DEBOUNCE_DELAY);
}

void resetStats() {
    updateValue(0, LIVES_LOST_ADDRESS);
    updateValue(0, BRICKS_BROKEN_ADDRESS);
    updateValue(0, GAMES_WON_ADDRESS);
    OrbitOledClear();
    statsInit();
}
