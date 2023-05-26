#ifndef TwoWheel_H
#define TwoWheel_H

// #if (ARDUINO >= 100)
#include <Arduino.h>
#include "Wheel.h"
// #else
// #include <WProgram.h>
// #endif

class TwoWheel
{
public:
    float x, y;
    float dir;
    /*
    (0,0) = origin, in 
    0rad = north, 90deg = east, 
    */
    void init(int enA_, int in1_, int in2_, int enB, int in3_, int in4_);
    void calibrate(float dist, float turn, float dTime=1, float tTime=1);
    // distTimed = dist of rumba at maxspeed for 1 sec
    // turnTimed = radians turned of rumba at maxspeed for 1 sec

    bool setSpeeds(float move, float turn); // move (ft/sec), turn (rad/sec)
    void setPos(float x_, float y_, float dir_);

    void update(unsigned long newTime);

// Basic move functions
    void moveStop();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveChar(char code);


// Debug - gets
    float getSpeed();
    float getTurnSpeed();
    int getPinSpeed();
    int getPinTurnSpeed();
    void setPinSpeeds(int move, int turn);

    void calibrateMode();

private:
    Wheel left, right;
    
    float maxMoveSpeed, maxTurnSpeed;
    // maxMoveSpeed in ft/sec 
    // maxTurnSpeed in rad/sec

    float setRealMoveSpeed, setRealTurnSpeed;
    // real set speeds from setSpeeds(float, float)

    int mSpeed, tSpeed;
    // The translated set speeds from setSpeeds(float,float)

    int currSpeed, currTSpeed; // 0-255
    // currSpeed = mSpeed when moving or 0 when stopped or turning
    // currTSpeed = tSpeed when turning or 0 when moving or stopped
    // PWM signal strengths

    unsigned long currTime;
};


#endif