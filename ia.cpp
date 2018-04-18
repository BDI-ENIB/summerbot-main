#include "ia.hpp"

IA::IA(MotionBase *mb, Claw *claw):
  protocols_{},
  protocolCount_{},
  selectedProtocolId_{},
  mb_{mb},
  claw_{claw},
  maxFlagIndex{0} {}

IA::IA(MotionBase *mb, Claw *claw, Protocol *protocols[], unsigned short int protocolCount):
  protocols_{},
  protocolCount_{protocolCount},
  selectedProtocolId_{},
  mb_{mb},
  claw_{claw},
  maxFlagIndex{0} {
  for (unsigned short int i = 0; i < protocolCount; ++i) {
    protocols_[i] = protocols[i];
  }
}

void IA::addProtocol(Protocol *protocol) {
  protocols_[protocolCount_++] = protocol;
}

void IA::autoselectProtocol() {
  unsigned short int maxPriority = 0;
  for (unsigned short int selectedProtocolId = 0; selectedProtocolId < protocolCount_; ++selectedProtocolId) {
    if (!protocols_[selectedProtocolId]->isCompleted()) {
      if (protocols_[selectedProtocolId]->getPriority(this) > maxPriority) {
        maxPriority = protocols_[selectedProtocolId]->getPriority(this);
        selectedProtocolId_ = selectedProtocolId;
      }
    }
  }
}

void IA::update() {
  if (!mb_->isBusy() && !claw_->isBusy()) {

    if (protocols_[selectedProtocolId_]->isCompleted()) {
      autoselectProtocol();
    }
    protocols_[selectedProtocolId_]->update(this);
  }
}


void IA::createFlag(String flagName, unsigned char value) {
  dictionnary[++maxFlagIndex] = {flagName, value};
}
short int IA::getFlag(String flagName) { //return an unsigned char, or -1 if not found
#if 1

  for (auto entry : dictionnary) {
    if (entry.id == flagName) {
      return entry.value;
    }
  }

#else

  //Je surchauffe, si qqn veux faire de l'optimisation et rajouter une hashmap ça me va

#endif
  return -1;
}

