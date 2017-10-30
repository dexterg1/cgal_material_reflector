#include "../vert/vert.h"

Vert::Vert(){
    this->x=0;
    this->y=0;
}

Vert::Vert(double x, double y) {
    this->x = x;
    this->y = y;
}

void Vert::Displace(Vector_2 p) {
this->x += p.x();
this->y += p.y();
}


double Vert::size() {
    sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void Vert::Displace(Vector_2 p, double limit) {
double vectorSize = sqrt(p.squared_length());
    if(vectorSize > limit) {
        this->x += p.x() * limit / vectorSize;
        this->y += p.y() * limit / vectorSize;
    }else{
        this->x += p.x();
        this->y += p.y();
    }

}


