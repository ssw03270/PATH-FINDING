#include<iostream>
#include<cstdio>
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
		closedList2[i][0] = true;
		closedList2[i][MAX_HEIGHT - 1] = true;
	}
	for(int i = 0; i < MAX_HEIGHT; i++){
		map[0][i] = 1;
		map[MAX_WIDTH - 1][i] = 1;
		closedList2[0][i] = true;
		closedList2[MAX_WIDTH - 1][i] = true;
	}

	// set obstacle
	for(int i = 0; i < NUM_OBSTACLE; i++){
		int randX = randomNum(1, MAX_WIDTH - 2);
		int randY = randomNum(1, MAX_HEIGHT - 2);
		
		map[randX][randY] = 1;
		closedList2[randX][randY] = true;
	}
	
}

int** Map::getMap(){
	return map;
}

void Map::printMap(){
	for(int i = 0; i < MAX_WIDTH; i++){
		for(int j = 0; j < MAX_HEIGHT; j++){
			printf("%3d",visualizedMap[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	for(int i = 0; i < MAX_WIDTH; i++){
		for(int j = 0; j < MAX_HEIGHT; j++){
			printf("%3d",map[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void Map::setWayPoint(){
	startX = randomNum(1, MAX_WIDTH - 2);
	startY = randomNum(1, MAX_HEIGHT - 2);

	while(map[startX][startY] == 1){
		startX = randomNum(1, MAX_WIDTH - 2);
		startY = randomNum(1, MAX_HEIGHT - 2);
	}

	endX = randomNum(1, MAX_WIDTH - 2);
	endY = randomNum(1, MAX_HEIGHT - 2);

	while(map[endX][endY] == 1){
		endX = randomNum(1, MAX_WIDTH - 2);
		endY = randomNum(1, MAX_HEIGHT - 2);
	}
}

void Map::pathFinding(){

	std::cout << startX << ":" << startY << std::endl;
	std::cout << endX << ":" << endY << std::endl;

	int dist = (abs(startX - endX) + abs(startY - endY)) * 10;
	Point* startPoint = new Point(0, dist, dist);
	v.push_back(std::make_tuple(startPoint, startX, startY));
	openList[startX][startY] = startPoint;
	openList2[startX][startY] = true;

	num = 1;

	while(!v.empty()){
		int frontX = std::get<1>(v.front());
		int frontY = std::get<2>(v.front());

		visualizedMap[frontX][frontY] = num++;
		
		
		if(frontX == endX && frontY == endY){
			printMap();
			return;
		}

		closedList[frontX][frontY] = openList[frontX][frontY];
		closedList2[frontX][frontY] = true;
		
		v.erase(v.begin());

		findNearPoint(frontX, frontY);

		std::sort(v.begin(), v.end(), compare);
		
		
	}

}

void Map::findNearPoint(int x, int y){
	int dirX[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
	int dirY[8] = {0, -1, 0, 1, -1, 1, -1, 1};
	for(int i = 0; i < 8; i++){
		int nextX = x + dirX[i];
		int nextY = y + dirY[i];
		// can move point
		if(!closedList2[nextX][nextY]){
			int dist = (abs(nextX - endX) + abs(nextY - endY)) * 10;
			// new point
			if(!openList2[nextX][nextY]){
				if(i < 4){
					Point* nextPoint = new Point(closedList[x][y] -> getG() + 10, dist, closedList[x][y] -> getG() + 10 + dist);
					openList[nextX][nextY] = nextPoint;
					openList2[nextX][nextY] = true;
					v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY));
				}else{
					Point* nextPoint = new Point(closedList[x][y] -> getG() + 14, dist, closedList[x][y] -> getG() + 14 + dist);
					openList[nextX][nextY] = nextPoint;
					openList2[nextX][nextY] = true;
					v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY));
				}
			}
			// old point
			else{
				if(i < 4){
					if(openList[nextX][nextY] -> getF() > closedList[x][y] ->getF() + 10){
						Point* nextPoint = new Point(closedList[x][y] -> getG() + 10, dist, closedList[x][y] -> getG() + 10 + dist);
						openList[nextX][nextY] = nextPoint;
						openList2[nextX][nextY] = true;
						v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY));
					}
				}else{
					if(openList[nextX][nextY] -> getF() > closedList[x][y] -> getF() + 14){
						Point* nextPoint = new Point(closedList[x][y] -> getG() + 14, dist, closedList[x][y] -> getG() + 14 + dist);
						openList[nextX][nextY] = nextPoint;
						openList2[nextX][nextY] = true;
						v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY));
					}
				}
			}
		}

	}
}

int Map::randomNum(int minNum, int maxNum){
	std::random_device rn;
    std::mt19937_64 rnd( rn() );
 
    //< 2단계. 분포 설정 ( 정수 )
    std::uniform_int_distribution<int> range(minNum, maxNum);
 
    //< 3단계. 값 추출
    return range( rnd );
}