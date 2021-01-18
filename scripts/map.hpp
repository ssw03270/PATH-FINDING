#ifndef __MAP_H__
#define __MAP_H__

#include<random>
#include<vector>
#include<tuple>
#include<algorithm>
#include"point.hpp"

#define MAX_WIDTH 20
#define MAX_HEIGHT 20
#define NUM_OBSTACLE 250

class Map {
    private:
        int** map;
        int startX, startY;
        int endX, endY;

        Point* openList[20][20];
        bool openList2[20][20];
        Point* closedList[20][20];
        bool closedList2[20][20];
        int visualizedMap[20][20] = {0};
        int num;
        std::vector<std::tuple<Point*, int, int>> v;    // NEED TO FIX
        
	public:
		void setMap();
        int** getMap();
        void printMap();
        void setWayPoint();
        void pathFinding();
        void findNearPoint(int, int);
        int randomNum(int, int);
        static bool compare(const std::tuple<Point*, int,int>& a, const std::tuple<Point*, int,int>& b){
            if(std::get<0>(a) -> getF() == std::get<0>(b) -> getF()){
                return std::get<0>(a) -> getH() < std::get<0>(b) -> getH();
            }else{
                return std::get<0>(a) -> getF() < std::get<0>(b) -> getF();
            }
        }
        
};


#endif