#include <iostream>
#include <stdlib.h>

#include "../GraphString.h"

using namespace std;

void Test_Insert();
void Test_GetLink();
void Test_GetAllLinks();
void Test_Size();
void Test_Display();
void Test_CreateGraphVizFile();

int main()
{
    Test_Insert();
    Test_GetLink();
    Test_GetAllLinks();
    Test_Size();
    Test_Display();
    Test_CreateGraphVizFile();
    return 0;
}

void Test_Insert() { }
void Test_GetLink() { }
void Test_GetAllLinks() { }
void Test_Size() { }
void Test_Display() { }

void Test_CreateGraphVizFile()
{
    cout << "\tTest de CreateGraphVizFile()" << endl;
    
    cout << "Création d'un graphe et du fichier GraphViz court.dot avec les liens :" << endl;
    cout << "page1 -> page2 (2)" << endl;
    cout << "page2 -> page1 (1)" << endl;
    cout << "page2 -> page3 (1)" << endl;
    cout << "page3 -> page2 (1)" << endl;
    
    GraphString g;
    g.Insert("/page2.html", "/page1.html");
    g.Insert("/page1.html", "/page2.html");
    g.Insert("/page2.html", "/page3.html");
    g.Insert("/page3.html", "/page2.html");
    g.Insert("/page2.html", "/page1.html");
    
    cout << "Résultat de l'exécution : génération de court.dot et d'un court.png" << endl;
    g.CreateGraphVizFile("Unit_Tests/court.dot");
    system("dot -Tpng -o Unit_Tests/court.png Unit_Tests/court.dot");
}