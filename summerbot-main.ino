#include <Arduino.h>
#include <Servo.h>

#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-motionbase/MotionBase.h"
#include "pinout.h"
#define STEPS_PER_REV 200
IntervalTimer motionTimer;
DRV8825* right=new DRV8825(STEPS_PER_REV, R_DIR, R_STEP, M1, M2, M3);// steps per rev,dir pin, step pin, mode pin 0, mode pin 1, mode pin 2
DRV8825* left =new DRV8825(STEPS_PER_REV, R_DIR, R_STEP, M1, M2, M3);
MotionBase mb(left,right,33,63); // left motor, right motor, wheel radius, robot radius, x, y, a

void setup (){
  //Timer
  motionTimer.begin(motionLoop,1000);// 1kHz (1000 is the period in microS)
  motionTimer.priority(129); //slightly above normal
  
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
