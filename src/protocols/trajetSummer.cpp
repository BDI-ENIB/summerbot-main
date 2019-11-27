/*      trajet du Summer:
aller chercher les palets devant lui /zone de chaos
	 -avancer de 550 mm
	  -tourner à -90° pour être face à la zone de chaos
	   -avancer de 150/170 mm
	    -reculer de 150/170 mm
	     -tourner de 90° de façon à ce que le robot se retrouve face au tableau
	      -reculer de 150 /170 mm
	       -tourner de 90° pour que le robot soit face à l’expérience
	        -reculer (distance à définir)
	         -tourner de 90° pour que le robot soit face à la case bleue
les ramener dans la case bleue (en prenant au passage celui devant la case bleue)
	  -avancer jusqu’à la case bleue

    */


#include "trajetSummer.h"
#include <Arduino.h>// fonctions de base Arduino
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"

void TrajetSummer::update(IA *ia){ //execute the next action of this protocol
  
  switch(state){
    case 0:
    if(initialPlacement == true){//330,750
      ia->mb->moveTo(750,880);//tout droit jusqu'au milieu
    }
    break;
    case 1:
    ia->mb->translate(-100);//reculer
    break;
    case 2:
    ia->mb->moveTo(450,1000);
    break;
    case 3:
    ia->mb->moveTo(930,1000);
    break;
    case 4:
    ia->mb->translate(-300);
    break;
    case 5:
    ia->mb->moveTo(1100,1400);
    break;
    case 6:
    ia->mb->moveTo(1100,350);
    break;
    default:
    // Abnormal comportment
    break;
  }
  state++;
}

boolean TrajetSummer::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>6;
}

unsigned short int TrajetSummer::getPriority(IA *ia){
  return priority;
}
