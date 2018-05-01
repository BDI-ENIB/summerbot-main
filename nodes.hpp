#ifndef NODES_HPP
#define NODES_HPP 1

#include "src/summerbot-pathfinder/pathfinder.h"
#include "terrain.h"
#include "robot.h"

class Node {
  private:
    int x, y;
  public:
    int getX(){
      return x;
    }
    int getY(bool isGreenSide){
      return isGreenSide?3000-y:y;
    }
    Node(int x, int y): x{x}, y{y} {}
};

extern Node g_roadMain;
extern Node g_start;
extern Node g_cross1;
extern Node g_cross2;
extern Node g_cross3;

extern Node unloadingZones[];
extern Node RoadCubeLoadingZone[];
extern Node RealCubeLoadingZone[];
#endif
