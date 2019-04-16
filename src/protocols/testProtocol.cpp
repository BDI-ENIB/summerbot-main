#include "testProtocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include <Arduino.h>

void TestProtocol::update(IA *ia){ //execute the next action of this protocol
  switch(state){
    case 0:
    ia->mb->moveTo(500, 0);
    break;
    case 1:
    ia->mb->moveTo(500, 500);
    break;
    case 2:
    ia->mb->moveTo(0, 500);
    break;
    case 3:
    ia->mb->moveTo(0,0);
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

boolean TestProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>3;
}

unsigned short int TestProtocol::getPriority(IA *ia){
  return priority;
}
