/*************************************************************************
                           GraphString  -  description
                             -------------------
    début                : 05/12/2014
    copyright            : (C) 2014 par Loïc Touzard et David Wobrock
*************************************************************************/

//---------- Réalisation de la classe <GraphString> (fichier GraphString.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "GraphString.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés
typedef map<string, int> Inner_map; //map interne, contenant la cible et son nombre de liens
typedef pair<Inner_map, int> Inner_pair;
typedef map<string, Inner_pair> Outer_map;


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type GraphString::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void GraphString::Insert(string referer, string target)
{
    if(graph.find(target) != graph.end())
    {
        cout << "OUI" << endl;
        // la clé existe
        Inner_pair* currentPair = &graph[target];
        Inner_map* currentInnerMap = &currentPair->first;
        currentPair->second++;// on incrémente le compteur de liens totaux
        if(currentInnerMap->find(referer) != currentInnerMap->end())
        {
            // le liens existe
            (*currentInnerMap)[referer]++;
        }
        else
        {
            // le liens n'existe pas, on l'insere
            (*currentInnerMap)[referer]++;
        }

    }
    else
    {
        //la clé n'existe pas, on la créée
        cout << "NON" << endl;
        Inner_map newMap;
        newMap[referer] = 1;
        Inner_pair newPair(newMap, 1);
        graph[target] = newPair;
    }
}


int GraphString::GetLinks(string referer, string target)
{
    return graph[target].first[referer];
}

int GraphString::GetAllLinks(string target)
{
    return graph[target].second;
}

int GraphString::Size()
{
    return graph.size();
}

void GraphString::Display()
{
    for(Outer_cIterator i = graph.begin(), iend = graph.end(); i != iend; ++i)//du debut a la fin du graph
    {
        cout << "cible : (" << i->second.second << ")" << endl << i->first << endl;
        cout << "\treferer : " << endl;
        for (Inner_cIterator j = i->second.first.begin(), jend = i->second.first.end(); j != jend; ++j)
        {
               cout << "\t- " << j->first << "(" << j->second << ")" << endl;
        }
    }
}

void GraphString::CreateGraphVizFile(string fileName)
// Algorithme :
//      1) Ouverture du flux
//      2) Ecriture du début du fichier
//      3) Ecriture du graphe
//      4) Ecriture de fin de fichier
//      5) Fermeture du flux
{
    // 1) Ouverture du flux
    ofstream graphFileStream;
    graphFileStream.open(fileName);
    if (graphFileStream.good())
    {
        
    }
    
    // 2) Ecriture du début du fichier
    
    
    // 3) Ecriture du graphe
    // 4) Ecriture de fin de fichier
    
    // 5) Fermeture du flux
    graphFileStream.close();

} // Fin de la méthode CreateGraphVizFile

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
GraphString::GraphString ( const GraphString & unGraphString )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <GraphString>" << endl;
#endif
} //----- Fin de GraphString (constructeur de copie)


GraphString::GraphString ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <GraphString>" << endl;
#endif
} //----- Fin de GraphString


GraphString::~GraphString ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <GraphString>" << endl;
#endif
} //----- Fin de ~GraphString


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
