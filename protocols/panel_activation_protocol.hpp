#ifndef PANEL_PROTOCOL
#define PANEL_PROTOCOL 1

class PanelActivationProtocol: public Protocol {
  public:
    void update(); //execute the next action of this protocol
    boolean isCompleted(); //wether the last action of this protocol have already been executed or not
    unsigned short int getPriority();
  private:
    Command[10]={{CommandType.moveTo,{roadMain}]};
}

#endif
