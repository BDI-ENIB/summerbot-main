#ifndef CUBE_BULDOZER_LOADING_PROTOCOL
#define CUBE_BULDOZER_LOADING_PROTOCOL 1

#include "../../protocol.hpp"
class IA;

class BuldozerCubeLoadingProtocol: public Protocol {
  public:
    BuldozerCubeLoadingProtocol(unsigned char lz,unsigned short p):loadingZone{lz}, priority{p}{};
    void update(IA *ia) override; //execute the next action of this protocol
    bool isCompleted() override; //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority(IA *ia) override;
  private:
    unsigned char loadingZone;
    unsigned char state = 0;
    unsigned short priority;
};

#endif
