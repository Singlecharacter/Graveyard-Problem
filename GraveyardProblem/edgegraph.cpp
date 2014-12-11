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
        vertex *newVertex = new vertex;
        newVertex->data = newData;
        newVertex->beenVisited = false;
        vertices.push_back(newVertex);
    }
}

void EdgeGraph::addEdge(int firstValue, int secondValue, int weight)
{
    int firstIndex = findVertex(firstValue);
    int secondIndex = findVertex(secondValue);

    if(firstIndex >= 0 && secondIndex >= 0)
    {
        edge *newEdge = new edge;

        newEdge->startIndex = firstIndex;
        newEdge->endIndex = secondIndex;
        newEdge->directed = false;
        newEdge->weight = weight;
        newEdge->beenChecked = false;

        edges.push_back(newEdge);
    }
}

void EdgeGraph::addEdgeDirected(int firstValue, int secondValue, int weight)
{
    int firstIndex = findVertex(firstValue);
    int secondIndex = findVertex(secondValue);

    if(firstIndex >= 0 && secondIndex >= 0)
    {
        edge *newEdge;

        newEdge->startIndex = firstIndex;
        newEdge->endIndex = secondIndex;
        newEdge->directed = true;
        newEdge->weight = weight;
        newEdge->beenChecked = false;

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
            if((edges.at(i)->startIndex == firstIndex && edges.at(i)->endIndex == secondIndex)
               || (edges.at(i)->startIndex == secondIndex && edges.at(i)->endIndex == firstIndex))
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
            if(edges.at(i)->startIndex == removeIndex || edges.at(i)->endIndex == removeIndex)
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
        if(vertices.at(i)->data == searchData)
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
    return vertices.at(index)->data;
}

std::vector<edge*> EdgeGraph::findKruskalPath(int startValue, int endValue, std::vector<int> ignoredEdgeIndexes)
{
    int startIndex = findVertex(startValue);
    int endIndex = findVertex(endValue);

    if(!(startIndex >= 0 && endIndex >= 0))
    {
        std::vector<edge*> path;
        return path;
    }

    std::vector< std::vector<edge*> > trees;
    std::vector<edge*> temp;
    trees.push_back(temp);

    if(edges.size() >= vertices.size() - 1)
    {
        int smallestWeight = edges.at(0)->weight;
        int smallestIndex = 0;

        for(int i = 1; i < edges.size(); i++)
        {
            if(edges.at(i)->weight < smallestWeight)
            {
                smallestWeight = edges.at(i)->weight;
                smallestIndex = i;
            }
        }

        trees.at(0).push_back(edges.at(smallestIndex));

        return findKruskalPath(startValue,endValue,trees, ignoredEdgeIndexes);
    }
    else
    {
        std::vector<edge*> path;
        return path;
    }
}

std::vector<edge*> EdgeGraph::findKruskalPath(int startValue, int endValue, std::vector<std::vector<edge*> > trees, std::vector<int> ignoredEdgeIndexes)
{
    int startIndex = findVertex(startValue);
    int endIndex = findVertex(endValue);

    if(!(startIndex >= 0 && endIndex >= 0))
    {
        std::vector<edge*> path;
        return path;
    }

    for(int i = 0; i < edges.size(); i++)
    {
        edges.at(i)->beenChecked = false;
    }

    for(int i = 0; i < ignoredEdgeIndexes.size(); i++)
    {
        edges.at(ignoredEdgeIndexes.at(i))->beenChecked = true;
    }

    if(edges.size() >= vertices.size() - 1)
    {
        while(trees.at(0).size() < vertices.size() - 1)
        {
            //Find the edge with smallest weight that hasn't been checked yet
            int smallestWeight = edges.at(0)->weight;
            int smallestIndex = 0;
            bool foundSmallest = false;
            for(int i = 0; i < edges.size(); i++)
            {
                if(edges.at(i)->weight <= smallestWeight && !edges.at(i)->beenChecked)
                {
                    foundSmallest = true;
                    smallestWeight = edges.at(i)->weight;
                    smallestIndex = i;
                }
            }

            if(!foundSmallest)
            {
                std::vector<edge*> path;
                return path;
            }

            edge *smallestEdge = edges.at(smallestIndex);
            smallestEdge->beenChecked = true;

            //Make sure the new edge doesn't form a cycle in any trees, then add it to all connecting trees
            for(int i = 0; i < trees.size(); i++)
            {
                bool addedEdge = false;
                for(int j = 0; j < trees.at(i).size(); j++)
                {
                    edge *treeEdge = trees.at(i).at(j);
                    if(smallestEdge->startIndex == treeEdge->startIndex || smallestEdge->startIndex == treeEdge->endIndex
                       || smallestEdge->endIndex == treeEdge->startIndex || smallestEdge->endIndex == treeEdge->endIndex)
                    {
                        bool edgeOkay = true;

                        //Ensure a cycle isn't formed
                        for(int k = 0; k < trees.at(i).size(); k++)
                        {
                            edge *otherTreeEdge = trees.at(i).at(k);
                            if(k != j)
                            {
                                if(smallestEdge->endIndex == otherTreeEdge->startIndex || smallestEdge->endIndex == otherTreeEdge->endIndex)
                                {
                                    edgeOkay = false;
                                    break;
                                }
                            }
                            else
                            {
                                //Duplicate edge check
                                if((smallestEdge->startIndex == otherTreeEdge->startIndex && smallestEdge->endIndex == otherTreeEdge->endIndex)
                                   || (smallestEdge->startIndex == otherTreeEdge->endIndex && smallestEdge->endIndex == otherTreeEdge->startIndex))
                                {
                                    edgeOkay = false;
                                    break;
                                }
                            }
                        }

                        if(edgeOkay)
                        {
                            trees.at(i).push_back(smallestEdge);
                            addedEdge = true;
                        }
                    }
                }

                if(addedEdge)
                {
                    ignoredEdgeIndexes.push_back(smallestIndex);

                    //Combine trees that now share the newly added edge, if any
                    std::vector<int> sharedIndexes;
                    for(int j = 0; j < trees.size(); j++)
                    {
                        for(int k = 0; k < trees.at(j).size(); k++)
                        {
                            if(smallestEdge == trees.at(j).at(k))
                            {
                                sharedIndexes.push_back(j);
                                break;
                            }
                        }
                    }

                    for(int j = sharedIndexes.size()-1; j > 0; j--)
                    {
                        for(int k = 0; k < trees.at(sharedIndexes.at(j)).size(); k++)
                        {
                            if(trees.at(sharedIndexes.at(j)).at(k) != smallestEdge)
                            {
                                trees.at(sharedIndexes.at(j)).erase(trees.at(sharedIndexes.at(j)).begin()+k);
                                trees.at(sharedIndexes.at(0)).push_back(trees.at(sharedIndexes.at(j)).at(k));
                            }
                        }
                        trees.erase(trees.begin()+sharedIndexes.at(j));
                    }

                    //If the new amalgamated vector is large than trees[0], swap the two
                    if(trees.at(sharedIndexes.at(0)).size() > trees.at(0).size())
                    {
                        trees.at(0).swap(trees.at(sharedIndexes.at(0)));
                    }

                    break;
                }
            }
        }

        //Find the path from start to end

        //Push the first edge onto the path
        std::vector<edge*> path;
        std::vector<edge*> spanningTree = trees.at(0);
        for(int i = 0; i < spanningTree.size(); i++)
        {
            if(spanningTree.at(i)->startIndex == startIndex)
            {
                path.push_back(spanningTree.at(i));
                break;
            }
            else if(spanningTree.at(i)->endIndex == startIndex)
            {
                if(spanningTree.at(i)->directed)
                {
                    for(int j = 0; j < edges.size(); j++)
                    {
                        if(spanningTree.at(i) == edges.at(j))
                        {
                            spanningTree.erase(spanningTree.begin()+i);
                            ignoredEdgeIndexes.push_back(j);
                            trees.at(0) = spanningTree;
                            return findKruskalPath(startValue,endValue,trees,ignoredEdgeIndexes);
                        }
                    }
                }
                else
                {
                    path.push_back(spanningTree.at(i));
                    break;
                }
            }
        }

        while(true)
        {
            for(int i = 0; i < spanningTree.size(); i++)
            {
                if(spanningTree.at(i)->startIndex == path.at(path.size()-1)->endIndex)
                {
                    path.push_back(spanningTree.at(i));
                    break;
                }
                else if(spanningTree.at(i)->endIndex == path.at(path.size()-1)->endIndex)
                {
                    if(trees.at(0).at(i)->directed)
                    {
                        spanningTree.erase(trees.at(0).begin()+i);
                        i--;
                    }
                    else
                    {
                        path.push_back(trees.at(0).at(i));
                        break;
                    }
                }
            }

            if(path.at(path.size()-1)->endIndex == endIndex;)
        }
    }
    else
    {
        std::vector<edge*> path;
        return path;
    }
}
