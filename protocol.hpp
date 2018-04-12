#ifndef PROTOCOL_H
#define PROTOCOL_H 1
class Protocol {
  public:
    virtual void update() = 0; //execute the next action of this protocol
    virtual boolean isCompleted() = 0; //wether the last action of this protocol have already been executed or not
    virtual unsigned short int getPriority();
  private:
    enum CommandType {forward, rotate, moveTo, load, unload, stack, buldozer, recalibrateMovingBackward};
    typedef struct {
      CommandType commandType;
      double args[3];
    } Command;
};
#endif
