
#include "trajetBasic.h"
#include <Arduino.h>// fonctions de base Arduino
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"

void TrajetBasic::update(IA *ia){ //execute the next action of this protocol
  switch(state){
    //exemples
    //  ia->mb->translate(-270);
    //  ia->mb->rotate(ia->getFlag("side")?(PI/2):-(PI/2));
    case 0:
    if(initialPlacement == true){//330,750

    }
    break;
    case 1:
    ia->mb->translate(-100);
    break;





    default:
    // Abnormal comportment
    break;
  }
  state++;
}

boolean TrajetBasic::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>1;
}

unsigned short int TrajetBasic::getPriority(IA *ia){
  return priority;
}
