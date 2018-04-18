#ifndef PANEL_PROTOCOL
#define PANEL_PROTOCOL 1

#class IA;

class RecalibrationProtocol: public Protocol {
  public:
    void update(IA *ia); //execute the next action of this protocol
    boolean isCompleted(); //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority(IA *ia);
  private:
    Command[10]={{CommandType.moveTo,{roadMain}]};
}

#endif
