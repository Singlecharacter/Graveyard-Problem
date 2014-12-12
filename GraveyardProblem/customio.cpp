#include "customio.h"
#define SCREENSIZE 40

void clearScreen()
{

    std::cout << std::string(SCREENSIZE, '\n');
}

int getInt(std::string prompt = "")
{

    int num;
    while(true)
    {
        std::cout << prompt;
        std::cin.sync();
        std::cin >> num;
        if(std::cin.good())
        {
            break;
        }
        else
        {
            std::cin.clear();
            std::cout << "Error! That wasn't an integer! Please enter an integer." << std::endl;
            std::cin.get();
        }
    }
    return num;
}

float getFloat(std::string prompt = "")
{

    float num;
    while(true)
    {
        std::cout << prompt;
        std::cin.sync();
        std::cin >> num;
        if(std::cin.good())
        {
            break;
        }
        else
        {
            std::cin.clear();
            std::cout << "Error! That wasn't a float! Please enter a float." << std::endl;
            std::cin.get();
        }
    }
    return num;
}

std::string getString(std::string prompt = "")
{
    std::string inString = "";
    std::cout << prompt;
    std::cin.sync();
    getline(std::cin,inString);
    return inString;
}

bool getBool(std::string prompt = "")
{
    bool myBool;
    char inChar = ' ';
    while(true)
    {
        std::cout << prompt;
        std::cin.sync();
        std::cin >> inChar;
        if(inChar == 'Y')
        {
            myBool = true;
            break;
        }
        else if(inChar == 'N')
        {
            myBool = false;
            break;
        }
        else
        {
            std::cout << "That wasn't Y or N! Please enter Y or N." << std::endl;
            std::cin.sync();
            std::cin.get();
        }
    }
    return myBool;
}
