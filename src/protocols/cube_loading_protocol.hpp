#ifndef CUBE_LOAD_PROTOCOL
#define CUBE_LOAD_PROTOCOL 1

#include "../../protocol.hpp"
class IA;

class CubeLoadingProtocol: public Protocol {
  public:
    CubeLoadingProtocol(int lz):loadingZone{lz} {};
    void update(IA *ia) override; //execute the next action of this protocol
    bool isCompleted() override; //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority(IA *ia) override;
  private:
    unsigned char loadingZone = 0;
    unsigned char state = 0;
};

#endif
