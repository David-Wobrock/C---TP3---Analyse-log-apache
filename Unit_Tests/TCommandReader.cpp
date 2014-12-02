#include <iostream>

#include "../CommandReader.h"

using namespace std;

void Test_IsGood();
void DisplayStringMap(map<string, string>*);

int main(int argc, char** argv)
{
    CommandReader c(argc, argv);
    
    bool isGood = c.IsGood();
    
    if (isGood)
    {
        DisplayStringMap(c.GetParameters());
    }
    else
    {
        cout << "COUCOU3" << endl;
    }
    
    //Test_IsGood();
    //Test_Fonctionnel();
    
    return 0;
}

void Test_IsGood()
{
    char** argv = new char*[1];
    argv[0] = (char*)string("./analog").c_str();
    
    CommandReader c(1, argv);
    c.IsGood();
    
    delete [] argv;
}

void DisplayStringMap(map<string, string>* m)
{
    map<string, string>::const_iterator iter;
    
    for(iter = m->begin(); iter != m->end(); iter++)
    {
        cout << "[" << iter->first << ", " << iter->second << "]" << endl;
    }
}