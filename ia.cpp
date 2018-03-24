#include "ia.hpp"
#define LEFT_SIDE true


IA::IA(MotionBase *mb, Claw *claw){
	this->mb = mb;
	this->claw = claw;
}

void IA::addCommands(Command commandList[]){
	char size = (int)sizeof(commandList)/(int)sizeof(Command);
	for(char i = 0; i<size; i++){
		protocol[i+protocolLenght]=commandList[i];
	}
}

void IA::update(){
	if(!mb->isBusy()&&!claw->isBusy()){
		if(currentCommandIndex+1>=protocolLenght){
			return;		
		}		
		currentCommandIndex++;
		executeCommand(protocol[currentCommandIndex].commandType, protocol[currentCommandIndex].args);
	}
}

void IA::executeCommand(CommandType command, double args[3]){
		// {forward, rotate, load, unload, stack}
		if(command==CommandType::forward){
			mb->translate(args[0]);
		}else if(command==CommandType::rotate){
			mb->rotate(args[0]);
		}else if(command==CommandType::moveTo){
			mb->moveTo(args[0], args[1], args[2]); //X, Y, TETA
		}else if(command==CommandType::load){
			claw->load();
		}else if(command==CommandType::unload){
			claw->unload();
		}else if(command==CommandType::stack){
			claw->stack();
		}else if(command==CommandType::buldozer){
			//claw.openWide();
		}
}

