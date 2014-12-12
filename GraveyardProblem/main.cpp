#include "edgegraph.h"
#include "customio.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main()
{
    std::string fname = getString("Enter a filename: ");
    std::ifstream in;
    in.open("C:/Users/Conor/Desktop/testyards.txt");

    while(true)
    {
        EdgeGraph *graveyardGraph = new EdgeGraph();
        //get map width and height
        int width,height;
        in >> width >> height;
        std::cout << "Width: " << width << std::endl;
        std::cout << "Height: " << height << std::endl;
        std::cin.sync();
        std::cin.get();
        if(in.peek() == EOF || (width == 0 && height == 0))
        {
            break;
        }
        in.get();

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                graveyardGraph->addVertex(i*width+j);
            }
        }

        for(int i = 0; i < width*height;i++)
        {
            bool excludeLeft = false;
            bool excludeRight = false;
            bool excludeUp = false;
            bool excludeDown = false;
            if(i%width == 0)
            {
                excludeLeft = true;
            }

            if(i % width == width - 1)
            {
                excludeRight = true;
            }

            if(i/width == 0)
            {
                excludeDown = true;
            }

            if(i/width == height - 1)
            {
                excludeUp = true;
            }

            if(!excludeLeft)
            {
                graveyardGraph->addEdge(i,i-1,1);
            }

            if(!excludeRight)
            {
                graveyardGraph->addEdge(i,i+1,1);
            }

            if(!excludeDown)
            {
                graveyardGraph->addEdge(i,i-width,1);
            }

            if(!excludeUp)
            {
                graveyardGraph->addEdge(i,i+width,1);
            }
        }

        int gravestones;
        in >> gravestones;

        for(int i = 0; i < gravestones; i++)
        {
            int graveX, graveY;
            in >> graveX >> graveY;

            graveyardGraph->removeVertex(graveY*width+graveX);
        }

        int holes;
        in >> holes;

        for(int i = 0; i < holes; i++)
        {
            int sourceX,sourceY,destX,destY,time;

            in >> sourceX >> sourceY >> destX >> destY >> time;

            graveyardGraph->addEdgeDirected(sourceX+sourceY*width,destX+destY*width,time);
        }

        std::vector<int> ignored;
        std::vector<edge*> path = graveyardGraph->findKruskalPath(0,(width*height)-1,ignored);

        std::cout << "Path: " << std::endl;

        for(int i = 0; i < path.size(); i++)
        {
            std::cout << path.at(i)->startIndex << "," << path.at(i)->endIndex << std::endl;
        }

        if(path.size() == 0)
        {
            std::cout << "Impossible" << std::endl;
        }
        else
        {
            int pathWeight = 0;
            for(int i = 0; i < path.size(); i++)
            {
                pathWeight += path.at(0)->weight;
            }

            std::cout << pathWeight << std::endl;
        }
    }

    in.close();

    return 0;
}
