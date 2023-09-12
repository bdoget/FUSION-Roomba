#include "Sensors.h"
#include "Arduino.h"

void Sensors::initPos(double x1A, double y1A, double x2A, double y2A, double x3A, double y3A) {
    x1 = x1A;
    y1 = y1A;
    x2 = x2A;
    y2 = y2A;
    x3 = x3A;
    y3 = y3A;
}

void Sensors::initPins(int trig1A, int echo1A, int trig2A, int echo2A, int trig3A, int echo3A)
{

    trig1 = trig1A;
    echo1 = echo1A;
    trig2 = trig2A;
    echo2 = echo2A;
    trig3 = trig3A;
    echo3 = echo3A;

    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT_PULLUP);
    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT_PULLUP);
    pinMode(trig3, OUTPUT);
    pinMode(echo3, INPUT_PULLUP);
}

void Sensors::setEffect(double effectiveDistA) {
    effectiveDist = effectiveDistA;
}

double Sensors::getDist(int sensorNum) {
    switch (sensorNum) {
    case 1:
        return getDist_(trig1, echo1);
    case 2:
        return getDist_(trig2, echo2);
    case 3:
        return getDist_(trig3, echo3);
    }
    return 0.0;
}

double Sensors::getX(int sensorNum) {
    switch (sensorNum) {
    case 1:
        return x1;
    case 2:
        return x2;
    case 3:
        return x3;
    }
    return 0.0;
}

double Sensors::getY(int sensorNum) {
    switch (sensorNum) {
    case 1:
        return y1;
    case 2:

        return y2;
    case 3: 
        return y3;
    }  
    return 0.0;
}

double Sensors::getDist_(int trig, int echo) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Measure the duration of the ultrasonic pulse
    long duration = pulseIn(echo, HIGH);
    double distance = duration * 0.034 / 2 * 3.937;
    
    if (distance > effectiveDist) {
        distance = -1;
    }

    return distance;
}
void Sensors::printPos() {
    Serial.print("x1: ");
    Serial.print(x1);
    Serial.print(" y1: ");
    Serial.print(y1);
    Serial.print(" x2: ");
    Serial.print(x2);
    Serial.print(" y2: ");
    Serial.print(y2);
    Serial.print(" x3: ");
    Serial.print(x3);
    Serial.print(" y3: ");
    Serial.println(y3);
}
void Sensors::printPins() {
    Serial.print("trig1: ");
    Serial.print(trig1);
    Serial.print(" echo1: ");
    Serial.print(echo1);
    Serial.print(" trig2: ");
    Serial.print(trig2);
    Serial.print(" echo2: ");
    Serial.print(echo2);
    Serial.print(" trig3: ");
    Serial.print(trig3);
    Serial.print(" echo3: ");
    Serial.println(echo3);
}
void Sensors::printDist() {
    Serial.print("dist1: ");
    Serial.print(getDist(1));
    Serial.print(" dist2: ");
    Serial.print(getDist(2));
    Serial.print(" dist3: ");
    Serial.println(getDist(3));
}
