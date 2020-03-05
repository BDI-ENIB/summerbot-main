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
    // le robot fait ~220*220
    case 0:
    if(initialPlacement == true){//330,750

    }
    break;
    case 1:
    ia->mb->translate(460);
    break;
    case 2:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 3:
    ia->mb->translate(200);
    break;
    case 4:
    ia->mb->translate(-200);
    break;
    case 5:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 6:
    ia->mb->translate(-1720);
    break;
    case 7:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 8:
    ia->mb->translateRPM(-590,10);
    break;
    case 9:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 10:
    ia->mb->translate(-810);
    break;
    case 11:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 12:
    ia->mb->translate(590);
    break;
    case 13:
    ia->mb->translate(-590);
    break;
    case 14:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 15:
    ia->mb->translate(-560);
    break;
    case 16:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 17:
    ia->mb->translate(590);
    break;
    case 18:
    ia->mb->translate(-590);
    break;
    case 19:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;





    default:
    // Abnormal comportment
    break;
  }
  state++;
}

boolean TrajetBasic::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>19;
}

unsigned short int TrajetBasic::getPriority(IA *ia){
  return priority;
}
