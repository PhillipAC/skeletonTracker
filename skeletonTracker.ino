#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#include "Pins.h"
#include "MotorStates.h"
#include "SensedPositions.h"

int currentState = Front;
int movements[] = {Front, Left, Front, Right};
int position = 0;
int direction = true;
Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_Left, INPUT);
  pinMode(PIR_Front, INPUT);
  pinMode(PIR_Right, INPUT);
  servo.attach(Motor);
  servo.write(Front);
}

void loop() {
  int checkedState = 90;
  //sendMessage("Checking...");
  checkedState = checkSensors();
  //checkedState = autoMove();
  //checkedState = rotateMove();
  //checkedState = manualMove();
  //sendMessage(String(checkedState));
  moveMotor(checkedState);
  delay(20);
}

int checkSensors(){
  int sensedDirection = 0;
  if(digitalRead(PIR_Left)){
    sensedDirection += SensedLeft;
  }
  if(digitalRead(PIR_Front)){
    sensedDirection += SensedFront;
  }
  if (digitalRead(PIR_Right)){
    sensedDirection += SensedRight;
  }
  switch(sensedDirection)
  {
    case 0:
      return -1;
    case 1:
      return 0;
    case 2:
      return 90;
    case 3:
      return 45;
    case 4:
      return 180;
    case 5:
      return 90;
    case 6:
      return 135;
    case 7:
      return 90;
    default:
      return -1;
  }
}

int rotateMove(){
  if(direction)
  {
    currentState++;
    if(currentState > 180)
    {
      direction = !direction;
      currentState = 180;
    }
  }else{
   currentState--;
   if(currentState < 0)
   {
     direction = !direction;
     currentState = 0;
   }
  }
  return currentState;
}

int manualMove(){
  if(Serial.available() > 0)
  {
    int key = Serial.read();
    Serial.print(key);
    if(key == 97)
    {
      currentState+=10;
      if(currentState > 180)
      {
        currentState = 180;
      }
    }
    if(key == 100)
    {
      currentState-=10;
      if(currentState < 0)
      {
        currentState = 0;
      }
    }
  }
  return currentState;
}

void moveMotor(int checkedState){
  if(checkedState != -1){
    currentState = checkedState;
    servo.write(currentState);
  }
}

int autoMove(){
  position = (position + 1) % 4;
  return movements[position];
}

void sendMessage(String message)
{
  if (Serial.available())
  {
    Serial.println(message);
  }
}
