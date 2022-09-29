#include <Arduino.h>
#include "Skeleton.h"

Skeleton::Skeleton(uint8_t leftPin, uint8_t frontPin, uint8_t rightPin, uint8_t motorPin){
  _leftPin = leftPin;
  _frontPin = frontPin;
  _rightPin = rightPin;
  _motorPin = motorPin;
}

void Skeleton::initialize(){
  pinMode(_leftPin, INPUT);
  pinMode(_frontPin, INPUT);
  pinMode(_rightPin, INPUT);
  _servo.attach(_motorPin);
  _servo.write(90);
}

int Skeleton::trackMovement(){
  int sensedDirection = 0;
  if(digitalRead(_leftPin)){
    sensedDirection += 1;
  }
  if(digitalRead(_frontPin)){
    sensedDirection += 2;
  }
  if (digitalRead(_rightPin)){
    sensedDirection += 4;
  }
  return sensedDirection;
}

void Skeleton::setAngleOfInterestByDirection(int direction){
  switch(direction)
  {
    case 1:
      _angleOfInterest = 0;
      break;
    case 2:
      _angleOfInterest = 90;
      break;
    case 3:
      _angleOfInterest = 45;
      break;
    case 4:
      _angleOfInterest = 180;
      break;
    case 5:
      _angleOfInterest = 90;
      break;
    case 6:
      _angleOfInterest = 135;
      break;
    case 7:
      _angleOfInterest = 90;
      break;
    default:
      break;
  }
}

void Skeleton::moveHeadTowardAngleOfInterest(int speed){
  if(_currentAngle < _angleOfInterest)
  {
    _currentAngle += speed;
    if(_currentAngle > _angleOfInterest)
    {
      _currentAngle = _angleOfInterest;
    }
    _servo.write(_currentAngle);
  }
  else if(_currentAngle > _angleOfInterest)
  {
    _currentAngle -= speed;
    if(_currentAngle < _angleOfInterest)
    {
      _currentAngle = _angleOfInterest;
    }
    _servo.write(_currentAngle);
  }
}

void Skeleton::moveHeadInstantly(int angle){
  _currentAngle = angle;
  _servo.write(_currentAngle);
}
