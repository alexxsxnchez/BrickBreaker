static paddle paddleObj;
static paddle *paddlePtr = &paddleObj;

void initPaddle() {
    paddlePtr -> x = INIT_PADDLE_X;
    paddlePtr -> y = PADDLE_Y;
    paddlePtr -> dir = 0;
}

void drawPaddle() {
    setPaddleDir(getMotionDir());
    int dir = paddlePtr -> dir;
    if(dir) {
        showPaddle(false);
        paddlePtr -> x += (dir * PADDLE_SPEED);
    }
    showPaddle(true);
}

void showPaddle(boolean makeVisible) {
    // show or hide paddle
    int pattern;
    if(makeVisible) {
        pattern = iptnSolid;
    }
    else {
        pattern = iptnBlank;
    }
    OrbitOledSetFillPattern(OrbitOledGetStdPattern(pattern));
    // draw rectangle from "fromX" and "fromY" to "toX" and "toY"
    int fromY = paddlePtr -> y;
    int fromX;
    if(paddlePtr -> x < 0) {
        fromX = (paddlePtr -> x % -OLED_HEIGHT) + OLED_HEIGHT - 1;
    }
    else {
        fromX = paddlePtr -> x % OLED_HEIGHT;
    }
    OrbitOledMoveTo(fromY, fromX);
    int toY = fromY - PADDLE_HEIGHT + 1;
    int toX = fromX + PADDLE_WIDTH - 1;
    // wrap paddle to other side of screen
    if(toX >= OLED_HEIGHT) {
        OrbitOledFillRect(toY, OLED_HEIGHT - 1);
        OrbitOledMoveTo(fromY, 0);
        OrbitOledFillRect(toY, toX % OLED_HEIGHT);
    }
    else {
        OrbitOledFillRect(toY, toX);
    }
}

void setPaddleDir(int dir) {
    paddlePtr -> dir = dir;
}
paddle *getPaddlePtr() {
    return paddlePtr;
}
