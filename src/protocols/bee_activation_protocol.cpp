#include "bee_activation_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include "../../pinout.h"
#include "../summerbot-bee/Bee.h"
#include <Arduino.h>

void BeeActivationProtocol::update(IA *ia){ //execute the next action of this protocol
  Servo *servo;
  switch(state){
    case 0:
    ia->mb->moveTo(RoadCubeLoadingZone[2].getX(), RoadCubeLoadingZone[2].getY(ia->getFlag("side")), -PI/4);
    break;
    case 1:
    ia->mb->moveTo(2000-ROBOT_1_W/2-40,(ia->getFlag("side")?(ROBOT_1_W/2+40):3000-(ROBOT_1_W+30)), (ia->getFlag("side")?1:-1)*PI/2);
    Serial.println("LOG Starting_BeeSplatProtocol_(bugsplat...understood?_loool)");
    break;
    case 2:
    ia->bee->deploy();
    break;
    case 3:
    ia->mb->translate(570-ROBOT_1_W-50);
    Serial.println("LOG splating_the_bee..._hopefully_xD");
    break;
    case 4:
    ia->bee->retract();
    break;
    default:
    // Abnormal bee-havior
    break;
  }
  state++;
}

boolean BeeActivationProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>4;
}

unsigned short int BeeActivationProtocol::getPriority(IA *ia){
  return priority;
}
