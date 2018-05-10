#include <Arduino.h>
#include <Servo.h>

#include "src/protocols/cube_unloading_protocol.hpp"
#include "src/protocols/cube_loading_protocol.hpp"
#include "src/protocols/recalibration_protocol.hpp"
#include "src/protocols/panel_activation_protocol.hpp"
#include "src/protocols/buldozer_cube_loading_protocol.hpp"
#include "src/protocols/bee_activation_protocol.hpp"
#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-motionbase/MotionBase.h"
#include "src/summerbot-screen/Screen.h"
#include "src/summerbot-screen/IconsId.h"
#include "src/summerbot-sensormanager/SensorManager.hpp"
#include "src/summerbot-bee/Bee.h"
#include "pinout.h"
#include "terrain.h"
#include "robot.h"
#include "ia.hpp"

#define STEPS_PER_REV 200
#define DISTANCE_THRESHOLD_MOVING_FORWARD 250 //15cm
#define DISTANCE_THRESHOLD_MOVING_BACKWARD 0 //5cm ~ 200 ~ now disabled
#define MATCHLENGHT 100000 //millisec
#define SIMULATOR false
#define TARGET_SCORE 42

IntervalTimer motionTimer;
long startTime;
DualDRV8825* dd = new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24); // steps per rev,left dir pin, left step pin, right dir pin, right step pin, mode pin 0, mode pin 1, mode pin 2
MotionBase *mb = new MotionBase(dd, 109 / 2.0, 180 / 2.0 +2); // motors, wheel radius, robot radius, x, y, a

Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Claw *claw;

Screen *screen;

Bee *bee;

IA *ia;

SensorManager* sensorManager;

bool forcedSide =false;
bool blocked = false;

void setup () {

  pinMode(SIDE, INPUT_PULLUP);
  pinMode(STARTER, INPUT_PULLUP);
  pinMode(DIST_BACK_LEFT, INPUT_PULLUP);
  pinMode(DIST_BACK_RIGHT, INPUT_PULLUP);

  //screen
  screen = new Screen;
  screen->showInitFrame(TARGET_SCORE);
  while(screen->isBusy()) { //waiting for the screen to update
    delay(100);
  }

  //Bee
  Servo *leftSideBeeSplasher = new Servo();
  leftSideBeeSplasher->attach(SERVO6);
  Servo *rightSideBeeSplasher = new Servo();
  rightSideBeeSplasher->write(180 - (OFFSET+RETRACTED)); // workaround
  rightSideBeeSplasher->attach(SERVO5);
  bee = new Bee(leftSideBeeSplasher, rightSideBeeSplasher, globalSide);

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

  //AI
  ia = new IA(mb, claw, screen, bee);
  ia->addProtocol(new PanelActivationProtocol(PRIORITY_HIGHEST, false));
  ia->addProtocol(new BuldozerCubeLoadingProtocol(0, PRIORITY_VERY_HIGH, true, 2));
  ia->addProtocol(new BuldozerCubeLoadingProtocol(1, PRIORITY_LOW, true, 1, false));
  ia->addProtocol(new BeeActivationProtocol(PRIORITY_MEDIUM));
  ia->setFlag("towerLoaded", 0);
  ia->setFlag("simulator", (SIMULATOR?1:0));
  ia->setFlag("recalibrationNeeded", 0);
  ia->setFlag("cross0SuccessfullyCleared", 0);
  ia->setFlag("cross1SuccessfullyCleared", 0);
  ia->setFlag("cross2SuccessfullyCleared", 0);
  ia->setFlag("ignore_IR", 0);


  //Starter & Simulator
  #if !SIMULATOR
    delayStarter();
  #endif
  #if SIMULATOR
    remoteStarter();
  #endif

  //start time
  startTime = millis();

  { // Init. hardcoded move, the AI will wait for those move to be finished before starting
    mb->pause();
    mb->translate(200);
    mb->translate(-200);
  }

  //side
  if(!forcedSide){
    globalSide = digitalRead(SIDE);
    ia->setFlag("side", globalSide);
    mb->setPosition(START_1_X,START_1_Y,START_1_A);
  }
  ia->activate();
}

void delayStarter() {
  double tmp = 0;
  boolean hasStarterBeenInserted = false;
  while (true) {
    tmp = (double)(tmp * 99.0 + digitalRead(STARTER)) / 100.0;
    if (!hasStarterBeenInserted && tmp >= 0.99) {
      hasStarterBeenInserted = true;
      screen->drawIcon(ARMED);
    }
    if (hasStarterBeenInserted && tmp <= 0.01) {
      screen->clearIcon(ARMED);
      return;
    }
    delay(1);
    commands_update();
  }

}

long IR_detect;
bool IR_blocked = false;
void loop () {
  if ((sensorManager->detectObject(IRS1, DISTANCE_THRESHOLD_MOVING_FORWARD) ||
        sensorManager->detectObject(IRS4, DISTANCE_THRESHOLD_MOVING_FORWARD) ||
        sensorManager->detectObject(IRS2, DISTANCE_THRESHOLD_MOVING_BACKWARD) ||
        sensorManager->detectObject(IRS3, DISTANCE_THRESHOLD_MOVING_BACKWARD))&&!SIMULATOR&&!ia->getFlag("ignore_IR")){
    IR_blocked = true;
  }else{
    IR_blocked = false;
    IR_detect = millis();
  }
  if (((millis() - startTime) >= MATCHLENGHT) ||
    (IR_blocked && (millis()-IR_detect)>500)){
    if(!blocked){
      mb->pause();
      Serial.println("LOG robot_blocked");
    }
    blocked=true;
    return;
  }
  commands_update();
  mb->resume();
  blocked=false;
  claw->update();
  ia->update();
}
void motionLoop() {
  mb->update();
}
