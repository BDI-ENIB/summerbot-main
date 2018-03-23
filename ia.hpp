#ifndef IA_H
#define IA_H 1

#include "arduino.h"
#include <vector>

class IA{
	public:
		void IA()
		void update();
	
	private:
		enum CommandType{None=0,
				Forward=1,
				Rotate=2,
				MoveTo=3,
				Load=4,
				Unload=5,
				InitClaw=6};
		typedef struct command {CommandType commandType; int[3] args};
		typedef struct protocol {string name; vector<command> commands;};
		vector<protocol> protocols;
		typedef struct objective {string name; byte priority; boolean isCompleted;};
		vector<objective> objectives;
		byte currentObjectiveIndex = 0;
		byte currentCommandIndex = 0;
		byte currentProtocolIndex = 0;
}
#endif
