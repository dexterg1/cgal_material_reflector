#include <iostream>


#include <OpenGL/gl.h>
#include <GLUT/glut.h>


#include "vert/vert.h"

#include "mesh/mesh.h"

#include <math.h>

//#include <CGAL/Simple_cartesian.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_mesher_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>
#include <CGAL/Delaunay_mesh_size_criteria_2.h>

#include <CGAL/Aff_transformation_2.h>

#include <typeinfo>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_with_info_2<Vert, K> Vb;
typedef CGAL::Vector_2<K> v2;
typedef CGAL::Point_2<K> Point_2;
typedef CGAL::Delaunay_mesh_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, Tds> CDT;
typedef CGAL::Delaunay_mesh_size_criteria_2<CDT> Criteria;
typedef CDT::Vertex_handle Vertex_handle;
typedef CDT::Point Point;

typedef CGAL::Aff_transformation_2<K> Transformation;

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(.005,.005,.005);
    glRotatef(20, 0, 1, 0);
    glRotatef(30, 0, 0, 1);
    glRotatef(5, 1, 0, 0);
    glTranslatef(-300, 0, 0);

    glColor3f(1,1,1);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'P');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'I');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');

    glutSwapBuffers();
} /* end func displayCall */

int main(int argc, char *argv[]) {

    CDT cdt;
    Vertex_handle va = cdt.insert(Point(-4,0));
    Vertex_handle vb = cdt.insert(Point(0,-1));
    Vertex_handle vc = cdt.insert(Point(4,0));
    Vertex_handle vd = cdt.insert(Point(0,1));
    cdt.insert(Point(2, 0.6));
    cdt.insert_constraint(va, vb);
    cdt.insert_constraint(vb, vc);
    cdt.insert_constraint(vc, vd);
    cdt.insert_constraint(vd, va);
    std::cout << "Number of vertices: " << cdt.number_of_vertices() << std::endl;
    std::cout << "Meshing the triangulation..." << std::endl;
    CGAL::refine_Delaunay_mesh_2(cdt, Criteria(0.125, 0.5));
    std::cout << "Number of vertices: " << cdt.number_of_vertices() << std::endl;

    CDT::Finite_faces_iterator it;
    for (it = cdt.finite_faces_begin(); it != cdt.finite_faces_end(); it++)
    {
        std::cout << cdt.triangle(it)  << std::endl;
    }



    //Access info object make its values the same as the base point
    CDT::Finite_vertices_iterator vt;
    for (vt = cdt.finite_vertices_begin(); vt != cdt.finite_vertices_end(); vt++)
    {
        Vert *vh;
        vh = &vt->info();

        Point_2 *pp;
        pp= &vt->point();

        vh->setX(pp->x());
        vh->setY(pp->y());

        //std::cout << vt->point() << " Info address:"<<  &vt << " Info: " << vh->x << ","<<vh->y << std::endl;
    }


    //Access and manipulate info object
    for( int i = 0; i < 3 ; i++) {
        Vert *vh;
        for (vt = cdt.finite_vertices_begin(); vt != cdt.finite_vertices_end(); vt++) {

            vh = &vt->info();
            vh->setX(vh->x + 1.0);
            vh->setY(vh->y + 1.0);
            }
        std::cout<< "Last Looped: " << vt->point() << std::endl << " Info: " << vh->x << "," << vh->y << std::endl << std::endl;

    }

    CDT::Vertex_handle vhy = cdt.finite_vertex();


    Point_2 testPoint(1,1);
    Point_2 testPoint2(0,0);

    Vector_2 testVector(2,2);

    std::cout << "Vector size:" << testVector << " = "<< sqrt(testVector.squared_length()) << std::endl;


    Vert testCustomVert(0.0, 0.0);

    testCustomVert.Displace(testVector);
    std::cout << "Custom vert pos:" << testCustomVert.x << "," << testCustomVert.y << std::endl;

    testCustomVert.Displace(Vector_2(1,0));
    std::cout << "Custom vert pos:" << testCustomVert.x << "," << testCustomVert.y << std::endl;

    testCustomVert.Displace(Vector_2(1,2),1);
    std::cout << "Custom vert pos:" << testCustomVert.x << "," << testCustomVert.y << std::endl;

    double toDouble = 2.1;
    std::cout<< "val: "<< toDouble << " doubled: " << doubleIt(toDouble)<< std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Hello World!");
    glutDisplayFunc(display);
    glutMainLoop();



    return 0;
}