#ifndef T1_VERT_H
#define T1_VERT_H

#endif //T1_VERT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <math.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Vector_2<K> Vector_2;

class Vert {

public:
    double x;
    double y;

    Vert();
    Vert(double x, double y);
    void setX(double nx){ x = nx; return;};
    void setY(double ny){ y = ny; return;};


    void Displace(Vector_2 p);

    double size();

    void Displace(Vector_2 p, double limit);


};
