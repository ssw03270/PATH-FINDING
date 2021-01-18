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

        int setG(int g);
        int setH(int h);
        int setF(int f);

        int getG();
        int getH();
        int getF();
};

#endif