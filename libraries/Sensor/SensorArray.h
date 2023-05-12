#ifndef Sensor_H
#define Sensor_H

class SensorArray
{

public:
    // Gets the distance 90 degrees to the left of the Roomba
    float getDistLeft();
    // Gets the distance 90 degrees to the right of the Roomba
    float getDistRight();
    // Gets whether an obstacle in the Roomba's field of view will cause a collision
    bool isTooCloseObstacle();
};

#endif // Sensor_H
