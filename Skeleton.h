#ifndef Skeleton_h
#define Skeleton_h
#include <Arduino.h>
#include <Servo.h>

class Skeleton {

  private:
    int _leftPin;
    int _frontPin;
    int _rightPin;
    int _motorPin;
    Servo _servo;
    
    int _angleOfInterest;
    int _currentAngle;
    
  public:
    Skeleton(uint8_t leftPin, uint8_t frontPin, uint8_t rightPin, uint8_t motorPin);

    void initialize();
    int trackMovement();
    void setAngleOfInterestByDirection(int direction);
    void moveHeadTowardAngleOfInterest(int speed);
    void moveHeadInstantly(int angle);

};

#endif
