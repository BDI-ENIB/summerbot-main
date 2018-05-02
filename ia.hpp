#ifndef IA_H
#define IA_H 1

#include "src/summerbot-motionbase/MotionBase.h"
#include "src/summerbot-claw/claw.hpp"
#include "src/summerbot-screen/Screen.h"
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
    short int selectedProtocolId_=-1;
    void autoselectProtocol();
    typedef struct {
      String id;
      unsigned char value;
    } DictionnaryEntry;
    DictionnaryEntry dictionnary[MAX_FLAG_NUMBER];
    unsigned char maxFlagIndex;
    bool active = false;

  public:
    MotionBase *mb;
    Claw *claw;
    Screen *screen;

    IA(MotionBase *mb, Claw *claw, Screen *screen, Protocol *protocols[], short unsigned int protocolCount);
    IA(MotionBase *mb, Claw *claw, Screen *screen);
    void addProtocol(Protocol *protocol);
    void update();
    void setFlag(String flagName, unsigned char value);
    short int getFlag(String flagName); //return an unsigned char, or -1 if not found
    void activate();
    void deactivate();
};
#endif
