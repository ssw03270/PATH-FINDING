#ifndef __POINT_H__
#define __POINT_H__

class Point {
    private:
        int costG;  // start to now
        int costH;  // now to end
        int costF;  // G + H

    public:
        Point(int _costG, int _costH, int _costF){
            costG = _costG;
            costH = _costH;
            costF = _costF;
        }
        Point(){
            costG = 0;
            costH = 0;
            costF = 0;
        }

        int getG();
        int getH();
        int getF();
};

#endif