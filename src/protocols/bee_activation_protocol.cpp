#include "bee_activation_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include "../../pinout.h"
#include <Arduino.h>

void BeeActivationProtocol::update(IA *ia){ //execute the next action of this protocol
  Servo *servo;
  switch(state){
    case 0:
    ia->mb->moveTo(2000-ROBOT_1_W/2-30,(ia->getFlag("side")?(ROBOT_1_W+30):3000-(ROBOT_1_W+30)), (ia->getFlag("side")?1:-1)*PI/2);
    Serial.println("LOG Starting_BeeSplatProtocol_(bugsplat...understood?_loool)");
    break;
    case 1:
    if(ia->getFlag("side")){
      servo->attach(SERVO5);
    }else{
      servo->attach(SERVO6);
    }
    servo->write(servo->read()+90);
    break;
    case 2:
    ia->mb->translate(570-ROBOT_1_W/2-30);
    Serial.println("LOG splating_the_bee..._hopefully_xD");
    break;
    case 3:
    servo->write(servo->read()-90);
    break;
    default:
    // Abnormal bee-havior
    break;
  }
  state++;
}

boolean BeeActivationProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>3;
}

unsigned short int BeeActivationProtocol::getPriority(IA *ia){
  return priority;
}
