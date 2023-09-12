#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>

class Sensors {
public:
    void initPos(double x1A, double y1A, double x2A, double y2A, double x3A, double y3A);
    void initPins(int trig1A, int echo1A, int trig2A, int echo2A, int trig3A, int echo3A);
    void setEffect(double effectiveDistA);

    double getDist(int sensorNum);
    double getX(int sensorNum);
    double getY(int sensorNum);

    void printPos();
    void printPins();
    void printDist();

private:
    double x1, y1, x2, y2, x3, y3;
    int trig1, echo1, trig2, echo2, trig3, echo3;
    double effectiveDist = 0.0;

    double getDist_(int trig, int echo);

};

#endif // Sensor_H
