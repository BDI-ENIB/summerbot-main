#ifndef NODES
#define NODES 1

#include "src/summerbot-pathfinder/pathfinder.h"

enum Node {
  G_RoadMain(350,610),
  G_Start(180,200),
  G_UnloadingZone1(180,500),
  G_UnloadingZone2(180,720),
  G_UnloadingZone3(180,830),
  G_Cross1(550,650),
  G_Cross2(990,300),
  G_Cross3(1500,900);
  
  
  private unsigned short int x, y;
  public getX(){
    return x;
  }
  public getY(isGreenSide){
    return isGreenSide?y:3000-y;
  }
  public Node(unsigned short int x_, unsigned short int y_): x{x_}, y{y} {}
}

Node unloadingZones[6]={G_UnloadingZone1,G_UnloadingZone2,G_UnloadingZone3};
#endif
