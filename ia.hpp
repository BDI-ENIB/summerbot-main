#ifndef IA_H
#define IA_H 1

#include "src/summerbot-motionbase/MotionBase.h"
#include "src/summerbot-claw/claw.hpp"
#include "protocol.hpp"

class IA {
  private:
    Protocol *protocols_[15];
    unsigned short int protocolCount_;
    unsigned short int selectedProtocolId_;
    void autoselectProtocol();
    MotionBase *mb_;
    Claw *claw_;

  public:
    IA(MotionBase *mb, Claw *claw, Protocol *protocols[], short unsigned int protocolCount);
    IA(MotionBase *mb, Claw *claw);
    void addProtocol(Protocol *protocol);
    void update();
};
#endif
