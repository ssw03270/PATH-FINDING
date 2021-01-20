#include<iostream>
#include<chrono>
#include<fstream>
#include<cstring>

#include"map.hpp"

Map map[100];
int main(){
    std::ofstream writeFile;
    std::string fileNmae = "500x500";
    std::string fileType = ".csv";
    writeFile.open(fileNmae + fileType);

    
    for(int i = 0; i < 1; i++){
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        map[i].setMap();
        map[i].setWayPoint();
        if(!map[i].pathFinding()){
            i -= 1;
            continue;
        }
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        // std::cout << ms.count() << std::endl;

        writeFile << fileNmae << "," << "62500," << ms.count() << "\n";
        
    }
    
    
    
    return 0;
}
