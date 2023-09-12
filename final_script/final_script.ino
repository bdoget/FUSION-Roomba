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
    rumba.calibrate(1, 1); // 3ft in 1 sec, 2.05*PI rad in 1 sec
    // rumba.setPinSpeeds(255, 255);
    rumba.setSpeeds(1, 1);
    // rumba.setSpeeds(182, 1.04 * PI);
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

    double check = 175.0;
    double side = 90.0;

    return ((dist1 > 0.0 && dist1 < check) || (dist2 > 0.0 && dist2 < side) || (dist3 > 0.0 && dist3 < side));
}

int spinCheck()
{
    double dist1 = sensors.getDist(1); // mid
    double dist2 = sensors.getDist(2); // right
    double dist3 = sensors.getDist(3); // left
    double check = 155.0;
    double side = 70.0;

    if (dist1 > 0.0 && dist1 < check)
        return 1;
    if (dist2 > 0.0 && dist2 < side)
        return 2;
    if (dist3 > 0.0 && dist3 < side)
        return 3;
    return 0;
}

int delayTurn(long time)
{ // delays for time, and checks spinning. if breaks sensor, then safety stop
    unsigned long startTime = millis();
    int ans = 0;
    while (ans == 0 && millis() - startTime < time)
    {
        ans = spinCheck();
        if (ans > 0)
        {
            rumba.moveStop();
        }
    }
    return ans;
}

void turnRandom()
{
    if (checkSensors())
    {
        rumba.moveStop();
        delay(100);
        rumba.moveBackward();
        delay(300);

        rumba.moveStop();
        delay(100);

        bool temp = true;
        int dir = 2;

        while (temp)
        {
            // rumba.moveStop();
            // delay(200);

            if (dir == 2)
                rumba.moveRight();
            else
                rumba.moveLeft();

            int obs = delayTurn(random(150, 300));
            rumba.moveStop();

            if (obs == 2)
            {
                dir = 3;
            }
            else if (obs == 3)
            {
                dir = 2;
            }
            else if (obs == 1)
            {
                rumba.moveBackward();
                delay(200);
                rumba.moveStop();
                dir = 2;
            }

            // delay(random(150, 300));
            // rumba.moveStop();

            delay(300); // nenad pause
            temp = checkSensors();
        }
    }
}

void loop()
{
    // checkWhileTurn();
    turnRandom();
    // Wheelie
    rumba.moveForward();
    delay(100);
    rumba.moveBackward();
    delay(400);
    rumba.moveStop();
    delay(100);
    rumba.moveForward();
    rumba.update();
    rumba.print();
    delay(100);
}
