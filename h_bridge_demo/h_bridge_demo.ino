#include "Arduino.h"
#include "TwoWheel.h"

unsigned long currT = 0;
unsigned long startT = 0;
TwoWheel rumba;

void setup()
{
    Serial.begin(9600);
    Serial.println("Start Setup");

    rumba.init(A0, 4, 5, A1, 7, 8);
    rumba.calibrate(360, 2.05 * PI); // 3ft in 1 sec, 2.05*PI rad in 1 sec
    rumba.setSpeeds(182, 1.05*PI);
    rumba.setPos(0, 0, PI/2);

    // rumba.setPinSpeeds(100,100);

    Serial.println("Done Setup");
    delay(1000);
    startT = millis();
    // rumba.moveForward();

}

int flip = 0;
// bool flip = false;

void loop()
{
    
    // currT = millis();
    if (millis() - startT > 1000){
      startT = millis();
      flip = (flip + 1) % 8;
    }
    if (flip == 0) {
      rumba.moveForward();
    } else if (flip == 1) {
      rumba.moveStop();
    } else if (flip == 2) {
      rumba.moveRight();
    } else if (flip == 3) {
      rumba.moveStop();
    } else if (flip == 4) {
      rumba.moveLeft();
    } else if (flip == 5) {
      rumba.moveStop();
    } else if (flip == 6) {
      rumba.moveBackward();
    } else if (flip == 7) {
      rumba.moveStop();
    }

    rumba.update();
    rumba.print();
    delay(100);
    // delay(100 - ((millis() - startT) % 100));
}


// rumba.calibrate(2.54, 4); // moved 2.54 ft in 1 sec, 4 rads in 1 sec
// rumba.setPos(0,0,0);
// rumba.setSpeeds(1,1); // 1ft /sec

// // if (currT - startT < 10000)
//       rumba.moveForward();
//       Serial.print(rumba.x);
//       Serial.print(" ");
//       Serial.println(rumba.y);
