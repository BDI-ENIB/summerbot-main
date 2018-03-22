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
MotionBase mb(dd,33,63); // motors, wheel radius, robot radius, x, y, a
SensorManager* sensorManager;
double startTime ;

void setup (){
  //SensorManager
  sensorManager = new SensorManager();  
  sensorManager->registerNewSensor(IRS1, SHARP);
  sensorManager->registerNewSensor(IRS2, SHARP);
  sensorManager->registerNewSensor(IRS3, SHARP);
  sensorManager->registerNewSensor(IRS4, SHARP);
  sensorManager->registerNewSensor(IRS5, SHARP);
  sensorManager->registerNewSensor(IRS6, SHARP);
  sensorManager->registerNewSensor(IRS7, SHARP);
  sensorManager->registerNewSensor(IRS8, SHARP);
  
  //Timer
  motionTimer.begin(motionLoop,100);// 10kHz (100 is the period in microS)
  motionTimer.priority(1); //slightly above normal
  
  //Serial
  Serial.begin(250000);
  delay(5000);

  //Moves

  Serial.println("mb.pause");
  mb.pause();
  Serial.println("mb.translate");
  mb.translate(400);
  mb.translate(-100);
  Serial.println("entering starter loop");
  delayStarter();
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
			sensorManager->detectObject(IRS4, DISTANCETHRESHOLD) ||
			sensorManager->detectObject(IRS5, DISTANCETHRESHOLD) ||
			sensorManager->detectObject(IRS6, DISTANCETHRESHOLD) ||
			sensorManager->detectObject(IRS7, DISTANCETHRESHOLD) ||
			sensorManager->detectObject(IRS8, DISTANCETHRESHOLD)){
		mb.pause();
		return;
	}
	Serial.println("mb.resume()");
	mb.resume();
}
void motionLoop(){
  mb.update();
}
