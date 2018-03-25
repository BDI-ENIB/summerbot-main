#include <Arduino.h>
#include <Servo.h>

#include "src/summerbot-sensormanager/SensorManager.hpp"
#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-motionbase/MotionBase.h"
#include "pinout.h"

#define STEPS_PER_REV 200
#define DISTANCETHRESHOLD 300
#define MATCHLENGHT 100'000 //millisec

IntervalTimer motionTimer;
DualDRV8825* dd=new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24);// steps per rev,left dir pin, left step pin, right dir pin, right step pin, mode pin 0, mode pin 1, mode pin 2
MotionBase mb(dd,109/2,180/2.0); // motors, wheel radius, robot radius, x, y, a
SensorManager* sensorManager;
double startTime ;
bool side;

void setup (){

  pinMode(STARTER, INPUT_PULLUP);  
	pinMode(SIDE, INPUT_PULLUP);
 
  //SensorManager
  sensorManager = new SensorManager();  
  sensorManager->registerNewSensor(IRS1, SHARP);
  sensorManager->registerNewSensor(IRS2, SHARP);
  sensorManager->registerNewSensor(IRS3, SHARP);
  sensorManager->registerNewSensor(IRS4, SHARP);
  
  //Timer
  motionTimer.begin(motionLoop,100);// 10kHz (100 is the period in microS)
  motionTimer.priority(1); //slightly above normal
  
  //Serial
  Serial.begin(250000);
  delay(5000);
  Serial.println("entering starter loop");
  delayStarter();
  side = digitalRead(SIDE);
  
  //Moves
  #define ORANGE_FLIP (side?1:-1)
  Serial.println("mb.pause");
  mb.pause();
  Serial.println("mb.translate");
  mb.translate(400);
  mb.translate(-100);
  mb.rotate(3.14/2*ORANGE_FLIP);
  mb.translate(200);
  mb.rotate(3.14/2*ORANGE_FLIP);
  mb.translate(-710); //Attention: à vérifier en ligne sur les dimensions du robot.
  mb.rotate(-3.14/2*ORANGE_FLIP);
  mb.translate(-270); //Attention: épaisseur cale = 56 à prendre en compte
  
  startTime = millis();
  
}

void delayStarter(){
	double tmp = 0;
	boolean hasStarterBeenInserted = false;
	Serial.println("starter not inserted");
	while (true){
		tmp = (double)(tmp*99.0+digitalRead(STARTER))/100.0;
		if (!hasStarterBeenInserted && tmp >= 0.99){
			hasStarterBeenInserted=true;		
			Serial.println("starter inserted");
		}
		if (hasStarterBeenInserted && tmp <= 0.01){
			Serial.println("starting");
			return;
		}
		delay(1);
	}
}

void loop (){
	if(millis()>=startTime+MATCHLENGHT ||
			sensorManager->detectObject(IRS1, DISTANCETHRESHOLD) ||
			sensorManager->detectObject(IRS2, DISTANCETHRESHOLD) ||
			sensorManager->detectObject(IRS3, DISTANCETHRESHOLD) ||
			sensorManager->detectObject(IRS4, DISTANCETHRESHOLD)){
		mb.pause();
		return;
	}
	Serial.println(mb.movesString());
	mb.resume();
}
void motionLoop(){
  mb.update();
}
