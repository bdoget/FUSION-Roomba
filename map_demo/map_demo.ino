#include "Arduino.h"
#include "Sensors.h"
#include "TwoWheel.h"

unsigned long startT = 0;
Sensors sensors;
TwoWheel rumba;

void setup()
{
    Serial.begin(9600);
    Serial.println("Start Setup");

    rumba.init(A0, 4, 5, A1, 7, 8);
    rumba.calibrate(360, 2 * PI); // 3ft in 1 sec, 2.05*PI rad in 1 sec
    // rumba.setPinSpeeds(128, 128);
    rumba.setSpeeds(182, 1.04 * PI);
    rumba.setPos(5, 5, 0);

    sensors.initPos(0, 0, -10, 0, 10, 0);
    sensors.initPins(A2, A3, A4, A5, 3, 2);
    sensors.setEffect(600);

    Serial.println("Done Setup");
    delay(1000);
    startT = millis();

    rumba.moveForward();
}

bool checkSensors()
{
    double dist1 = sensors.getDist(1); // mid
    double dist2 = sensors.getDist(2); // right
    double dist3 = sensors.getDist(3); // left
    // Serial.print(dist1);
    // Serial.print(" | ");
    // Serial.print(dist2);
    // Serial.print(" | ");
    // Serial.print(dist3);
    // Serial.println("|");

    double check = 160.0;

    return ((dist1 > 0.0 && dist1 < check) || (dist2 > 0.0 && dist2 < check) || (dist3 > 0.0 && dist3 < check));
}

void turnRandom()
{
    if (checkSensors()) {
        rumba.moveStop();
        delay(200);
        rumba.moveBackward();
        delay(100);

        bool temp = true;
        while (temp) {
            rumba.moveStop();
            delay(200);
            rumba.moveLeft();
            delay(random(200, 800));
            rumba.moveStop();
            delay(200);
            temp = checkSensors();
        }
    }
}

void checkWhileTurn()
{
    if (checkSensors())
    {
        rumba.moveStop();
        delay(200);
        rumba.moveLeft();
        while (checkSensors())
        {
            rumba.update();
            rumba.print();
        }
        rumba.moveStop();
        delay(100);
    }
}

void loop()
{

    turnRandom();
    rumba.moveForward();
    rumba.update();
    rumba.print();
    delay(100);
}
