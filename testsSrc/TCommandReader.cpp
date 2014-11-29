#include <iostream>
#include <string>

#include "../CommandReader.h"

using namespace std;

void testIsGood();

int main()
{
    cout << "A";
    testIsGood();
    
    return 0;
}

void testIsGood()
{
    int argc = 1;
    cout << "A";
    char** argv = new char*[argc];
    cout << "A";
    for (int i = 0; i < argc; ++i)
    {
        
        argv[i] = (char*)string("./analog").c_str();
    }
    
    
    CommandReader c(argc, argv);
    cout << c.IsGood();
}