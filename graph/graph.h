#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>

using namespace std;

template<class TypeOfVer,class TypeOfEdge>
class graph
{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;//w是边的权值
    virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
    virtual bool exist(TypeOfVer x, TypeOfVer y) const = 0;
    int numOfVer() const { return Vers; }
    int numOfEdge() const { return Edges; }
protected:
    int Vers, Edges;
};


#endif // GRAPH_H_INCLUDED
