#include "Wheel.h"
#include "Arduino.h"

// ---------------------------------------------------------------------------
void Wheel::init(int enA_, int in1_, int in2_)
{
    enA = enA_;
    in1 = in1_;
    in2 = in2_;
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    // Serial.println(enA);
}

void Wheel::moveSpeed(int speed)
{
    // Serial.print(speed);
    analogWrite(enA, speed);
    if (speed >= 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }
}

