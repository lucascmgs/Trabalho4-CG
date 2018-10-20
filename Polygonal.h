#ifndef POLYGONAL_H
#define POLYGONAL_H
#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "Point.h"
#include "Segment.h"
#include "TriangleMesh.h"
#include "Edge.h"
#include <list> 
#include <set>


using namespace std;

class Polygonal {
    public:
    bool isPolygon = false;
    vector<Point*> Points;

    void Reset(){
        isPolygon = false;
        Points.clear();
    }

    void Add(Point *p){
        if(!this->isPolygon){
            this->Points.push_back(p);
        }
    }

    bool IsPolygon(){
        return this->isPolygon;
    }

    bool CheckInside(Point *p){
        if(this->isPolygon){
            int interceptCount = 0;
            Point outerPoint = Point(1.1, 1.1);
            Segment testSegment = Segment(*p, outerPoint);
            for (vector<Point*>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
                vector<Point*>::iterator second;
                second = it;
                second++;
                if(second == this->Points.end()){
                    break;
                }
                
                Segment currentSegment = Segment(**it, **second);

                if(testSegment.Intercepts(currentSegment)){
                    interceptCount++;
                }
            }
            if(interceptCount % 2 == 0) {
                return false;
            } else {
                return true;
            }
        }
        return false;
    }


    void Close (){
        this->isPolygon = true;
    }

    void PlotLines(){
        glLineWidth(3);
        glBegin(GL_LINE_STRIP);
        for (vector<Point*>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){   

            Point p = **it;   
            glColor3f(p.Color[0], p.Color[1], p.Color[2]);
            double px = (*it)->x;
            double py = (*it)->y;
            //cout << "X: " << px << " Y: " << py << endl; 
            glVertex2f(px,py);
        }
        glEnd();
    }

    void PlotPoints(){
        glPointSize(5.0);
        glBegin(GL_POINTS);
        for (vector<Point*>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){     
 
            Point p = **it;
            glColor3f(p.Color[0], p.Color[1], p.Color[2]);
            double px = (*it)->x;
            double py = (*it)->y;
            //cout << "X: " << px << " Y: " << py << endl; 
            glVertex2f(px,py);
        }
        glEnd();
    }

    vector<Point*> GetPoints(){
        return this->Points;
    }

    long unsigned int GetSize(){
        return this->Points.size();
    }
    
    Polygonal GetConvexHull(){

        if(Points.size() < 3){
            return *(this);
        }

        Polygonal result = Polygonal();
        Point * base = new Point();
        for (vector<Point*>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
            if((*it)->y < base->y){
                base = *it;
            }
        }
        Point axis = Point(10, 0);
        Point * originalBase = base;
        base->SetColor(1, 0, 0);
        result.Add(base);

        int k = 0;
        for (Point* newPoint = new Point(); newPoint != originalBase;){
            newPoint = new Point(); 
            double newAngle = 10;
            //cout << "Axis: " << axis << " Base: " << base << endl;     
            for (vector<Point*>::iterator jt = this->Points.begin(); jt != this->Points.end(); ++jt){ 
                Point comparison = **jt - *base;     
                double angle = axis.GetOrientedAngle(comparison); 
                if( **jt != *base && angle >= 0 && angle <= newAngle){
                    newAngle = angle;
                    newPoint = *jt;
                }
                //cout << "Iteration: " << k << " Point: " << **jt << " Angle with base: " << angle << endl;

            }
            axis = *newPoint - *base;
            base = newPoint;
            newPoint->SetColor(1, 0, 0);
            result.Add(newPoint);
            k++;
        } 
        int i = 0;
        for(vector<Point*>::iterator it = result.Points.begin(); it != result.Points.end(); it++){
            cout << "Ponto " << i << ": " <<**it << endl;
            i++;
        }
        result.Close();
        return result;
    }

    TriangleMesh GenerateDelaunay() {
        Polygonal convexHull = this->GetConvexHull();
        TriangleMesh result;
        set<string> visitedEdges;
        for(vector<Point*>::iterator it = convexHull.Points.begin(); it != convexHull.Points.end(); it++){
            vector<Point*>::iterator jt = it;
            jt++;
            if(jt == convexHull.Points.end()){
                jt = convexHull.Points.begin();
            }
            visitedEdges.insert(Edge(*it, *jt).ToString());
            visitedEdges.insert(Edge(*jt, *it).ToString());    
        }
        Edge firstEdge = Edge(convexHull.Points[0], convexHull.Points[1]);
        Triangle * firstTriangle;
        double maxAngle = 0;
        Point * maxPoint;
        for (vector<Point*>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
                Point first = *firstEdge.First - **it ;
                Point second = *firstEdge.Second - **it;
                double angle = first.GetOrientedAngle(second);
                if (angle > maxAngle){
                    maxAngle = angle;
                    maxPoint = *it;
                }
        }
        firstTriangle = new Triangle(firstEdge.First, firstEdge.Second, maxPoint);
        result.Add(firstTriangle);
        list<Triangle> triangleQueue;
        triangleQueue.push_back(*firstTriangle);
        while(!triangleQueue.empty()){
            Triangle itTriangle = triangleQueue.front();
            triangleQueue.pop_front();
            list<Edge> itEdges;
            itEdges.push_back(Edge(itTriangle.First, itTriangle.Second));
            itEdges.push_back(Edge(itTriangle.Second, itTriangle.Third));
            itEdges.push_back(Edge(itTriangle.Third, itTriangle.First));
            for(list<Edge>::iterator it = itEdges.begin(); it != itEdges.end(); it++){
                if(visitedEdges.count(it->ToString()) == 0){
                    double maxAngle = 0;
                    Point * maxPoint = nullptr;
                    for (vector<Point*>::iterator jt = this->Points.begin(); jt != this->Points.end(); ++jt){      
                        Point first = *firstEdge.First - **jt ;
                        Point second = *firstEdge.Second - **jt;
                        double angle = first.GetAngle(second);
                        if (angle > maxAngle && (**jt != (*it->First)) && (**jt != *it->Second)){
                            if(visitedEdges.count(Edge(*jt, maxPoint).ToString()) == 0 && visitedEdges.count(Edge(maxPoint, *jt).ToString()) == 0){
                                cout << "oi" << endl;
                                maxAngle = angle;
                                maxPoint = *jt;
                            }
                        }
                    }
                    Triangle * newTriangle = new Triangle(it->First, it->Second, maxPoint);
                    triangleQueue.push_back(*newTriangle);
                    result.Add(newTriangle);

                    visitedEdges.insert(it->ToString());
                    visitedEdges.insert(Edge(it->Second, it->First).ToString());
                    visitedEdges.insert(Edge(it->First, it->Second).ToString());
                }
            }
        }
        return result;
    }
};

#endif