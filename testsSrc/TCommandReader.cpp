#include <iostream>

#include "../CommandReader.h"

using namespace std;

void Test_IsGood();
void Test_Fonctionnel();
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

void Test_Fonctionnel()
{
    char** argv;
    
    //cout << "\tTest de la ligne './analog prog.log'" << endl;
    //cout << "Sortie attendue : [prog.log, ]" << endl;
    argv = new char*[2];
    argv[0] = (char*)string("./analog").c_str();
    argv[1] = (char*)string("prog.log").c_str();
    
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    
    CommandReader c1(2, argv);
    if (c1.IsGood())
    {
        DisplayStringMap(c1.GetParameters());
    }
    //cout << endl;
    
}

void DisplayStringMap(map<string, string>* m)
{
    map<string, string>::const_iterator iter;
    
    for(iter = m->begin(); iter != m->end(); iter++)
    {
        cout << "[" << iter->first << ", " << iter->second << "]" << endl;
    }
}