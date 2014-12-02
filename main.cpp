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
        return -1; // Fin du programme : mauvais paramètre ou aide demandée
    }
    
    cout << "Autre traitement..." << endl;
    
    
    return 0;
}

