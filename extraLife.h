#ifndef EXTRALIFE_H
#define EXTRALIFE_H

    #define INIT_BALL_X (DEFAULT_PADDLE_WIDTH / 2 + INIT_PADDLE_X)
    #define INIT_BALL_Y PADDLE_Y + 1
    #define LIFE_SPEED -1
    #define LIFE_SIZE 2
  
    typedef struct {
        int x;  //x-position
        int y;  // y-position
    } life;
    
    void initLife(int, int);
    void drawLife();
    void showLife(boolean);
    bool extraLifeCollisions(); // returns if ball was lost
    bool lifeAvailable();
    void setLifeAvailable(bool);
#endif
