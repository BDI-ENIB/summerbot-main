#include "recalibration_protocol.hpp"
#include "../../ia.hpp"
#include "../../robot.h"
#include "../../pinout.h"
#define SIMULATOR true

void RecalibrationProtocol::update(IA *ia){ //execute the next action of this protocol

  switch (state){
    case 0:
    ia->mb->translate(-ia->mb->getY()+10+ROBOT_1_W);
    break;
    case 1:
    ia->mb->translateRPM(-10, 60);
    break;
    case 2:
    if(!digitalRead(DIST_BACK) && ia->getFlag("simulator")!=1){
      state-=2;
    }
    break;
    case 3:
    ia->mb->translate(210-ROBOT_1_W);
    break;
    case 4:
    ia->mb->rotate(PI/2);
    break;
    case 5:
    ia->mb->translate(-490+ROBOT_1_W);
    break;
    case 6:
    ia->mb->translateRPM(-10, 60);
    break;
    case 7:
    if(!digitalRead(DIST_BACK) && ia->getFlag("simulator")!=1){
      state-=2;
    }
    break;
    case 8:
    ia->mb->translate(100);
    break;
    case 9:
    ia->mb->rotate(-PI/2);
    break;
    case 10:
    ia->mb->translate(400);
    break;
    case 11:
    ia->mb->setPosition(1900-ROBOT_1_W,610,PI/2);
    break;
    default:
    //somthing bad occured
    break;
  }
  state++;
}

bool RecalibrationProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>11;
}

unsigned short int RecalibrationProtocol::getPriority(IA *ia){
  if(ia->getFlag("recalibrationNeeded")==1){
    ia->setFlag("recalibrationNeeded",0);
    return PRIORITY_HIGHEST;
  }
  return PRIORITY_NULL;
}
