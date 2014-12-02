#include <iostream>

#include "../CommandReader.h"

using namespace std;

void Test_IsGood();
void Test_GetParameters();
void DisplayStringMap(map<string, string>*);

int main()
{    
    Test_IsGood();
    Test_GetParameters();
    
    return 0;
}

void Test_IsGood()
{
   
}

void Test_GetParameters()
{
    
}

void DisplayStringMap(map<string, string>* m)
{
    map<string, string>::const_iterator iter;
    
    for(iter = m->begin(); iter != m->end(); iter++)
    {
        cout << "[" << iter->first << ", " << iter->second << "]" << endl;
    }
}