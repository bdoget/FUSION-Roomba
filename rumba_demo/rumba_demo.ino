#include "Arduino.h"
#include "TwoWheel.h"
#include "Map.h"

int distance;
int duration;
unsigned long currT = 0;
unsigned long startT = 0;
TwoWheel rumba;
Map map;

#define BUTTON_PIN 7


void setup() {
  Serial.begin(9600);

  Serial.println("Start Setup");
  rumba = TwoWheel(3, 4, 5, 6, 7, 8);
  rumba.setPinSpeeds(100,100);

  // rumba.calibrate(2.54, 4); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
  // rumba.setPos(0,0,0);
  // rumba.setSpeeds(1,1); // 1ft /sec

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Done Setup");
  startT = millis();
}

void loop()
{
  currT = millis();

  // if (buttonState == HIGH) {
  //   rumba.moveForward();
  // } else {
  //   rumba.moveStop();
  // }


  // if (currT - startT < 10000)
  {

    rumba.moveForward();
    Serial.print(rumba.x);
    Serial.print(" ");
    Serial.println(rumba.y);

    rumba.update(currT);
  }

  delay(200);
}
