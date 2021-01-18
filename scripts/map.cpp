#include<iostream>
#include "map.hpp"


void Map::setMap(){
	// make foundation of map
	map = new int*[MAX_WIDTH];
	for(int i = 0; i < MAX_WIDTH; i++){
		map[i] = new int[MAX_HEIGHT];
	}

	// set border line
	for(int i = 0; i < MAX_WIDTH; i++){
		map[i][0] = 1;
		map[i][MAX_HEIGHT - 1] = 1;
	}
	for(int i = 0; i < MAX_HEIGHT; i++){
		map[0][i] = 1;
		map[MAX_WIDTH - 1][i] = 1;
	}

	// set obstacle
	for(int i = 0; i < NUM_OBSTACLE; i++){
		int randX = rand() % (MAX_WIDTH - 1) + 1;
		int randY = rand() % (MAX_HEIGHT - 1) + 1;
		
		map[randX][randY] = 1;
	}
}

int** Map::getMap(){
	return map;
}

void Map::printMap(){
	for(int i = 0; i < MAX_WIDTH; i++){
        for(int j = 0; j < MAX_HEIGHT; j++){
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
