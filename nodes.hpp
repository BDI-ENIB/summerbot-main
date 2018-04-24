#ifndef NODES
#define NODES 1

#include "src/summerbot-pathfinder/pathfinder.h"

class Node {
  private:
    int x, y;
  public:
    int getX(){
      return x;
    }
    int getY(bool isGreenSide){
      return isGreenSide?y:3000-y;
    }
    Node(int x, int y): x{x}, y{y} {}
};
Node G_RoadMain(350,610);
Node G_Start(180,200);
Node G_Cross1(550,650);
Node G_Cross2(990,300);
Node G_Cross3(1500,900);

Node unloadingZones[]={Node(180,500),Node(180,720),Node(180,830)};
#endif
