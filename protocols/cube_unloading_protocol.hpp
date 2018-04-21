#ifndef PANEL_PROTOCOL
#define PANEL_PROTOCOL 1

#include "nodes.hpp"
#include "src/summerbot-motionbase/MotionBase.h"
class IA;

class CubeUnloadingProtocol: public Protocol {
  public:
    void update(IA *ia); //execute the next action of this protocol
    boolean isCompleted(); //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority(IA *ia);
  private:
    unsigned char unloadingZone = 0;
    unsigned char state = 0;
}

#endif
