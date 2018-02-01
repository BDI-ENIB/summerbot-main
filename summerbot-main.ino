#include <Arduino.h>
#include <Servo.h>

#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-motionbase/Motion_base.hpp"
#include "pinout.h"
Motion_base motion_base(
  R_STEP,
  R_DIR,
  L_STEP,
  L_DIR,
  M1,
  M2,
  M3,
  0,
  0,
  0
);
void setup (){
  motion_base.moveStraight(50); //forward 20mm
  delay(10000); //let the base finish the movement
  motion_base.rotate(M_PI*2); //full turn
  delay(10000);
  motion_base.moveStraight(-50); //backward 20mm
  delay(10000);
  
}

void loop (){
}

