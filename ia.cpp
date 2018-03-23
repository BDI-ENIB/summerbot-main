#include "ia.h"
#define LEFT_SIDE true

void IA::IA(){
	protocols = {{"unloadCubes",{}},{"goToCross1",{}},{"goToCross2",{}},{"goToCross3",{}},{"loadCross",{}}}
	//TODO: Finir les différents protocoles
	
	objectives = {{"cross1", (LEFT_SIDE?5:0), false}, {"cross2", (LEFT_SIDE?4:1), false}, {"cross3", (LEFT_SIDE?3:2), false}, {"cross4", (LEFT_SIDE?2:3), false}, {"cross5", (LEFT_SIDE?1:4), false}, {"cross1", (LEFT_SIDE?0:5), false}, {"startingCube", 6, false}};
}

void updateObjectiveIndex(){
	byte maxPrio = -1;
	for(byte i = 0; i<objectives.size(); ++i){
		if(objectives[i].priority>maxPrio&&!objectives[i].isCompleted){
			currentObjectiveIndex = i;
			maxPrio = objectives[i].priority;
		}
	}
}

void IA::update(){
	//On update les actionneurs, et si ils répondent tous qu'ils ont tout fait...
	if(true){
		currentCommandIndex++;
		if(currentCommandIndex < protocols[currentProtocolIndex].size()){
			//Si nous n'avons pas terminé notre séquence d'action, on passe à la suivante
			
		}else{
			//Sinon, on update l'objectif, on en choisis un nouveau, et on conclut les protocoles à executer
			currentCommandIndex=0
			updateObjectiveIndex();
			//TODO lier les objectifs aux protocoles
		}
		updateObjectiveIndex();
	}
}

