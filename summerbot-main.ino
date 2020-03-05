#include <Arduino.h>
#include <Servo.h>

// Les protocoles:
#include "src/protocols/testProtocol.hpp"
#include "src/protocols/trajetBasic.h"

// Le code pour les déplacement et l'ia:
#include "src/summerbot-motionbase/MotionBase.h"
#include "ia.hpp"

// Les variables constantes pour faciliter le code
#include "pinout.h"
#include "robot.h"

#define STEPS_PER_REV 200
#define DISTANCE_THRESHOLD_MOVING_FORWARD 250 //15cm
#define DISTANCE_THRESHOLD_MOVING_BACKWARD 0 //5cm ~ 200 ~ now disabled
#define MATCHLENGHT 100000 //millisec

#define START_X 100
#define START_Y (isGreenSide?2900:100)
#define START_A (isGreenSide?-90:90)

// Préparation de la base roulante
IntervalTimer motionTimer;
long startTime;
DualDRV8825* dd; // steps per rev,left dir pin, left step pin, right dir pin, right step pin, mode pin 0, mode pin 1, mode pin 2
MotionBase *mb; // motors, wheel radius, robot radius, x, y, a

// Préparation de l'IA
IA *ia;

void setup () {
  //Serial (initialisation de l'usb, entre autre)
  Serial.begin(9600);
  delay(2000);
  Serial.println("Teensy started");


  // Un pin qu'on relie ou pas à la masse pour savoir le coté
  pinMode(SIDE, INPUT_PULLUP);
  // Le pin du starter
  pinMode(STARTER, INPUT_PULLUP);
  // Les capteurs
  pinMode(DIST_BACK_LEFT, INPUT_PULLUP);
  pinMode(DIST_BACK_RIGHT, INPUT_PULLUP);

  // On définit la position initiale du robot
  int isGreenSide = digitalRead(SIDE);

  // La motionbase
  dd = new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24);
  mb = new MotionBase(dd, 114 / 2.0, 169.5 / 2.0 ); // motors, wheel radius, robot radius
  mb->setPosition(START_X,START_Y,START_A);

  //Timers: pour les moteurs
  motionTimer.begin(motionLoop, 100); // 10kHz (100 is the period in microS)
  motionTimer.priority(1); //slightly above normal

  //AI
  ia = new IA(mb);
  // On donne les protocoles à l'IA :
  //ia->addProtocol(new TestProtocol(PRIORITY_MEDIUM));
  ia->addProtocol(new TrajetBasic(PRIORITY_MEDIUM));

  // On crée des valeurs au pif, les protocoles peuvent les utiliser pour communiquer entre eux
  ia->setFlag("isGreenSide", isGreenSide);
  ia->setFlag("towerLoaded", 0);
  ia->setFlag("cross0SuccessfullyCleared", 0);
  ia->setFlag("cross1SuccessfullyCleared", 0);
  ia->setFlag("cross2SuccessfullyCleared", 0);


  //Starter & Simulator
  Serial.println("Waiting starter...");
  delayStarter();
  Serial.println("Starting!");

  //start time
  startTime = millis();

  ia->activate();
  Serial.println("AI activated!");
}

// Detection du starter, sans faux-départs
void delayStarter() {
  double tmp = 0;
  boolean hasStarterBeenInserted = false;
  while (true) {
    tmp = (double)(tmp * 99.0 + digitalRead(STARTER)) / 100.0;
    if (!hasStarterBeenInserted && tmp >= 0.95) {
      hasStarterBeenInserted = true;
      Serial.println("Starter ready!");
    }
    if(hasStarterBeenInserted && tmp <= 0.05){
      return;
    }
    delay(1);
  }

}

bool collisionDetected(){
  //=====================================================//
  //     Insérer ici code de detection de collision      //
  //=====================================================//
  return false;
}

long collisionStart;
bool collisionPossible = false;
bool timeLimitDisplayed = false;
#define DETECTION_THRESHOLD 300 // en milliseconde
void loop () {
  /**
   * Pour éviter que des reflets qui dure 10ms ne donne des movements saccadés
   * au robot, on attends d'avoir détecté un obstacle pendant une fraction de
   * seconde avant de s'arréter
   */
  if (collisionDetected()){
    collisionPossible = true;
  }else{
    collisionPossible = false;
    collisionStart = millis();
  }
  /**
   * Si fin du match ou detection de collision
   */
  if (((millis() - startTime) >= MATCHLENGHT) ||
    (collisionPossible && (millis()-collisionStart)>DETECTION_THRESHOLD)){
    mb->pause();
    return;
  }
  mb->resume();
  ia->update();
}

// Le code executé par le timer. Fonctionnement des moteurs
void motionLoop() {
  mb->update();
}
