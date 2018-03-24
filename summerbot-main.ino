#include <Arduino.h>
#include <Servo.h>

#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-motionbase/MotionBase.h"
#include "pinout.h"
#include "terrain.h"
#include "robot.h"

#define STEPS_PER_REV 200
#define DISTANCE_THRESHOLD_MOVING_FORWARD 150 //15cm
#define DISTANCE_THRESHOLD_MOVING_BACKWARD 50 //5cm
#define MATCHLENGHT 100'000 //millisec

IntervalTimer motionTimer;
DualDRV8825* dd=new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24);// steps per rev,left dir pin, left step pin, right dir pin, right step pin, mode pin 0, mode pin 1, mode pin 2
MotionBase *mb(dd,33,63); // motors, wheel radius, robot radius, x, y, a

Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Claw *claw;

IA ia(mb, claw);
double startTime;

SensorManager* sensorManager;

void setup (){
	
	pinMode(SIDE, INPUT);
	pinMode(STARTER, INPUT_PULLUP);  
	
	//Claw
	tmplift.attach(9);
	tmpClampL.attach(10);
	tmpClampR.attach(11);
	claw = new Claw(&tmplift,220,&tmpClampL,&tmpClampR,220);
	
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
	commands_init();
	
	//Entering Starter Loop
	delayStarter();
	
	//Moves
	//Rappel: CommandType{forward, rotate, moveTo, load, unload, stack}
	mb->pause();
	boolean isRightSide = digitalRead(SIDE); //Bouton SIDE: Si activé, robot coté droit
	if(!isRightSide){ //Coté gauche
		#define IRS ((!isRightSide)?1:-1)*
		ia.addCommands({
			{CommandType.forward,{400.0}},
			{CommandType.forward,{-100.0}},
			{CommandType.rotate,{IRS 3.14159265/2}},
			{CommandType.forward,{145.0}},
			{CommandType.rotate,{IRS 3.14159265/2}},
			{CommandType.forward,{-730.0}},
			{CommandType.rotate,{IRS -3.14159265/2}},
			{CommandType.forward,{-260.0}},
			{CommandType.forward,{640}},
			{CommandType.rotate,{IRS 3.14159265/2}},
			{CommandType.forward,{280}},
			{CommandType.rotate,{IRS 3.14159265/2}},
			{CommandType.buldozer,{}}
			{CommandType.forward,{582}}
		});
	}
}

void delayStarter(){
	double tmp = 0;
	boolean hasStarterBeenInserted = false;
	while (true){
		tmp = (double)(tmp*99.0+digitalRead(STARTER))/100.0;
		if (!hasStarterBeenInserted && tmp >= 0.99){
			hasStarterBeenInserted=true;		
		}
		if (hasStarterBeenInserted && tmp <= 0.01){
			return;
		}
		delay(1);
	}
}

void loop (){
	if(++timer>=STOPTIME||
			sensorManager->detectObject(IRS1, DISTANCE_THRESHOLD_MOVING_BACKWARD) ||
			sensorManager->detectObject(IRS2, DISTANCETHRESHOLD_MOVING_BACKWARD) ||
			sensorManager->detectObject(IRS3, DISTANCETHRESHOLD_MOVING_FORWARD) ||
			sensorManager->detectObject(IRS4, DISTANCETHRESHOLD_MOVING_FORWARD)){
		mb->pause();
		return;
	}
	commands_update();
	mb->resume();
	ia.update();
}
void motionLoop(){
	mb->update();
}
