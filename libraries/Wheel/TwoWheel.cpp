#include "TwoWheel.h"
#include "Wheel.h"
#include "Arduino.h"

// ---------------------------------------------------------------------------

void TwoWheel::init(int enA_, int in1_, int in2_, int enB_, int in3_, int in4_) {
    left = Wheel();
    right = Wheel();
    left.init(enA_, in1_, in2_);
    right.init(enB_, in3_, in4_);

    mSpeed = 0;
    tSpeed = 0;
    currSpeed = 0;
    currTSpeed = 0;
}

void TwoWheel::calibrate(double dist, double turn, double dTime = 1, double tTime = 1) {
    maxMoveSpeed = dist/dTime;
    maxTurnSpeed = turn/tTime;
}

bool TwoWheel::setSpeeds(double move, double turn) {
    if (move > maxMoveSpeed or move < 0 or turn > maxTurnSpeed or turn < 0)
        return false;
    realMSpeed = move;
    realTSpeed = turn;
    mSpeed = move *255 / maxMoveSpeed;
    tSpeed = turn *255 / maxTurnSpeed;
    return true;
}

void TwoWheel::setPos(double x_, double y_, double dir_) {
    x = x_;
    y = y_;
    dir = dir_;
}

void TwoWheel::update()
{
    unsigned long newTime = millis(); // current time
    double dTime = newTime - currTime;  // time since last update
    dTime /= 1000; // convert to seconds

    // current time - last time * speed & dir
    if (currSpeed != 0) {
        x += realMSpeed * cos(dir) * dTime; // currSpeed
        y += realMSpeed * sin(dir) * dTime;
    }
    else if (currTSpeed != 0) {
        dir += (realTSpeed * dTime) + 2*PI;
        // dir += fmod(realTSpeed, ((double) PI));
        dir = fmod(dir, ((double) 2*PI));
    }
    currTime = newTime;
}

void TwoWheel::moveStop()
{
    left.moveSpeed(0);
    right.moveSpeed(0);

    currSpeed = 0;
    currTSpeed = 0;
}

void TwoWheel::moveForward()
{
    left.moveSpeed(mSpeed);
    right.moveSpeed(mSpeed);

    // Serial.print(mSpeed);
    
    currSpeed = mSpeed;
    currTSpeed = 0;
}

void TwoWheel::moveBackward()
{
    left.moveSpeed(-1*mSpeed);
    right.moveSpeed(-1*mSpeed);

    currSpeed = -1*mSpeed;
    currTSpeed = 0;
}

void TwoWheel::moveLeft()
{
    left.moveSpeed(-1*tSpeed);
    right.moveSpeed(tSpeed);

    currSpeed = 0;
    currTSpeed = tSpeed;
}

void TwoWheel::moveRight()
{
    left.moveSpeed(tSpeed);
    right.moveSpeed(-1*tSpeed);

    currSpeed = 0;
    currTSpeed = -1*tSpeed;
}

void TwoWheel::moveChar(char code) {
    switch (code) {
        case 'f':
            return moveForward();
        case 'b':
            return moveBackward();
        case 'l':
            return moveLeft();
        case 'r':
            return moveRight();
        case 's':
            return moveStop();
    }
    Serial.print("lmao");
}

// # Debugs and gets

double TwoWheel::getSpeed() {
    return realMSpeed;
}

double TwoWheel::getTurnSpeed() {
    return realTSpeed;
}

int TwoWheel::getPinSpeed()
{
    return mSpeed;
}

int TwoWheel::getPinTurnSpeed()
{
    return tSpeed;
}

void TwoWheel::setPinSpeeds(int move, int turn) {
    mSpeed = move;
    tSpeed = turn;
}
void TwoWheel::print() {
    Serial.print("Rumba: (");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(") , dir: ");
    Serial.print(dir);
    Serial.print(",  Moving ");
    if (currSpeed != 0) {
        if (currSpeed < 0)
            Serial.print("Backward");
        else
            Serial.print("Forward");
    }
    else if (currTSpeed != 0) {
        if (currTSpeed < 0)
            Serial.print("Left");
        else
            Serial.print("Right");
    }
    Serial.print(", Speeds: (");
    Serial.print(currSpeed);
    Serial.print(",");
    Serial.print(currTSpeed);
    Serial.println(")");

    // "Rumba: (x,y) , dir: dir,  Moving Right, Speeds: (m,t)";

}
void TwoWheel::calibrateMode()
{
    // Helps bypass calibrate() and setSpeeds()
    setPinSpeeds(255,255);
}
