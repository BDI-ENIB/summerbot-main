#include "cube_loading_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"

void CubeLoadingProtocol::update(IA *ia){ //execute the next action of this protocol
  if(state >=6){ // 3 states to get placed, a few states to load the cubes, 1 states to get back to ROAD
    loadingZone++;
    state = 0;
  }
  if(loadingZone>2){
    return;
  }
  switch(state){
    case 1:
    ia->mb->moveTo(unloadingZones[loadingZone].getX(), unloadingZones[loadingZone].getY(ia->getFlag("isGreenSide")), PI);
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
    case 5:
    ia->mb->moveTo(g_roadMain.getX(),g_roadMain.getY(ia->getFlag("isGreenSide")), 0);
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

boolean CubeLoadingProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return loadingZone>2;
}

unsigned short int CubeLoadingProtocol::getPriority(IA *ia){
  return ia->getFlag("isTheCubeLoaded")>0?PRIORITY_HIGH:0;
}
