#include "Arduino.h"
#include "TwoWheel.h"
#include "SensorArray.h"
#include "Map.h"

int func = 1;

int distance;
int duration;

unsigned long currT = 0;
unsigned long startT = 0;

TwoWheel rumba;

void setup()
{
    Serial.begin(9600);

    Serial.println("Start Setup");
    rumba = TwoWheel();
    rumba.init(3, 5, 6, 9, 10, 11);

    rumba.calibrateMode();
    // rumba.calibrate(2.54, 4); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
    // rumba.setPos(0,0,0);
    // rumba.setSpeeds(1,1); // 1ft /sec

    Serial.println("Done Setup");
    startT = millis();
}

void loop()
{
    currT = millis();
    if (currT - startT < 10000)
    {

        rumba.moveForward();
        Serial.print(rumba.x);
        Serial.print(" ");
        Serial.println(rumba.y);

        rumba.update(currT);
    }

    delay(200);
}
