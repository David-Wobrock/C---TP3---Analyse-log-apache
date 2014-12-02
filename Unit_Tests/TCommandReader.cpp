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
    // Tests fonctionnels réalisés avec le framework
    // (surtout tous les tests d'erreur)
    
    cout << "\tTest de IsGood()" << endl;
    cout << "Analyse de la ligne './analog fichier.log -x -g graphe.dot' : syntaxe correcte" << endl;
    int argc1 = 5;
    char** argv1 = new char*[argc1];
    argv1[0] = (char*)"./analog";
    argv1[1] = (char*)"fichier.log";
    argv1[2] = (char*)"-x";
    argv1[3] = (char*)"-g";
    argv1[4] = (char*)"graphe.dot";
      
    CommandReader c1(argc1, argv1);
    cout << "*** Sortie attendue : (ordre pas important)***" << endl;
    cout << "Vrai" << endl;
    cout << "[LOG_FILE_NAME, fichier.log]" << endl;
    cout << "[-x, ]" << endl;
    cout << "[-g, graphe.dot]" << endl;
    cout << "*** Sortie réelle : ***" << endl;
    if (c1.IsGood())
    {
        cout << "Vrai" << endl;
        DisplayStringMap(c1.GetParameters());
    }
    cout << endl;
    delete [] argv1;
    
    
    cout << "Analyse de la ligne './analog fichier.log -t' : erreur" << endl;
    int argc2 = 3;
    char** argv2 = new char*[argc2];
    argv2[0] = (char*)"./analog";
    argv2[1] = (char*)"fichier.log";
    argv2[2] = (char*)"-t";
      
    CommandReader c2(argc2, argv2);
    cout << "*** Sortie attendue : ***" << endl;
    cout << "Il manque l'argument après -t." << endl;
    cout << "./analog [-x] [-t HEURE] [-g FICHIERGRAPH] FICHIERLOG" << endl;
    cout << "*** Sortie réelle : ***" << endl;
    if (c2.IsGood())
    {
        cout << "Vrai" << endl;
        DisplayStringMap(c2.GetParameters());
    }
    cout << "Plus de messages d'erreur sont testés dans les tests fonctionnels (voir tests du framework)" << endl << endl;
    delete [] argv2;
}

void Test_GetParameters()
{
    cout << "\tTest de GetParameters()" << endl;
    
    cout << "Analyse de la ligne './analog fichier.log -x -g graphe.dot'" << endl;
    int argc1 = 5;
    char** argv1 = new char*[argc1];
    argv1[0] = (char*)"./analog";
    argv1[1] = (char*)"fichier.log";
    argv1[2] = (char*)"-x";
    argv1[3] = (char*)"-g";
    argv1[4] = (char*)"graphe.dot";
      
    CommandReader c1(argc1, argv1);
    cout << "*** Sortie attendue : (ordre pas important)***" << endl;
    cout << "[LOG_FILE_NAME, fichier.log]" << endl;
    cout << "[-x, ]" << endl;
    cout << "[-g, graphe.dot]" << endl;
    cout << "*** Sortie réelle : ***" << endl;
    DisplayStringMap(c1.GetParameters());
    cout << endl;
    delete [] argv1;
    
    cout << "Analyse de la ligne './analog fichier.log'" << endl;
    int argc2 = 2;
    char** argv2 = new char*[argc2];
    argv2[0] = (char*)"./analog";
    argv2[1] = (char*)"fichier.log";
    CommandReader c2(argc2, argv2);
    cout << "*** Sortie attendue : ***" << endl;
    cout << "[LOG_FILE_NAME, fichier.log]" << endl;
    cout << "*** Sortie réelle : ***" << endl;
    DisplayStringMap(c2.GetParameters());
    cout << endl;
    delete [] argv2;
    
    cout << "Analyse de la ligne './analog fichier.log -x -g graphe.dot -t 3'" << endl;
    int argc3 = 7;
    char** argv3 = new char*[argc3];
    argv3[0] = (char*)"./analog";
    argv3[1] = (char*)"fichier.log";
    argv3[2] = (char*)"-x";
    argv3[3] = (char*)"-g";
    argv3[4] = (char*)"graphe.dot";
    argv3[5] = (char*)"-t";
    argv3[6] = (char*)"3";
    CommandReader c3(argc3, argv3);
    cout << "*** Sortie attendue : (ordre pas important)***" << endl;
    cout << "[LOG_FILE_NAME, fichier.log]" << endl;
    cout << "[-x, ]" << endl;
    cout << "[-g, graphe.dot]" << endl;
    cout << "[-t, 3]" << endl;
    cout << "*** Sortie réelle : ***" << endl;
    DisplayStringMap(c3.GetParameters());
    cout << endl;
    delete [] argv3;
    
    cout << "Analyse de la ligne './analog fichier.log -x'" << endl;
    int argc4 = 3;
    char** argv4 = new char*[argc4];
    argv4[0] = (char*)"./analog";
    argv4[1] = (char*)"fichier.log";
    argv4[2] = (char*)"-x";
    CommandReader c4(argc4, argv4);
    cout << "*** Sortie attendue :***" << endl;
    cout << "[LOG_FILE_NAME, fichier.log]" << endl;
    cout << "[-x, ]" << endl;
    cout << "*** Sortie réelle : ***" << endl;
    DisplayStringMap(c4.GetParameters());
    cout << endl;
    delete [] argv4;
    
    cout << "Analyse de la ligne './analog fichier.log -g graphe.dot'" << endl;
    int argc5 = 4;
    char** argv5 = new char*[argc5];
    argv5[0] = (char*)"./analog";
    argv5[1] = (char*)"fichier.log";
    argv5[2] = (char*)"-g";
    argv5[3] = (char*)"graphe.dot";
    CommandReader c5(argc5, argv5);
    cout << "*** Sortie attendue :***" << endl;
    cout << "[LOG_FILE_NAME, fichier.log]" << endl;
    cout << "[-g, graphe.dot]" << endl;
    cout << "*** Sortie réelle : ***" << endl;
    DisplayStringMap(c5.GetParameters());
    cout << endl;
    delete [] argv5;
}

void DisplayStringMap(map<string, string>* m)
{
    map<string, string>::const_iterator iter;
    
    for(iter = m->begin(); iter != m->end(); iter++)
    {
        cout << "[" << iter->first << ", " << iter->second << "]" << endl;
    }
}