#ifndef __MAP_H__
#define __MAP_H__

#include<random>
#include<queue>
#include"point.hpp"

#define MAX_WIDTH 20
#define MAX_HEIGHT 20
#define NUM_OBSTACLE 100

class Map {
    private:
        int** map;
        int startX, startY;
        int endX, endY;

        Point** openList[50][50];
        Point** closedList[50][50];
        std::queue<Point> q;    // NEED TO FIX
        
	public:
		void setMap();
        int** getMap();
        void printMap();
        void setWayPoint();
};


#endif