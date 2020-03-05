#include "testProtocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include <Arduino.h>

void TestProtocol::update(IA *ia){ //execute the next action of this protocol
  switch(state){
    case 0:
    ia->mb->translateRPM(1000,10);
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

boolean TestProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>0;
}

unsigned short int TestProtocol::getPriority(IA *ia){
  return priority;
}
