#ifndef __MAP__
#define __MAP__

#include<random>

#define MAX_WIDTH 20
#define MAX_HEIGHT 20
#define NUM_OBSTACLE 100

class Map {
    private:
        int** map;
	public:
		void setMap();
        int** getMap();
        void printMap();
};

#endif