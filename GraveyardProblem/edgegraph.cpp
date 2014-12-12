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

bool EdgeGraph::addEdge(int firstValue, int secondValue, int weight)
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

        return true;
    }
    else
    {
        return false;
    }
}

void EdgeGraph::addEdgeDirected(int firstValue, int secondValue, int weight)
{
    int firstIndex = findVertex(firstValue);
    int secondIndex = findVertex(secondValue);

    if(firstIndex >= 0 && secondIndex >= 0)
    {
        edge *newEdge = new edge;

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

void EdgeGraph::removeVertex(int removeIndex)
{
    std::cout << removeIndex << std::endl;
    std::cout << "Edges before remove: " << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); i++)
    {
        std::cout << edges.at(i)->startIndex << "," << edges.at(i)->endIndex << std::endl;
    }

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
    }

    std::cout << "Edges after remove: " << edges.size() << std::endl;
    for(int i = 0; i < edges.size(); i++)
    {
        std::cout << edges.at(i)->startIndex << "," << edges.at(i)->endIndex << std::endl;
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

std::vector<edge*> EdgeGraph::findKruskalPath(int startIndex, int endIndex, std::vector<int> ignoredEdgeIndexes)
{
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
        ignoredEdgeIndexes.push_back(smallestIndex);

        return findKruskalPath(startIndex,endIndex,trees, ignoredEdgeIndexes);
    }
    else
    {
        std::vector<edge*> path;
        return path;
    }
}

std::vector<edge*> EdgeGraph::findKruskalPath(int startIndex, int endIndex, std::vector<std::vector<edge*> > trees, std::vector<int> ignoredEdgeIndexes)
{
    std::cout << "Starting at: " << startIndex << std::endl;
    std::cout << "Ending at: " << endIndex << std::endl;

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
                break;
            }

            edge *smallestEdge = edges.at(smallestIndex);
            smallestEdge->beenChecked = true;

            //Make sure the new edge doesn't form a cycle in any trees, then add it to all connecting trees

            int connectionCounter = 0;

            for(int i = 0; i < trees.at(0).size(); i++)
            {
                edge *treeEdge = trees.at(0).at(i);

                //Duplicate edge check
                if((smallestEdge->endIndex == treeEdge->endIndex && smallestEdge->startIndex == treeEdge->endIndex) ||
                   (smallestEdge->endIndex == treeEdge->startIndex && smallestEdge->startIndex == treeEdge->endIndex))
                {
                    connectionCounter = 3;
                    break;
                }

                if(smallestEdge->startIndex == treeEdge->startIndex)
                {
                    connectionCounter++;
                }

                if(smallestEdge->startIndex == treeEdge->endIndex)
                {
                    connectionCounter++;
                }

                if(smallestEdge->endIndex == treeEdge->startIndex)
                {
                    connectionCounter++;
                }

                if(smallestEdge->endIndex == treeEdge->endIndex)
                {
                    connectionCounter++;
                }
            }

            //The edge connects to the tree in one or fewer places, meaning no cycle is formed
            if(connectionCounter <= 2)
            {
                trees.at(0).push_back(smallestEdge);
            }
        }

        //Find the path from start to end, if it exists

        //Push the first edge onto the path
        std::vector<edge*> path;
        std::vector<edge*> spanningTree = trees.at(0);

        std::cout << "Spanning tree: " << std::endl;

        for(int i = 0; i < spanningTree.size(); i++)
        {
            std::cout << spanningTree.at(i)->startIndex << "," << spanningTree.at(i)->endIndex << std::endl;
        }

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
                    spanningTree.erase(spanningTree.begin()+i);
                    trees.at(0) = spanningTree;
                    return findKruskalPath(startIndex,endIndex,trees,ignoredEdgeIndexes);
                }
                else
                {
                    path.push_back(spanningTree.at(i));
                    break;
                }
            }
        }

        for(int i = 0; i < spanningTree.size(); i++)
        {
            spanningTree.at(i)->beenChecked = false;
        }

        while(true)
        {
            bool addedNewEdge = false;
            for(int i = 0; i < spanningTree.size(); i++)
            {
                if(spanningTree.at(i)->startIndex == path.at(path.size()-1)->endIndex && !spanningTree.at(i)->beenChecked)
                {
                    addedNewEdge = true;
                    path.push_back(spanningTree.at(i));
                    spanningTree.at(i)->beenChecked = true;
                    break;
                }
                else if(spanningTree.at(i)->endIndex == path.at(path.size()-1)->endIndex && !spanningTree.at(i)->beenChecked)
                {
                    if(spanningTree.at(i)->directed)
                    {
                        spanningTree.erase(spanningTree.begin()+i);
                        trees.at(0) = spanningTree;
                        return findKruskalPath(startIndex,endIndex,trees,ignoredEdgeIndexes);
                    }
                    else
                    {
                        addedNewEdge = true;
                        path.push_back(spanningTree.at(i));
                        spanningTree.at(i)->beenChecked = true;
                        break;
                    }
                }
            }

            if(addedNewEdge)
            {
                if(path.at(path.size()-1)->endIndex == endIndex)
                {
                    return path;
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        std::vector<edge*> path;
        return path;
    }

    std::vector<edge*> path;
    return path;
}
