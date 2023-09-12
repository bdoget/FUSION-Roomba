#include "Arduino.h"
#include "TwoWheel.h"

unsigned long startT = 0;
TwoWheel rumba;

/*  
    Calbration code to get rumba's max linear and angular velocity.

    This code will stop for 1 second,
    then move forward for 1 second, 
    then stop.

    Plug the distance moved and angle rotated into the calibration function
    for the rumba class.
    Ex: rumba.calibrate(2.54, 4); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
    Ex: rumba.calibrate(3ft, 2.05PI rad); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
    Ex: rumba.calibrate(360, 2.05*PI); // moved 2.54 ft in 1 sec, 4 rads in 1 sec

    ** NOTE: ** 
        Measure the distance in INCHES and angle in RADIANS.
*/

void setup()
{
    Serial.begin(9600);
    Serial.println("Start Setup");
    rumba.init(A0, 4, 5, A1, 7, 8);
    rumba.calibrateMode();
    Serial.println("Done Setup");

    delay(1000);
    startT = millis();
    // rumba.moveForward();
    rumba.moveLeft();
}

void loop() {
    if (millis() - startT >= 1000) {
        rumba.moveStop();
        delay(10000);
    }
    delay(10);
}

/*
            o = go to 0,0
            x = go around obstacle
            f = continue path
            g = go to nearest point
            s = stop
        */

// rumba.calibrate(2.54, 4); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
// rumba.setPos(0,0,0);
// rumba.setSpeeds(1,1); // 1ft /sec

// // if (currT - startT < 10000)
//       rumba.moveForward();
//       Serial.print(rumba.x);
//       Serial.print(" ");
//       Serial.println(rumba.y);
