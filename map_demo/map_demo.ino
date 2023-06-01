#include "Arduino.h"
#include "TwoWheel.h"
// #include "SensorArray.h"
#include "PathBrain.h"

unsigned long currT = 0;
unsigned long startT = 0;
TwoWheel rumba;
PathBrain myPath;

void setup()
{
    Serial.begin(9600);
    Serial.println("Start Setup");

    rumba.init(3, 4, 5, 6, 7, 8);
    rumba.setPos(5,5,0);
    rumba.setPinSpeeds(100, 100);

    myPath.init(60, 60, 7, 10); // inches

    Serial.println("Done Setup");
    startT = millis();
}

void loop()
{
    currT = millis();
    rumba.update(currT);
    char dirCode = myPath.getDir(rumba.x, rumba.y, rumba.dir);
    rumba.moveChar(dirCode);

    Serial.print(dirCode);
    Serial.print(" ");
    Serial.print(rumba.x);
    Serial.print(" ");
    Serial.print(rumba.y);
    Serial.print(" ");
    Serial.println(rumba.dir);
    
    delay(200);
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
