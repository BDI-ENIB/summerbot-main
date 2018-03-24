#ifndef IA_H
#define IA_H 1

#include "arduino.h"
#include "src/summerbot-motionbase/motionbase.hpp"
#include "src/summerbot-claw/claw.hpp"

class IA{
	public:
		IA();
		void update();
	
	private:
		Command[50] protocol;
		MotionBase *mb;
		Pince *claw;
		int protocolLenght = 0;;
		enum CommandType{forward, rotate, moveTo, load, unload, stack, buldozer};
		typedef struct Command {CommandType commandtype; double[3] args};
}
#endif
