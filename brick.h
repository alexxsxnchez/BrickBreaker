#ifndef BRICK_H
#define BRICK_H

    #define BRICK_WIDTH 3
    #define BRICK_HEIGHT 3
    #define MAX_HP 2
    #define ROWS 6
    #define COLS 8
  
    typedef struct {
        int x;
        int y;
        int hp;
    } brick;
    
    brick *initBricks(brick *);
    void drawBricks(brick *);
    void drawBrick(brick *);
    brick *getBrickAt(int, int);
    void lowerBrickHealth(brick *);
    int getBrickCount();
#endif
