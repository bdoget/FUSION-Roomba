#ifndef TwoWheel_H
#define TwoWheel_H

#include <Arduino.h>
#include "Wheel.h"

class TwoWheel
{
public:
    double x, y;
    double dir;
    /*
    (0,0) = origin, in 
    0rad = east, 90deg = north
    */
    void init(int enA_, int in1_, int in2_, int enB, int in3_, int in4_);
    void calibrate(double dist, double turn, double dTime=1, double tTime=1);
    // distTimed = dist of rumba at maxspeed for 1 sec
    // turnTimed = radians turned of rumba at maxspeed for 1 sec

    bool setSpeeds(double move, double turn); // move (inches/sec), turn (rad/sec)
    void setPos(double x_, double y_, double dir_);

    void update();

// Basic move functions
    void moveStop();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveChar(char code);


// Debug - gets
    double getSpeed();
    double getTurnSpeed();
    int getPinSpeed();
    int getPinTurnSpeed();
    void setPinSpeeds(int move, int turn);
    void print();

    void calibrateMode();

private:
    Wheel left, right;
    
    double maxMoveSpeed, maxTurnSpeed;
    // maxMoveSpeed in ft/sec 
    // maxTurnSpeed in rad/sec

    double realMSpeed, realTSpeed;
    // real set speeds from setSpeeds(float, float)

    int mSpeed, tSpeed;
    // The translated set speeds from setSpeeds(float,float)

    int currSpeed, currTSpeed; // 0-255
    // currSpeed = mSpeed when moving or 0 when stopped or turning
    // currTSpeed = tSpeed when turning or 0 when moving or stopped
    // PWM signal strengths


    // float maxMSpeed, maxTSpeed; // ft/sec, rad/sec
    // float setMSpeed, setTSpeed; // ft/sec, rad/sec
    // int setPinMSpeed, setPinTSpeed; // 0-255
    // int mSpeed, tSpeed; // 0-255 current speed

    unsigned long currTime;
};


#endif