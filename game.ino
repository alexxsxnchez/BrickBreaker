static int lives;

void gameInit() {
    lives = INIT_LIVES;
    initBricks();
    initPaddle();
    initBall();
    draw();
    delay(GAME_START_DELAY);
}

void loseLife() {
    uint32_t totalLivesLost = getValue(LIVES_LOST_ADDRESS);
    totalLivesLost++;
    updateValue(totalLivesLost, LIVES_LOST_ADDRESS); // update the stats stored in the EEPROM
    lives--;
}

void extraLife() {
    if(lives >= MAX_LIVES) {
        return; 
    }
    lives++;
    flashLED(GREEN_LED, 1);
}

void drawLifeCounter() {
    OrbitOledMoveTo(1, 0);
    OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnBlank));
    OrbitOledFillRect(1, OLED_HEIGHT - 1);
    OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
    for(int i = 0; i < lives; i++) {
        OrbitOledMoveTo(1, i * 3 + 2);
        OrbitOledFillRect(1, i * 3 + 2);
    }
}

void respawn() {
    showBall(false);
    showPaddle(false);
    if(lifeAvailable()) {
        showLife(false);
        setLifeAvailable(false);
    }    
    initPaddle();
    initBall();
    flashLED(RED_LED, 5);
    OrbitOledUpdate();
}
void draw() {
    drawBricks();
    drawPaddle();
    drawLifeCounter();
    drawBall();
    if(lifeAvailable()) {
        drawLife();
    }
    OrbitOledUpdate();
    if(lives <= 0) {
        newMode(GAME_OVER);
    }
    else if(getBrickCount() <= 0) {
        newMode(GAME_WIN);
    }
}

unsigned long refreshScreen(unsigned long sinceRefresh) {
    unsigned long timeNow = millis();
    if(timeNow - sinceRefresh >= REFRESH_RATE) {
        draw();
        return timeNow;
    }
    return sinceRefresh;
}
