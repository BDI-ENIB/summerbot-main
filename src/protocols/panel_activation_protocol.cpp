#include "panel_activation_protocol.hpp"
#include "../../robot.h"
#include "../../ia.hpp"
#include "../../nodes.hpp"
#include <Arduino.h>

void PanelActivationProtocol::update(IA *ia){ //execute the next action of this protocol
  switch(state){
    case 0:
    ia->mb->moveTo(g_roadButton.getX(), g_roadButton.getY(ia->getFlag("side")),0);
    Serial.println("LOG Starting_PanelActivationProtocol");
    break;
    case 1:
    ia->mb->translate(-340);
    Serial.println("LOG going_to_the_button");
    break;
    case 2:
    ia->mb->translateRPM(-20,60);
    Serial.println("LOG smashing_the_button");
    break;
    case 3:
    ia->mb->moveTo(g_roadButton.getX(), g_roadButton.getY(ia->getFlag("side")));
    Serial.println("LOG backing_away");
    break;
    default:
    // Anomality
    break;
  }
  state++;
}

bool PanelActivationProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
    return state>3;
}

unsigned short int PanelActivationProtocol::getPriority(IA *ia){
  return priority;
}
