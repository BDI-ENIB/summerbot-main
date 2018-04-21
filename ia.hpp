#ifndef IA_H
#define IA_H 1

#include "src/summerbot-motionbase/MotionBase.h"
#include "src/summerbot-claw/claw.hpp"
#include "protocol.hpp"

#define MAX_FLAG_NUMBER 20
#define MAX_PROTOCOL_NUMBER 15

#define PRIORITY_HIGHEST 5
#define PRIORITY_VERY_HIGH 4
#define PRIORITY_HIGH 3
#define PRIORITY_MEDIUM 2
#define PRIORITY_LOW 1
#define PRIORITY_NULL 0

class IA {
  private:
    Protocol *protocols_[MAX_PROTOCOL_NUMBER];
    unsigned short int protocolCount_;
    unsigned short int selectedProtocolId_;
    void autoselectProtocol();
    MotionBase *mb_;
    Claw *claw_;
    typedef struct {
      String id;
      unsigned char value;
    } DictionnaryEntry;
    DictionnaryEntry dictionnary[MAX_FLAG_NUMBER];
    unsigned char maxFlagIndex;

  public:
    IA(MotionBase *mb, Claw *claw, Protocol *protocols[], short unsigned int protocolCount);
    IA(MotionBase *mb, Claw *claw);
    void addProtocol(Protocol *protocol);
    void update();
    void createFlag(String flagName, unsigned char value);
    short int getFlag(String flagName); //return an unsigned char, or -1 if not found
};
#endif
