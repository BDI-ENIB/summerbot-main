#include "testProtocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include <Arduino.h>

void TestProtocol::update(IA *ia){ //execute the next action of this protocol
  switch(state){
    case 0:
    ia->mb->translate(500);
    break;
    case 1:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 2:
    ia->mb->translate(500);
    break;
    case 3:
    ia->mb->rotate(PI*(ia->getFlag("side")?1:-1));
    break;
    case 4:
    ia->mb->translate(500);
    break;
    case 5:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 6:
    ia->mb->translate(500);
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

boolean TestProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>7;
}

unsigned short int TestProtocol::getPriority(IA *ia){
  return priority;
}