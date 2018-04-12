#include "ia.hpp"

IA::IA(MotionBase *mb, Claw *claw):
  protocols_{},
  protocolCount_{},
  selectedProtocolId_{},
  mb_{mb},
  claw_{claw} {}

IA::IA(MotionBase *mb, Claw *claw, Protocol *protocols[], unsigned short int protocolCount):
  protocols_{},
  protocolCount_{protocolCount},
  selectedProtocolId_{},
  mb_{mb},
  claw_{claw}  {
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
      if (protocols_[selectedProtocolId]->getPriority() > maxPriority) {
        maxPriority = protocols_[selectedProtocolId]->getPriority();
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
    protocols_[selectedProtocolId_]->update();
  }
}

