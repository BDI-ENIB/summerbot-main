#include "ia.hpp"
#include <Arduino.h>

IA::IA(MotionBase *mb):
  protocols_{},
  protocolCount_{},
  mb{mb},
  maxFlagIndex{0} {}

IA::IA(MotionBase *mb, Protocol *protocols[], unsigned short int protocolCount):
  protocols_{},
  protocolCount_{protocolCount},
  mb{mb},
  maxFlagIndex{0} {
  for (unsigned short int i = 0; i < protocolCount; ++i) {
    protocols_[i] = protocols[i];
  }
}

void IA::addProtocol(Protocol *protocol) {
  protocols_[protocolCount_++] = protocol;
}

void IA::autoselectProtocol() {
  selectedProtocolId_=-1;
  unsigned short int maxPriority = 0;
  for (unsigned short int selectedProtocolId = 0; selectedProtocolId < protocolCount_; ++selectedProtocolId) {
    if (!protocols_[selectedProtocolId]->isCompleted()) {
      if (protocols_[selectedProtocolId]->getPriority(this) > maxPriority
            && protocols_[selectedProtocolId]->getPriority(this)>PRIORITY_NULL) {
        maxPriority = protocols_[selectedProtocolId]->getPriority(this);
        selectedProtocolId_ = selectedProtocolId;
      }
    }
  }

}

void IA::update() {
  if(!active)return;
  if (!mb->isBusy()) {
    if (selectedProtocolId_==-1||protocols_[selectedProtocolId_]->isCompleted()) {
      autoselectProtocol();
    }
    if(selectedProtocolId_!=-1)protocols_[selectedProtocolId_]->update(this);
  }
}


void IA::setFlag(String flagName, unsigned char value) {
  for (unsigned int i=0;i<=maxFlagIndex;i++) {
    if (dictionnary[i].id == flagName) {
      dictionnary[i].value = value;
      return;
    }
  }
  dictionnary[++maxFlagIndex] = {flagName, value};
}
short int IA::getFlag(String flagName) { //return an unsigned char, or -1 if not found
  for (auto entry : dictionnary) {
    if (entry.id == flagName) {
      return entry.value;
    }
  }
  return -1;
}
void IA::activate(){
  active=true;
  //Serial.println("LOG activated_AI");
}
void IA::deactivate(){
  active=false;
  //Serial.println("LOG deactivated_AI");
}
