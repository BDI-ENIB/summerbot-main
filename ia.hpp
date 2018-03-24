#ifndef IA_H
#define IA_H 1

#include "arduino.h"
#include "src/summerbot-motionbase/motionbase.h"
#include "src/summerbot-claw/claw.hpp"

class IA{
 
  public:
    enum CommandType{forward, rotate, moveTo, load, unload, stack, buldozer};
    typedef struct {CommandType commandType; double args[3];}Command;
  private:
    Command protocol[50];
    MotionBase *mb;
    Claw *claw;
    int protocolLenght = 0;
    int currentCommandIndex = 0;
    
	public:
		IA(MotionBase *mb, Claw *claw);
    void addCommands(Command commandList[]);
    void executeCommand(CommandType command, double args[3]);
		void update();
};
#endif
