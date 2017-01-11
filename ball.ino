static ball ballObj;
static ball *ballPtr = &ballObj;

void initBall() {
    ballPtr -> x = INIT_BALL_X;
    ballPtr -> y = INIT_BALL_Y;
    ballPtr -> xSpeed = 0;
    ballPtr -> ySpeed = 0;
}

void drawBall() {
    int xSpeed = ballPtr -> xSpeed;
    int ySpeed = ballPtr -> ySpeed;
    if(xSpeed || ySpeed) {
        bool ballLost = checkForCollision();
        if(ballLost) {
            loseLife();
            respawn();
            return;     
        }
        showBall(false);
        ballPtr -> x += ballPtr -> xSpeed;
        ballPtr -> y += ballPtr -> ySpeed;
    }
    else {
        ballPtr -> ySpeed = 2;
    }
    showBall(true);
}
void showBall(boolean makeVisible) {
    int pattern;
    if(makeVisible) {
        pattern = iptnSolid;
    }
    else {
        pattern = iptnBlank;
    }
    OrbitOledSetFillPattern(OrbitOledGetStdPattern(pattern));
    int x = ballPtr -> x;
    int y = ballPtr -> y;
    OrbitOledMoveTo(y, x);
    OrbitOledFillRect(y, x);
}
// helper function for checkForCollision()
int myRound(double n) {
    double whole = floor(n);
    double remainder = n - whole;
    if(remainder >= 0.5) {
        return (int) whole + 1;
    }
    return (int) whole;
}

bool checkForCollision() {
    int x = ballPtr -> x;
    int y = ballPtr -> y;
    int xSpeed = ballPtr -> xSpeed;
    int ySpeed = ballPtr -> ySpeed;
    int n = max(abs(xSpeed), abs(ySpeed));
    double sumX = 0;
    double sumY = 0;
    int xMultiplier = xSpeed / abs(xSpeed);
    int yMultiplier = ySpeed / abs(ySpeed);
    for(int i = 1; i <= n; i++) {
        sumX += (double) abs(xSpeed) / (double) n;
        sumY += (double) abs(ySpeed) / (double) n;
        if(myRound(sumX) == 1) {
            x += 1 * xMultiplier;
            sumX -= 1;
        }
        if(myRound(sumY) == 1) {
            y += 1 * yMultiplier;
            sumY -= 1;
        }
        if(y <= 0) {
            return true;
        }
        bool wallBounce = isWallCollision(x, y);
        if(isBrickCollision(x, y) || wallBounce) {
            return false;
        }
        if(isPaddleCollision(x, y)) {
            return false;
        }
    }
    return false;
}

bool isWallCollision(int x, int y) {
    if(x < 0 || x > OLED_HEIGHT - 1 || y > OLED_WIDTH - 1) {
        if(y > OLED_WIDTH - 1) {
            ballPtr -> ySpeed *= -1;
        }
        if(x < 0 || x > OLED_HEIGHT - 1) {
            ballPtr -> xSpeed *= -1;
        }
        return true;
    }
    return false;
}

bool isBrickCollision(int x, int y) {
    brick *brick = getBrickAt(x, y);
    if(brick != NULL) {
        lowerBrickHealth(brick);
        int brickX = brick -> x;
        int brickY = brick -> y;
        int xSpeed = ballPtr -> xSpeed;
        int ySpeed = ballPtr -> ySpeed;
        int edgeCaseX = brickX + BRICK_WIDTH;
        int edgeCaseY = brickY - BRICK_HEIGHT;
        if(x == edgeCaseX && y == edgeCaseY) {
            lowerBrickHealth(getBrickAt(x + BRICK_WIDTH + 1, y));
            lowerBrickHealth(getBrickAt(x, y - BRICK_HEIGHT - 1));
            lowerBrickHealth(getBrickAt(x + BRICK_WIDTH + 1, y - BRICK_HEIGHT - 1));
            if(abs(xSpeed) == abs(ySpeed)) {
                xSpeed *= -1;
                ySpeed *= -1;
            } 
            else if (abs(xSpeed) > abs(ySpeed)) {
                xSpeed *= -1;
            }
            else {
                ySpeed *= -1;
            }
        }
        else if (abs(y - (brickY - 1)) >= abs(x - (brickX + 1))) {
            ySpeed *= -1; //ERROR
        }
        else {
            xSpeed *= -1;
        }
        ballPtr -> xSpeed = xSpeed;
        ballPtr -> ySpeed = ySpeed;
        return true;
    }
    return false;
}

bool isPaddleCollision(int x, int y) {
    paddle *paddlePtr = getPaddlePtr();
    if(y == paddlePtr -> y) {
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
        switch(collisionX) {
            case 0:
                ballPtr -> xSpeed = -2;
                ballPtr -> ySpeed = 1;
                break;
            case 1:
            case 2:
                ballPtr -> xSpeed = -2;
                ballPtr -> ySpeed = 2;
                break;
            case 3:
                ballPtr -> xSpeed = -1;
                ballPtr -> ySpeed = 2;
                break;
            case 4:
                ballPtr -> xSpeed = 0;
                ballPtr -> ySpeed = 2;
                break;
            case 5:
                ballPtr -> xSpeed = 1;
                ballPtr -> ySpeed = 2;
                break;
            case 6:
            case 7:
                ballPtr -> xSpeed = 2;
                ballPtr -> ySpeed = 2;
                break;
            case 8:
                ballPtr -> xSpeed = 2;
                ballPtr -> ySpeed = 1;
                break;
        }
        return true;
    }
    return false;
}
