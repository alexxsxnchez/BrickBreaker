#ifndef PADDLE_H
#define PADDLE_H

    #define INIT_PADDLE_X ((OLED_HEIGHT - PADDLE_WIDTH) / 2)
    #define PADDLE_Y 4
    #define PADDLE_WIDTH 9
    #define PADDLE_HEIGHT 2
    #define PADDLE_SPEED 2
    
    typedef struct {
        int x;  //x-position
        int y;  // y-position
        int dir; // x-heading
        //int width;
    } paddle;
    
    void initPaddle();
    void drawPaddle();
    void showPaddle();
    void setPaddleDir(int);
    paddle *getPaddlePtr();
#endif
