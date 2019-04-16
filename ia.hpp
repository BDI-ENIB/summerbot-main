#ifndef IA_H
#define IA_H 1

#include "src/summerbot-motionbase/MotionBase.h"
#include "protocol.hpp"

#define MAX_FLAG_NUMBER 20
#define MAX_PROTOCOL_NUMBER 15

#define PRIORITY_HIGHEST 6
#define PRIORITY_VERY_HIGH 5
#define PRIORITY_HIGH 4
#define PRIORITY_MEDIUM 3
#define PRIORITY_LOW 2
#define PRIORITY_VERY_LOW 1
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

    IA(MotionBase *mb,Protocol *protocols[], short unsigned int protocolCount);
    IA(MotionBase *mb);
    void addProtocol(Protocol *protocol);
    void update();
    void setFlag(String flagName, unsigned char value);
    short int getFlag(String flagName); //return an unsigned char, or -1 if not found
    void activate();
    void deactivate();
};
#endif
