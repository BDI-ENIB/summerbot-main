#include "panel_activation_protocol.hpp"
#include "../../ia.hpp"

void PanelActivationProtocol::update(IA *ia){ //execute the next action of this protocol

}

boolean PanelActivationProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not
    return true;
}

unsigned short int PanelActivationProtocol::getPriority(IA *ia){
  return priority;
}
