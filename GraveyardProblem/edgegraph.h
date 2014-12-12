#ifndef EDGEGRAPH_H
#define EDGEGRAPH_H

#include <vector>
#include <iostream>

struct vertex
{
    int data;
    bool beenVisited;
};

struct edge
{
    int startIndex;
    int endIndex;
    int weight;
    bool directed;

    bool beenChecked;
};

class EdgeGraph
{
public:

    EdgeGraph();
    ~EdgeGraph();

    void addVertex(int newData);
    bool addEdge(int firstValue, int secondValue, int weight);
    void addEdgeDirected(int firstValue, int secondValue, int weight);
    void removeEdge(int firstValue, int secondValue);
    void removeVertex(int removeIndex);

    int getIndex(int value);
    int getValue(int index);

    //These methods return a vector containing a sequence of indexes which detail a path from
    //the vertex containing startValue to the vertex containing endValue
    //std::vector<int> findDijkstraPath(int startValue, int endValue);
    //std::vector<int> findPrimPath(int startValue, int endValue);
    std::vector<edge*> findKruskalPath(int startIndex, int endIndex, std::vector<int> ignoredEdgeIndexes);
    std::vector<edge*> findKruskalPath(int startIndex, int endIndex, std::vector<std::vector<edge*> > trees, std::vector<int> ignoredEdgeIndexes);

private:

    int findVertex(int searchData);

    std::vector<edge*> edges;
    std::vector<vertex*> vertices;
};

#endif // EDGEGRAPH_H

