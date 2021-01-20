#include<iostream>
#include<chrono>
#include<cstring>
#include<fstream>
#include"../Includes/map.hpp"

Map map[100];
int main(){
    std::ofstream writeFile;
    std::string fileNmae = "500x500";
    std::string fileType = ".csv";
    writeFile.open(fileNmae + fileType);

    
    for(int i = 0; i < 100; i++){
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        map[i].setMap();
        map[i].setWayPoint();
        if(!map[i].pathFinding()){
            std::cout << "no path" << std::endl;
            i -= 1;
        }else{
            std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
            std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            std::cout << ms.count() << std::endl;

            writeFile << fileNmae << "," << "25000," << ms.count() << "\n";
        }
        
        
    }
    
    
    
    return 0;
}
