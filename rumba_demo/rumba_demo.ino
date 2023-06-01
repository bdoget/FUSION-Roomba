#include "Arduino.h"
#include "TwoWheel.h"

unsigned long currT = 0;
unsigned long startT = 0;
TwoWheel rumba;


void setup() {
  Serial.begin(9600);
  Serial.println("Start Setup");

  rumba.init(3, 4, 5, 6, 7, 8);
  rumba.calibrate(12,PI); // 1ft in 1 sec, PI rad in 1 sec
  rumba.setSpeeds(12,PI);
  rumba.setPos(0,0,-PI/4);

  // rumba.setPinSpeeds(100,100);

  Serial.println("Done Setup");
  startT = millis();
  
  rumba.moveForward();
}

void loop() {
  // currT = millis();
  if (millis() - startT > 2000) {
    Serial.print(millis()-startT);
    rumba.update();
    rumba.moveStop();
    rumba.print();
    while(1) {
      delay(100000);
    }
  }
  rumba.update();
  rumba.print();
  delay(100 - ((millis()-startT) % 100));

}

/*
            o = go to 0,0
            x = go around obstacle
            f = continue path
            g = go to nearest point
            s = stop
        */


// rumba.calibrate(2.54, 4); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
// rumba.setPos(0,0,0);
// rumba.setSpeeds(1,1); // 1ft /sec

// // if (currT - startT < 10000)
//       rumba.moveForward();
//       Serial.print(rumba.x);
//       Serial.print(" ");
//       Serial.println(rumba.y);
