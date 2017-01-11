static life lifeObj;
static life *lifePtr = &lifeObj;
static bool extraLifeAvailable = false;

void initLife(int x, int y) {
    lifePtr -> x = x;
    lifePtr -> y = y;
    extraLifeAvailable = true;
}

void drawLife() {
    bool lifeLost = extraLifeCollision();
    showLife(false);
    if(lifeLost) {
        extraLifeAvailable = false;
        return;     
    }
    lifePtr -> y += LIFE_SPEED;
    showLife(true);
}
void showLife(boolean makeVisible) {
    int pattern;
    if(makeVisible) {
        pattern = iptnSolid;
    }
    else {
        pattern = iptnBlank;
    }
    OrbitOledSetFillPattern(OrbitOledGetStdPattern(pattern));
    int x = lifePtr -> x;
    int y = lifePtr -> y;
    OrbitOledMoveTo(y, x);
    OrbitOledFillRect(y + LIFE_SIZE - 1, x + LIFE_SIZE - 1);
}

bool extraLifeCollision() {
    int x = lifePtr -> x;
    int y = lifePtr -> y + LIFE_SPEED;
    brick *brick = getBrickAt(x, y);
    if(y <= 0 || brick != NULL) {
        return true;
    }
    paddle *paddlePtr = getPaddlePtr();
    if(y <= paddlePtr -> y) {
        int paddleX;
        if(paddlePtr -> x < 0) {
            paddleX = (paddlePtr -> x % -OLED_HEIGHT) + OLED_HEIGHT - 1;
        }
        else {
            paddleX = paddlePtr -> x % OLED_HEIGHT;
        }
        if(x < paddleX) {
            paddleX -= OLED_HEIGHT;
        }
        int collisionX = x - paddleX;
        if(collisionX >= 0 && collisionX <= PADDLE_WIDTH) {
            extraLife();
            return true;
        }
    }
    return false; 
}
bool lifeAvailable() {
    return extraLifeAvailable;
}

void setLifeAvailable(bool isLife) {
    extraLifeAvailable = isLife;
}
