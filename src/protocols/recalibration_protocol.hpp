#ifndef RECALL_PROTOCOL
#define RECALL_PROTOCOL 1

#include "../../protocol.hpp"
class IA;

class RecalibrationProtocol: public Protocol {
  public:
    void update(IA *ia) override; //execute the next action of this protocol
    bool isCompleted() override; //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority(IA *ia) override;
  private:
    unsigned short int priority = 0;
};

#endif
