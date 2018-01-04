#ifndef T1_VERT_H
#define T1_VERT_H

#endif //T1_VERT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <math.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Vector_2<K> Vector_2;
typedef CGAL::Vector_3<K> Vector_3;

class Vert {

public:
    float x;
    float y;
    float z;

    Vert();
    Vert(float x, float y, float z);
    void setX(float nx){ x = nx; return;};
    void setY(float ny){ y = ny; return;};
    void setZ(float nz){ z = nz; return;};


    void Displace(Vector_3 p);

    float size();

    void Displace(Vector_3 p, float limit);


};
