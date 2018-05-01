#include "cube_unloading_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include "Arduino.h"

void CubeUnloadingProtocol::update(IA *ia){ //execute the next action of this protocol
  if(state >=7){
    unloadingZone++;
    state = 0;
  }
  if(unloadingZone>2){
    return;
  }
  switch(state){
    case 1:
    ia->mb->moveTo(g_roadMain.getX(), g_roadMain.getY(ia->getFlag("isGreenSide")), PI);
    Serial.println("LOG Starting_CubeUnloadingProtocol.");
    break;
    case 2:
    ia->mb->moveTo(unloadingZones[unloadingZone].getX(), unloadingZones[unloadingZone].getY(ia->getFlag("isGreenSide")), PI);
    Serial.println("LOG going_to_unload_zone");
    break;
    case 3:
    ia->mb->translate(ROBOT_1_W_DEPLOYED-180);
    Serial.println("LOG forward");
    break;
    case 4:
    //ia->claw->unload();
    Serial.println("LOG empty");
    break;
    case 5:
    ia->mb->translate(180-ROBOT_1_W_DEPLOYED);
    Serial.println("LOG back");
    break;
    case 6:
    ia->mb->moveTo(g_roadMain.getX(),g_roadMain.getY(ia->getFlag("isGreenSide")), 0);
    Serial.println("LOG back_to_base");
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

boolean CubeUnloadingProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return unloadingZone>2;
}

unsigned short int CubeUnloadingProtocol::getPriority(IA *ia){
  return ia->getFlag("isTheCubeLoaded")>0?PRIORITY_HIGH:0;
}
