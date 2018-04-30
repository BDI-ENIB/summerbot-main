#include "recalibration_protocol.hpp"
#include "../../ia.hpp"

void RecalibrationProtocol::update(IA *ia){ //execute the next action of this protocol

}

bool RecalibrationProtocol::isCompleted(){ //wether the last action of this protocol have already been executed or not

}

unsigned short int RecalibrationProtocol::getPriority(IA *ia){
  return priority;
}
