#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "Point.h"
#include "Segment.h"
#include "Polygonal.h"

using namespace std;


const float GREEN[3] = {0.0, 1.0, 0.0};
const float RED[3] = {1.0, 0.0, 0.0};


const int WINDOWSIZE = 500;

Polygonal IsolatedPoints;
TriangleMesh triangles;

void resetScreen(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
}

void mouse (int button, int state, int givenX, int givenY)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point * result = new Point((2.*givenX)/WINDOWSIZE - 1., -(2.*givenY)/WINDOWSIZE + 1.);
        resetScreen();
        
        IsolatedPoints.Add(result);
        glutPostRedisplay();
    }
}

void keyboard_cb(unsigned char key, int X, int Y)
{
    switch (key)
    {
        case 27:             
            exit (0);
            break;

        //Tecla para chamar a suaviação das retas
        case 'c':
            IsolatedPoints.GetConvexHull().PlotLines();
            glutPostRedisplay();
            break;
        case 'd':
            triangles = IsolatedPoints.GenerateDelaunay();
            glutPostRedisplay();
            break;
        //Tecla para limpar os points
        case 'r':
            cout << "Pontos resetados" << endl;
            IsolatedPoints.Reset();
            triangles.Reset();
            glutPostRedisplay();
            break;
    }
}




void display() {
    resetScreen();

    
    IsolatedPoints.PlotPoints();
    if(!triangles.Triangles.empty()){
        triangles.PlotTriangles();
    }

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    IsolatedPoints = Polygonal();
    triangles = TriangleMesh();
    glutInit(&argc,argv);
    glutInitWindowSize (WINDOWSIZE, WINDOWSIZE);
    glutCreateWindow("points");
    glutKeyboardFunc(keyboard_cb);
    glutMouseFunc(mouse);
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return EXIT_SUCCESS ;

}
