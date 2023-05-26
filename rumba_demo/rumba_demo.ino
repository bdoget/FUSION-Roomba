#include "Arduino.h"
#include "TwoWheel.h"
#include "SensorArray.h"
#include "Map.h"


unsigned long currT = 0;
unsigned long startT = 0;
TwoWheel rumba;
Map map;


void setup() {
  Serial.begin(9600);
  Serial.println("Start Setup");

  rumba.init(3, 4, 5, 6, 7, 8);
  rumba.setPinSpeeds(100,100);

  map.init(60, 60, 7, 10); // inches

  Serial.println("Done Setup");
  startT = millis();
}

void loop() {
  currT = millis();
  rumba.update(currT);
  char dirCode = map.getDir(rumba.x, rumba.y, rumba.dir);
  rumba.moveChar(dirCode);

  delay(200);

}

// rumba.calibrate(2.54, 4); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
// rumba.setPos(0,0,0);
// rumba.setSpeeds(1,1); // 1ft /sec

// // if (currT - startT < 10000)
//       rumba.moveForward();
//       Serial.print(rumba.x);
//       Serial.print(" ");
//       Serial.println(rumba.y);
