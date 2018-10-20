#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <sstream>

class Edge{
    public:
    Point* First;
    Point* Second;

    Edge(Point * givenFirst, Point * givenSecond){
        this->First = givenFirst;
        this->Second = givenSecond;
    }

    bool operator== (const Edge& operated){
        if(*(this->First) == *(operated.First) && *(this->Second) == *(operated.Second)){
            return true;
        } else {
            return false;
        }
    }

    bool operator< (const Edge& operated) const {
        if(*(this->First) < *(operated.First) && *(this->Second) < *(operated.Second)){
            return true;
        } else {
            return false;
        }
    }

    string ToString(){
        ostringstream myObjectStream;

        myObjectStream << this->First << this->Second;

        return myObjectStream.str();

    }

    bool Intercepts (Edge * operated){

        Point * tFirst = this->First;
        Point * tSecond = this->Second;
        Point * oFirst = operated->First;
        Point * oSecond = operated->Second;

        Point AB = *oSecond - *oFirst;
        Point AD = *tSecond - *oFirst;
        Point AC = *tFirst - *oFirst;

        Point CD = *tSecond - *tFirst;
        Point CA = *oFirst - *tFirst;
        Point CB = *oSecond - *tFirst;

        double ABAD = AB.ZProdVec(AD);
        double ABAC = AB.ZProdVec(AC);

        double CDCA = CD.ZProdVec(CA);
        double CDCB = CD.ZProdVec(CB);

        cout << ABAD << " " << ABAC << endl << CDCA << " " << CDCB << endl << "-----------" << endl ; 

        double firstRes = ABAD * ABAC ;
        double secondRes = CDCA * CDCB ;

        //cout << firstRes << " " << secondRes << endl;
        return (firstRes < 0 && secondRes < 0);
    }
};

ostream& operator<< (ostream& os, const Edge& givenEdge){  
        os << givenEdge.First << givenEdge.Second;  
        return os;  
}  

#endif