#include<iostream>
#include<chrono>
#include<fstream>
#include<cstring>

#include"map.hpp"

int main(){
    Map map[100];
    std::ofstream writeFile;
    std::string fileNmae = "20x20";
    std::string fileType = ".csv";
    writeFile.open(fileNmae + fileType);

    
    for(int i = 0; i < 100; i++){
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

        writeFile << fileNmae << "," << "100," << ms.count() << "\n";
        
    }
    
    
    
    return 0;
}
