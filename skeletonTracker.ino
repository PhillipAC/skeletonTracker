#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#include "Skeleton.h"

int speed = 1;
int waitTime = 1;
Skeleton skeleton(7, 8, 12, 2);

void setup() {
  skeleton.initialize();
  skeleton.moveHeadInstantly(90);
}

void loop() {
  int direction = skeleton.trackMovement();
  skeleton.setAngleOfInterestByDirection(direction);
  skeleton.moveHeadTowardAngleOfInterest(speed);
  delay(waitTime);
}
