#include <Arduino.h>
#include <Servo.h>

#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-motionbase/MotionBase.h"
#include "pinout.h"
#define STEPS_PER_REV 200
IntervalTimer motionTimer;
DualDRV8825* dd=new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24);// steps per rev,left dir pin, left step pin, right dir pin, right step pin, mode pin 0, mode pin 1, mode pin 2
MotionBase mb(dd,33,63); // motors, wheel radius, robot radius, x, y, a
MotionBase mb(left,right,33,63); // left motor, right motor, wheel radius, robot radius, x, y, a

void setup (){
  //Timer
  motionTimer.begin(motionLoop,100);// 1kHz (100 is the period in microS)
  motionTimer.priority(1); //slightly above normal
  
  //Serial
  Serial.begin(250000);
  commands_init();
  
}

void loop (){
  commands_update();
}
void motionLoop(){
  mb.update();
}
