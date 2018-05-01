#include <Arduino.h>
#include <Servo.h>

#include "src/protocols/cube_unloading_protocol.hpp"
#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-motionbase/MotionBase.h"
#include "src/summerbot-sensormanager/SensorManager.hpp"
#include "pinout.h"
#include "terrain.h"
#include "robot.h"
#include "ia.hpp"

#define STEPS_PER_REV 200
#define DISTANCE_THRESHOLD_MOVING_FORWARD 300 //15cm
#define DISTANCE_THRESHOLD_MOVING_BACKWARD 200 //5cm
#define MATCHLENGHT 100000 //millisec
#define SIMULATOR true

IntervalTimer motionTimer;
long startTime;
DualDRV8825* dd = new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24); // steps per rev,left dir pin, left step pin, right dir pin, right step pin, mode pin 0, mode pin 1, mode pin 2
MotionBase *mb = new MotionBase(dd, 109 / 2.0, 180 / 2.0); // motors, wheel radius, robot radius, x, y, a

Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Claw *claw;

IA *ia;

SensorManager* sensorManager;

void setup () {

  pinMode(SIDE, INPUT);
  pinMode(STARTER, INPUT_PULLUP);

  //Claw
  tmplift.attach(9);
  tmpClampL.attach(10);
  tmpClampR.attach(11);
  claw = new Claw(&tmplift, &tmpClampL, &tmpClampR);
  claw->init();

  //SensorManager
  sensorManager = new SensorManager();
  sensorManager->registerNewSensor(IRS1, SHARP);
  sensorManager->registerNewSensor(IRS2, SHARP);
  sensorManager->registerNewSensor(IRS3, SHARP);
  sensorManager->registerNewSensor(IRS4, SHARP);

  //Timer
  motionTimer.begin(motionLoop, 100); // 10kHz (100 is the period in microS)
  motionTimer.priority(1); //slightly above normal

  //Serial
  Serial.begin(250000);
  commands_init();

  //MotionBase
  mb->pause();

  //Starter
#if !SIMULATOR
  delayStarter();
#endif
#if SIMULATOR
  remoteStarter();
#endif
  startTime = millis();


  //IA
  ia = new IA(mb, claw);
  ia->addProtocol(new CubeUnloadingProtocol());
  ia->createFlag("isTheCubeLoaded", 0);
  globalSide = digitalRead(SIDE);
  ia->createFlag("side", globalSide);
  mb->setPosition(START_1_X,START_1_Y,START_1_A);
}

void delayStarter() {
  double tmp = 0;
  boolean hasStarterBeenInserted = false;
  while (true) {
    tmp = (double)(tmp * 99.0 + digitalRead(STARTER)) / 100.0;
    if (!hasStarterBeenInserted && tmp >= 0.99) {
      hasStarterBeenInserted = true;
    }
    if (hasStarterBeenInserted && tmp <= 0.01) {
      return;
    }
    delay(1);
  }
}

void loop () {
  if (millis() - startTime >= MATCHLENGHT ||
      (
        (
          sensorManager->detectObject(IRS1, DISTANCE_THRESHOLD_MOVING_FORWARD) ||
          sensorManager->detectObject(IRS2, DISTANCE_THRESHOLD_MOVING_FORWARD) ||
          sensorManager->detectObject(IRS3, DISTANCE_THRESHOLD_MOVING_BACKWARD) ||
          sensorManager->detectObject(IRS4, DISTANCE_THRESHOLD_MOVING_BACKWARD)
        )&&!SIMULATOR
      )
    ) {
    mb->pause();
    return;
  }
  commands_update();
  mb->resume();
  ia->update();
}
void motionLoop() {
  mb->update();
}
