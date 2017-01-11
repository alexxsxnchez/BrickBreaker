static brick bricks[ROWS][COLS] = {0};
static int brickCount = 0;

void initBricks() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            brick brick;
            // random brick generation
            randomSeed(analogRead(0));
            int r = random(4);
            if(r == 0) {
                brick.hp = 0;
            }
            else {
                brickCount++;
                if(r == 1) {
                    brick.hp = MAX_HP;
                }
                else {
                    brick.hp = 1;
                }
            }
            brick.x = j * (BRICK_WIDTH + 1);
            brick.y = OLED_WIDTH - 1 - i * (BRICK_HEIGHT + 1);
            bricks[i][j] = brick;
        }
    }
} 
void drawBricks() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            drawBrick(&bricks[i][j]);
        }
    }
}
// draw a single brick
void drawBrick(brick *brick) {
    OrbitOledMoveTo(brick -> y, brick -> x);
    int hp = brick -> hp;
    int pattern;
    switch(hp) {
        case 0: 
            pattern = iptnBlank;
            break;
        case 2:
            pattern = iptnSolid; 
            break;
        default:
            pattern = iptnCross;
    }
    OrbitOledSetFillPattern(OrbitOledGetStdPattern(pattern));
    OrbitOledFillRect(brick -> y - BRICK_HEIGHT + 1, brick -> x + BRICK_WIDTH - 1);
}

brick *getBrickAt(int xCoor, int yCoor) {
    int x = xCoor / (BRICK_WIDTH + 1);
    int y = (OLED_WIDTH - 1 - yCoor) / (BRICK_HEIGHT + 1);
    if(x >= COLS || y >= ROWS || bricks[y][x].hp <= 0) {
        return NULL;
    }
    return &bricks[y][x];
}

void lowerBrickHealth(brick *brick) {
    if(brick != NULL) {
        brick -> hp--;
        if(brick -> hp <= 0) {
            brickCount--;
            uint32_t currentBricksBroken = getValue(BRICKS_BROKEN_ADDRESS);
            currentBricksBroken++;
            updateValue(currentBricksBroken, BRICKS_BROKEN_ADDRESS); // update the stats stored in the EEPROM
        }
        randomSeed(analogRead(0));
        int r = random(5);
        if(r == 0 && !lifeAvailable()) {  // 20% chance of generating an extra life
            initLife(brick -> x, brick -> y);
        }
    }
}

int getBrickCount() {
    return brickCount;
}
