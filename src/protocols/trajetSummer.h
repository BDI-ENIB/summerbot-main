
//--------variables----------------------------
#ifndef TRAJETSUMMER
#define TRAJETSUMMER 1

#include "../../protocol.hpp"
class IA;

class TrajetSummer: public Protocol {
  public:
    TrajetSummer( unsigned short p, bool ip = true):
                 priority{p}, initialPlacement{ip} {};
    void update(IA *ia) override; //execute the next action of this protocol
    bool isCompleted() override; //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority(IA *ia) override;
    unsigned char state = 0;
    bool initialPlacement;
  private:
    unsigned short priority;

};

#endif
