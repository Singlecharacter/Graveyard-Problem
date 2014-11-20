#include "edgegraph.h"

EdgeGraph::EdgeGraph()
{

}

EdgeGraph::~EdgeGraph()
{

}

void EdgeGraph::addVertex(int newData)
{
    if(findVertex(newData) < 0)
    {
        vertex newVertex;
        newVertex.data = newData;
        newVertex.beenVisited = false;
        vertices.push_back(newVertex);
    }
}

void EdgeGraph::addEdge(int firstValue, int secondValue, int weight)
{
    int firstIndex = findVertex(firstValue);
    int secondIndex = findVertex(secondValue);

    if(firstIndex >= 0 && secondIndex >= 0)
    {
        edge newEdge;

        newEdge.startIndex = firstIndex;
        newEdge.endIndex = secondIndex;
        newEdge.directed = false;
        newEdge.weight = weight;
        newEdge.beenChecked = false;

        edges.push_back(newEdge);
    }
}

void EdgeGraph::addEdgeDirected(int firstValue, int secondValue, int weight)
{
    int firstIndex = findVertex(firstValue);
    int secondIndex = findVertex(secondValue);

    if(firstIndex >= 0 && secondIndex >= 0)
    {
        edge newEdge;

        newEdge.startIndex = firstIndex;
        newEdge.endIndex = secondIndex;
        newEdge.directed = true;
        newEdge.weight = weight;
        newEdge.beenChecked = false;

        edges.push_back(newEdge);
    }
}

void EdgeGraph::removeEdge(int firstValue, int secondValue)
{
    int firstIndex = findVertex(firstValue);
    int secondIndex = findVertex(secondValue);

    if(firstIndex >= 0 && secondIndex >= 0)
    {
        for(int i = 0; i < edges.size(); i++)
        {
            if((edges.at(i).startIndex == firstIndex && edges.at(i).endIndex == secondIndex)
               || (edges.at(i).startIndex == secondIndex && edges.at(i).endIndex == firstIndex))
            {
                edges.erase(edges.begin()+i);
                break;
            }
        }
    }
}

void EdgeGraph::removeVertex(int removeData)
{
    int removeIndex = findVertex(removeData);

    if(removeIndex >= 0)
    {
        for(int i = 0; i < edges.size(); i++)
        {
            if(edges.at(i).startIndex == removeIndex || edges.at(i).endIndex == removeIndex)
            {
                edges.erase(edges.begin()+i);
                i--;
            }
        }

        vertices.erase(vertices.begin()+removeIndex);
    }
}

int EdgeGraph::findVertex(int searchData)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).data == searchData)
        {
            return i;
        }
    }

    return -1;
}

int EdgeGraph::getIndex(int value)
{
    return findVertex(value);
}

int EdgeGraph::getValue(int index)
{
    return vertices.at(index).data;
}

std::vector<edge> findKruskalPath(int startIndex, int endIndex)
{
    for(int i = 0; i < edges.size(); i++)
    {
        edges.at(i).beenChecked = false;
    }

    std::vector< std::vector<edge> > trees;
    std::vector<edge> temp;
    trees.push_back(temp);

    if(edges.size() >= vertices.size() - 1)
    {
        int smallestWeight = edges.at(0).weight;
        int smallestIndex = 0;

        for(int i = 1; i < edges.size; i++)
        {
            if(edges.at(i).weight < smallestWeight)
            {
                smallestWeight = edges.at(i).weight;
                smallestIndex = i;
            }
        }

        trees.at(0).push_back(edges.at(smallestIndex));

        return findKruskalPath(startValue,endValue,trees);
    }
    else
    {
        std::vector<edge> path;
        return path;
    }
}

std::vector<edge> findKruskalPath(int startValue, int endValue, std::vector<std::vector<edge> > trees)
{
    if(edges.size() >= vertices.size() - 1)
    {
        while(trees.at(0).size() < vertices.size() - 1)
        {
            smallestWeight = edges.at(0).weight;
            smallestIndex = 0;
            for(int i = 0; i < edge.size(); i++)
            {
                if(edges.at(i).weight < smallestWeight && !edges.at(i).beenChecked)
                {
                    smallestWeight = edges.at(i).weight;
                    smallestIndex = i;
                }
            }

            edge smallestEdge = edges.at(smallestIndex);

            for(int i = 0; i < trees.size(); i++)
            {
                for(int j = 0; j < trees.at(i).size(); j++)
                {
                    edge *treeEdge = &trees.at(i).at(j);
                    if(smallestEdge.startIndex == treeEdge->startIndex || smallestEdge.startIndex == treeEdge->endIndex)
                    {
                        bool edgeOkay = true;
                        for(int k = 0; k < trees.at(i).size(); k++)
                        {
                            edge *otherTreeEdge = &trees.at(i).k;
                            if(k != j)
                            {
                                if(smallestEdge.)
                            }
                        }
                    }
                    else if(smallestEdge.endIndex == treeEdge->startIndex || smallestEdge.endIndex == treeEdge->endIndex)
                    {

                    }
                }
            }
        }
    }
    else
    {
        std::vector<edge> path;
        return path;
    }
}
