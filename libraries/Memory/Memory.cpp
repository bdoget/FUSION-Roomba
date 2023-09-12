#include "Memory.h"
#include "Arduino.h"

void Memory::init()
{
    for (int i = 0; i < 1200; i++) {
        for (int j = 0; j < 1200; j++) {
            array2D[i][j] = 0;
        }
    }

    for (int i = 0; i < 120; i++) {
        for (int j = 0; j < 120; j++) {
            rumba[i][j] = 0;
        }
    }
}
void Memory::print()
{
    for (int i = 0; i < 1200; i++)
    {
        // Iterate through the columns of the array
        for (int j = 0; j < 1200; j++)
        {
            // Send the value at the current row and column to the serial port
            Serial.print(array2D[i][j]);
            // Serial.print(" "); // Separate values with a space or any other delimiter
        }
        Serial.println(); // Move to the next line after each row is sent
    }
    delay(1000);
}

void Memory::spin360(TwoWheel rumba, Sensors sensors)
{
    // store rumba startDir
    double startDir = rumba.dir;

    
    // spin 360

}

void Memory::placeSensors(TwoWheel rumba, Sensors sensors) {
    // get all 3 dists from sensors
    double dist1 = sensors.getDist(1);
    double dist2 = sensors.getDist(2);
    double dist3 = sensors.getDist(3);

    if (dist1 > 0) {
        // get sensor's real pos
        double sensorX = rumba.x + rotateX(sensors.getX(1), sensors.getY(1), rumba.dir);
        double sensorY = rumba.y + rotateY(sensors.getX(1), sensors.getY(1), rumba.dir);
        
    }

}

// void Memory::placeSensor()

double Memory::rotateX(float x, float y, float angle)
{
    return x * cos(angle) - y * sin(angle);
}

double Memory::rotateY(float x, float y, float angle)
{
    return x * sin(angle) + y * cos(angle);
}

double Memory::FindNewDirection()
{
    return 0.0;
}

void Memory::SetNewDirection(TwoWheel rumba, double dir)
{
}
