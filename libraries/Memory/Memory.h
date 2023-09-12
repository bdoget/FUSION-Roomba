#ifndef Memory_H
#define Memory_H

#include <Arduino.h>
#include "TwoWheel.h"
#include "Sensors.h"

class Memory
{
public:
    int array2D[1200][1200]; // 1/10 inches

    int rumba[120][120]; // 1/10 inches

    void init();
    void print();

    void spin360(TwoWheel rumba, Sensors sensors);
    double FindNewDirection();
    void SetNewDirection(TwoWheel rumba, double dir);


    // spin in 360 check
    // move forward

    // void loop() {
    //     if spinTimer:
    //         stop;
    //         spin360;
    //     if canGoStraight:
    //         goStraight;
    //     else:
    //         spin360;
    //         FindNewDirection;
    //         SetNewDirection;
            
    //     gostraight
    // }

private:
    unsigned long currTime;
};

#endif