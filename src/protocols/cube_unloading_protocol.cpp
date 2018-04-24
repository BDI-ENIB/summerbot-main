#include "cube_unloading_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"

void CubeUnloadingProtocol::update(IA *ia){ //execute the next action of this protocol
  if(state >=5||unloadingZone>2){
    unloadingZone++;
    state = 0;
    return;
  }
  switch(state){
    case 1:
    ia->mb->moveTo(unloadingZones[unloadingZone].getX(), unloadingZones[unloadingZone].getY(ia->getFlag("isGreenSide")), PI);
    break;
    case 2:
    ia->mb->translate(180-ROBOT_1_W_DEPLOYED);
    break;
    case 3:
    ia->claw->unload();
    break;
    case 4:
    ia->mb->translate(ROBOT_1_W_DEPLOYED-180);
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
