#include "cube_loading_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include <Arduino.h>

void CubeLoadingProtocol::update(IA *ia){ //execute the next action of this protocol
  switch(state){
    case 0:
    ia->mb->moveTo(RoadCubeLoadingZone[loadingZone].getX(), RoadCubeLoadingZone[loadingZone].getY(ia->getFlag("side")), PI);
    ia->setFlag("towerLoaded",1);
    Serial.println("LOG Starting_CubeLoadingProtocol_#"+loadingZone);
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

boolean CubeLoadingProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>0;
}

unsigned short int CubeLoadingProtocol::getPriority(IA *ia){
  return (ia->getFlag("towerLoaded")==0)?priority:0;
}
