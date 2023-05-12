#ifndef Wheel_H
#define Wheel_H

// #if (ARDUINO >= 100)
#include <Arduino.h>
// #else
// #include <WProgram.h>
// #endif


class Wheel {
public:
    Wheel();
    Wheel(int enA_, int in1_, int in2_);
    void moveSpeed(int speed);

    // maybe add acceleration and deceleration function
    // accelerate(newSpeed, time) or int maxSpeedStep
    // update() to change internal speed

private:
    int enA;
    int in1;
    int in2;

    int speed;
};

#endif