#include <iostream>

#include "CommandReader.h"

using namespace std;

int main(int argc, char** argv)
{
    CommandReader cm(argc, argv);
    map<string, string>* parameters = NULL;
    
    if (cm.IsGood())
    {
        parameters = cm.GetParameters();
    }
    else
    {
        return -1; // Fin du programme : mauvais paramètre
    }
    
    cout << "Autre traitement..." << endl;
    
    
    
    if (parameters != NULL)
    {
        delete parameters;
    }
    
    return 0;
}

