#include <iostream>


#include <OpenGL/gl.h>
#include <GLUT/glut.h>


#include "vert/vert.h"

#include "mesh/mesh.h"

#include <math.h>

#include "stdfx.h"

CDT cdt;

void initCDTInfo(CDT &cd) {
    CDT::Finite_vertices_iterator vt;
    for (vt = cd.finite_vertices_begin(); vt !=  cd.finite_vertices_end(); vt++)
    {
        Vert *vh;
        vh = &vt->info();

        std::cout << vt->point().x() << std::endl;

        vh->setX(vt->point().x());
        vh->setY(vt->point().y());
        vh->setZ(0);

        std::cout << vt->point() << " Info address:"<<  &vt << " Info: " << vh->x << ","<<vh->y << std::endl;
    }
}

void displayFaces(CDT &cd, float scale) {

    glColor3f(1, 0, 0);
    Vertex_handle vh;
    CDT::Finite_faces_iterator it;
    for (it = cd.finite_faces_begin(); it != cd.finite_faces_end(); it++) {
        glColor3ub( rand()%255, rand()%255, rand()%255 );
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < 3; i++){
            glVertex3f(it->vertex(i)->info().x * scale, it->vertex(i)->info().y * scale, it->vertex(i)->info().z * scale);
        }
        glEnd();
        std::cout << "Tri X :" << cd.triangle(it)[0].x() << " Tri Y :" << cd.triangle(it)[0].y() << std::endl;
    }
}

void displayEdges(CDT &cd, float scale) {
    glLineWidth(2.5);
    glColor3f(1, 1, 0);
    CDT::Finite_edges_iterator ft;
    for ( ft = cd.finite_edges_begin(); ft !=cd.finite_edges_end(); ft++){
        glBegin(GL_LINES);
        glVertex3f(ft->first->vertex((ft->second+2)%3)->info().x * scale,ft->first->vertex((ft->second+2)%3)->info().y * scale, ft->first->vertex((ft->second+2)%3)->info().z * scale);
        glVertex3f(ft->first->vertex((ft->second+1)%3)->info().x * scale,ft->first->vertex((ft->second+1)%3)->info().y * scale, ft->first->vertex((ft->second+1)%3)->info().z * scale);
        glEnd();
    }
}

void calculateEdgeMove(){};

void display() {


    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0 * h / w, 2.0 * h / w, -2.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(.001, .001, 10, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glScalef(.005,.005,.005);

    displayFaces(cdt, 100);
    displayEdges(cdt, 100);

    std::cout << "W/H: " << w << "/"<< h <<std::endl;
    glutSwapBuffers();
} /* end func displayCall */

int main(int argc, char *argv[]) {


    Vertex_handle va = cdt.insert(Point(-2,-2));
    Vertex_handle vb = cdt.insert(Point(-2,2));
    Vertex_handle vc = cdt.insert(Point(2,2));
    Vertex_handle vd = cdt.insert(Point(2,-2));
    //cdt.insert(Point(2, 0.6));
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

    initCDTInfo(cdt);


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

    Vector_3 testVector(2,2,3);

    std::cout << "Vector size:" << testVector << " = "<< sqrt(testVector.squared_length()) << std::endl;

    Vert testCustomVert(0.0, 0.0, 0.0);

    testCustomVert.Displace(testVector);
    std::cout << "Custom vert pos:" << testCustomVert.x << "," << testCustomVert.y << std::endl;

    testCustomVert.Displace(Vector_3(1,0, 0));
    std::cout << "Custom vert pos:" << testCustomVert.x << "," << testCustomVert.y << std::endl;

    testCustomVert.Displace(Vector_3(1,2,0),1);
    std::cout << "Custom vert pos:" << testCustomVert.x << "," << testCustomVert.y << std::endl;

    double toDouble = 2.1;
    std::cout<< "val: "<< toDouble << " doubled: " << doubleIt(toDouble)<< std::endl;


    //Vertices of a given edge.
    CDT::Finite_edges_iterator ft;
    for ( ft = cdt.finite_edges_begin(); ft !=cdt.finite_edges_end(); ft++){
        std::cout<< "source: " << cdt.segment(ft).source()<< std::endl;
        std::cout<< "target: " << cdt.segment(ft).target()<< std::endl;
    }

    //Need to find points opposite an edge.
    for ( ft = cdt.finite_edges_begin(); ft !=cdt.finite_edges_end(); ft++){
        std::cout<< "source: " << cdt.segment(ft)<< std::endl;
        std::cout<< "source: " << cdt.segment(ft).source()<< std::endl;
        std::cout<< "target: " << cdt.segment(ft).target()<< std::endl;
    }


    // Circulators on a point

    // Face circulator
    Face_handle fh;


    std::cout << "##### Faces circulator" << std::endl;

    ///traverse all vertices
    for (vt = cdt.finite_vertices_begin(); vt != cdt.finite_vertices_end(); vt++) {

        /// incident faces circulator
        CDT::Face_circulator fc = vt->incident_faces(fh);

        /// number of faces connected
        int csize = CGAL::circulator_size(fc);

        std::cout <<std::endl << "Vertex : " << vt->point().x()<< ", " << vt->point().y()<< std::endl;
        std::cout << "Face circulator size: " << csize << std::endl;

        /// look at each face
        for (int n = 0; n < csize; n++) {

            ///points on the face
            for(int i =0 ;i<3;i++) {
                std::cout << "  Point "<<i<<" of face " << n << " : " << fc->vertex(i)->point().x() << ", "
                          << fc->vertex(i)->point().y() << std::endl;
            }
            std::cout <<std::endl;

            ///increment face circulator
            fc++;
        }

        std::cout <<std::endl;

        ///incident vertices
        CDT::Vertex_circulator vc = vt->incident_vertices();
        int vsize = CGAL::circulator_size(vc);

        for (int n = 0; n < vsize; n++) {

            ///Vertex adjacent to the vertex

                std::cout << " Incident Vertex " << n << " : " << vc->point().x() << ", " << vc->point().y() << std::endl;

            ///increment Vertex circulator
            vc++;


            //can find here all the edges associated with the point to apply strain.

        }
        std::cout <<std::endl;

    }


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Mesh");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}