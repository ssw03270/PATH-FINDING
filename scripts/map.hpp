#ifndef __MAP_H__
#define __MAP_H__

#include<random>
#include<vector>
#include<stack>
#include<tuple>
#include<algorithm>
#include"point.hpp"

#define MAX_WIDTH 500
#define MAX_HEIGHT 500
#define NUM_OBSTACLE 62500    // size * size / 4

class Map {
    private:
        int startX, startY;
        int endX, endY;
        int map[MAX_WIDTH][MAX_HEIGHT] = {0};
        Point* openList[MAX_WIDTH][MAX_HEIGHT];
        bool openList2[MAX_WIDTH][MAX_HEIGHT];
        Point* closedList[MAX_WIDTH][MAX_HEIGHT];
        bool closedList2[MAX_WIDTH][MAX_HEIGHT];
        bool notRenewal[MAX_WIDTH][MAX_HEIGHT];
        int visualizedMap[MAX_WIDTH][MAX_HEIGHT] = {0};
        std::stack<std::tuple<int, int, int, int>> s;             // current, pre
        std::vector<std::tuple<Point*, int, int, int, int>> v;    // NEED TO FIX
        std::vector<std::pair<int, int>> realPath;
        
	public:
		void setMap();
        void printMap();
        void printPath(int, int);
        void setWayPoint();
        bool pathFinding();
        void findNearPoint(int, int);
        int randomNum(int, int);
        static bool compare(const std::tuple<Point*, int, int, int, int>& a, const std::tuple<Point*, int, int, int, int>& b){
            if(std::get<0>(a) -> getF() == std::get<0>(b) -> getF()){
                return std::get<0>(a) -> getH() < std::get<0>(b) -> getH();
            }else{
                return std::get<0>(a) -> getF() < std::get<0>(b) -> getF();
            }
        }
        
};


#endif