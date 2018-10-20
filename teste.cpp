#include "Point.h"
#include "Edge.h"
#include <list>
#include <set>
#include <sstream>

using namespace std;

int main() {
    list<Point**> points;
    set<string> arestas;

    Point *x = new Point(1, 1);
    Point *y = new Point(2, 3);
    Point *z = new Point(5, 6);
    Point *w = new Point(7, 8);

    Edge aresta1 = Edge(x, y);
    Edge aresta2 = Edge(x, y);
    Edge aresta3 = Edge(z, y);
    arestas.insert(aresta1.ToString());

    // ostringstream myObjectStream;

    // myObjectStream << aresta1;

    // string teste = myObjectStream.str();

    cout << aresta1.ToString() << endl;

    cout << (aresta1 == aresta3) << endl;
    cout << (arestas.count(aresta1.ToString())) << endl;
    cout << (arestas.count(aresta2.ToString())) << endl;
    cout << (arestas.count(aresta3.ToString())) << endl;



    Point *k [3]= {x, y, z};
    points.push_back(k);

    return 0;
}