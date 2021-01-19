#include<iostream>
#include<chrono>
#include<fstream>
#include<cstring>

#include"map.hpp"

using namespace std;
using namespace chrono;
int main(){
    Map map[100];
    ofstream writeFile;
    string fileNmae = "100x100";
    string fileType = ".csv";
    writeFile.open(fileNmae + fileType);

    
    for(int i = 0; i < 100; i++){
        system_clock::time_point start = system_clock::now();  
        map[i].setMap();
        map[i].setWayPoint();
        if(!map[i].pathFinding()){
            i -= 1;
            continue;
        }
        system_clock::time_point end = system_clock::now();
        milliseconds ms = duration_cast<milliseconds>(end - start);  

        cout << ms.count() << endl;

        writeFile << fileNmae << "," << "2500," << ms.count() << "\n";
        
    }
    
    
    
    return 0;
}
