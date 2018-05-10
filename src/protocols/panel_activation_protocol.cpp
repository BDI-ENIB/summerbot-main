#include "panel_activation_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include <Arduino.h>

void PanelActivationProtocol::update(IA *ia){ //execute the next action of this protocol
  switch(state){
    case 0:
    ia->mb->moveTo(g_roadMain.getX(), g_roadMain.getY(ia->getFlag("side")),(ia->getFlag("side")?1:-1)*PI/2);
    Serial.println("LOG Starting_PanelActivationProtocol");
    break;
    case 1:
    ia->mb->moveTo(g_roadButton.getX(), g_roadButton.getY(ia->getFlag("side")),0);
    break;
    case 2:
    ia->mb->translate(ROBOT_1_W/2-g_roadButton.getX()+10);
    Serial.println("LOG going_to_the_button");
    break;
    case 3:
    ia->mb->translateRPM(-20,6);
    Serial.println("LOG smashing_the_button");
    break;
    case 4:
    ia->mb->translate(115); // Si il y a un déréglage en tapant le bouton, ça tape la croix #1
    Serial.println("LOG backing_away");
    break;
    case 5:
    ia->mb->moveTo(g_roadMain.getX(), g_roadMain.getY(ia->getFlag("side")),0);
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

bool PanelActivationProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
    return doesReposition?(state>5):(state>4);
}

unsigned short int PanelActivationProtocol::getPriority(IA *ia){
  return priority;
}
