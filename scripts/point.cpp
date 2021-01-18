#include "point.hpp"

int Point::setG(int g){costG = g;}
int Point::setH(int h){costH = h;}
int Point::setF(int f){costF = f;}

int Point::getG(){return costG;}
int Point::getH(){return costH;}
int Point::getF(){return costF;}

