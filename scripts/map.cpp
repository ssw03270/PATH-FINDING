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
	std::cout << "this is a random map design" << std::endl;

	for(int i = 0; i < MAX_WIDTH; i++){
		for(int j = 0; j < MAX_HEIGHT; j++){
			switch(map[i][j]){
				case 0:
				std::cout << "□   ";
				break;
				case 1:
				std::cout << "■   ";
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "this is a player movement" << std::endl;

	for(int i = 0; i < MAX_WIDTH; i++){
		for(int j = 0; j < MAX_HEIGHT; j++){
			if(i == endX && j == endY){
				std::cout << "★   ";
			}else if(i == startX && j == startY){
				std::cout << "☆   ";
			}else if(visualizedMap[i][j] == 9999){
				std::cout << "◎   ";
			}else if(map[i][j] == 1){
				std::cout << "■   ";
			}else if(map[i][j] == 0){
				std::cout << "□   ";
			}else if(visualizedMap[i][j] == 0){
				std::cout << "■   ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Map::printPath(int lastX, int lastY){
	int needX = lastX;
	int needY = lastY;
	while(!s.empty()){
		if(needX == 9999 && needY == 9999){
			break;
		}
		if(std::get<0>(s.top()) == needX && std::get<1>(s.top()) == needY){
			realPath.push_back(std::pair<int, int>(needX, needY));
			needX = std::get<2>(s.top());
			needY = std::get<3>(s.top());
			s.pop();
		}else{
			s.pop();
		}
	}
	for(int i = 0; i < realPath.size(); i++){
		std::cout << realPath[i].first << ":" << realPath[i].second << std::endl;
		visualizedMap[realPath[i].first][realPath[i].second] = 9999;
	}
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

	std::cout << "start point is " << startX << ":" << startY << std::endl;
	std::cout << "end point is " << endX << ":" << endY << std::endl;

	int dist = (abs(startX - endX) + abs(startY - endY)) * 10;
	Point* startPoint = new Point(0, dist, dist);
	v.push_back(std::make_tuple(startPoint, startX, startY, 9999, 9999));
	s.push(std::make_tuple(startX, startY, 9999, 9999));
	openList[startX][startY] = startPoint;
	openList2[startX][startY] = true;

	while(!v.empty()){
		int frontX = std::get<1>(v.front());
		int frontY = std::get<2>(v.front());
		
		if(frontX == endX && frontY == endY){
			printPath(endX, endY);
			printMap();
			return;
		}

		closedList[frontX][frontY] = openList[frontX][frontY];
		closedList2[frontX][frontY] = true;
		
		v.erase(v.begin());

		findNearPoint(frontX, frontY);

		std::sort(v.begin(), v.end(), compare);
		
		
	}
	std::cout << "there is no path. plz reload program" << std::endl;

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
					v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY, x, y));
					s.push(std::make_tuple(nextX, nextY, x, y));
				}else{
					Point* nextPoint = new Point(closedList[x][y] -> getG() + 14, dist, closedList[x][y] -> getG() + 14 + dist);
					openList[nextX][nextY] = nextPoint;
					openList2[nextX][nextY] = true;
					v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY, x, y));
					s.push(std::make_tuple(nextX, nextY, x, y));
				}
			}
			// old point
			else{
				if(i < 4){
					if(openList[nextX][nextY] -> getF() > closedList[x][y] ->getF() + 10){
						Point* nextPoint = new Point(closedList[x][y] -> getG() + 10, dist, closedList[x][y] -> getG() + 10 + dist);
						openList[nextX][nextY] = nextPoint;
						openList2[nextX][nextY] = true;
						v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY, x, y));
						s.push(std::make_tuple(nextX, nextY, x, y));
					}
				}else{
					if(openList[nextX][nextY] -> getF() > closedList[x][y] -> getF() + 14){
						Point* nextPoint = new Point(closedList[x][y] -> getG() + 14, dist, closedList[x][y] -> getG() + 14 + dist);
						openList[nextX][nextY] = nextPoint;
						openList2[nextX][nextY] = true;
						v.push_back(std::make_tuple(openList[nextX][nextY], nextX, nextY, x, y));
						s.push(std::make_tuple(nextX, nextY, x, y));
					}
				}
			}
		}

	}
}

int Map::randomNum(int minNum, int maxNum){
	std::random_device rn;
    std::mt19937_64 rnd( rn() );
 
    std::uniform_int_distribution<int> range(minNum, maxNum);
 
    return range( rnd );
}