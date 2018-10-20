#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <vector>

using namespace std;

class Triangle {
    public:
    Point * First;
    Point * Second;
    Point * Third;

    Triangle(){   }
    Triangle(Point * givenFirst, Point * givenSecond, Point * givenThird){
        this->First = givenFirst;
        this->Second = givenSecond;
        this->Third = givenThird;
    }
};

class TriangleMesh{
    public:
    vector<Triangle*> Triangles;

    void Add(Triangle * triangle){
        Triangles.push_back(triangle);
    }
    void PlotTriangles(){
        cout << "Qtd de triangulos: " << Triangles.size() << endl;
        glLineWidth(2);
        int k = 0;
        glBegin(GL_TRIANGLES);
        for(vector<Triangle*>::iterator it = Triangles.begin(); it < Triangles.end(); it++ ){
            cout << (*it)->First->x << " " << (*it)->First->y<< endl;
            cout << (*it)->Second->x << " " << (*it)->Second->y<< endl;
            cout << (*it)->Third->x << " " << (*it)->Third->y<< endl << endl;
            k++;
        
            glColor3f(0, 1, 0);
            
            glVertex2f((*it)->First->x,(*it)->First->y);
            glVertex2f((*it)->Second->x,(*it)->Second->y);
            glVertex2f((*it)->Third->x,(*it)->Third->y);
            
        
        }
        glEnd();
        for(vector<Triangle*>::iterator it = Triangles.begin(); it < Triangles.end(); it++ ){
            glBegin(GL_LINE_STRIP);
        
            glColor3f(1, 0, 0);
            
            glVertex2f((*it)->First->x,(*it)->First->y);
            glVertex2f((*it)->Second->x,(*it)->Second->y);
            glVertex2f((*it)->Third->x,(*it)->Third->y);
            glVertex2f((*it)->First->x,(*it)->First->y);
        
            glEnd();
        }
    }

    void Reset(){
        Triangles.clear();
    }
};



#endif