#ifndef BALL_H
#define BALL_H

    #define INIT_BALL_X (PADDLE_WIDTH / 2 + INIT_PADDLE_X)
    #define INIT_BALL_Y PADDLE_Y + 1
  
    typedef struct {
        int x;  //x-position
        int y;  // y-position
        int xSpeed;
        int ySpeed;
    } ball;
    
    void initBall();
    void drawBall();
    void showBall(boolean);
    int myRound(double); // helper function for checkForCollision()
    bool checkForCollision(); // returns if ball was lost  
    bool isWallCollision(int, int);
    bool isBrickCollision(int, int);
    bool isPaddleCollision(int, int);
#endif
