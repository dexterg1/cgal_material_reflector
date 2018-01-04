#include "../vert/vert.h"

Vert::Vert(){
    this->x=0;
    this->y=0;
    this->z=0;
}

Vert::Vert(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vert::Displace(Vector_3 p) {
this->x += p.x();
this->y += p.y();
this->z += p.z();
}


float Vert::size() {
    sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

void Vert::Displace(Vector_3 p, float limit) {
    float vectorSize = sqrt(p.squared_length());
    if(vectorSize > limit) {
        this->x += p.x() * limit / vectorSize;
        this->y += p.y() * limit / vectorSize;
        this->z += p.z() * limit / vectorSize;
    }else{
        this->x += p.x();
        this->y += p.y();
        this->z += p.z();
    }

}


