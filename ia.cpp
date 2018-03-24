#include "ia.hpp"
#define LEFT_SIDE true


IA::IA(MotionBase *mb, Pince *claw){
	protocol = commandList;
	this->mb = mb;
	this->claw = claw;
}

void IA::addCommands(Command[] commandList){
	char size = (int)sizeof(commandList)/(int)sizeof(Command);
	for(char i = 0; i<size; i++){
		protocol[i+protocolLenght]=commandList[i];
	}
}

void IA::update(){
	if(!mb.isBusy()&&!claw.isBusy()){
		if(currentCommandIndex+1>=protocolLenght){
			return;		
		}		
		currentCommandIndex++;
		executeCommand(protocol[currentCommandIndex]);
	}
}

void IA::executeCommand(Command command, double[3] args){
		// {forward, rotate, load, unload, stack}
		if(command==Command.forward){
			mb->forward(args[0]);
		}else if(command==Command.rotate){
			mb->rotate(args[0]);
		}else if(command==Command.moveTo){
			mb->moveTo(args[0], args[1], args[2]); //X, Y, TETA
		}else if(command==Command.load){
			claw->load();
		}else if(command==Command.unload){
			claw->unload();
		}else if(command==Command.stack){
			claw->stack();
		}else if(command==Command.buldozer){
			//claw.openWide();
		}
}

