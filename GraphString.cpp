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
            // le lien n'existe pas, on l'insere
            (*currentInnerMap)[referer]++;
        }

    }
    else
    {
        //la clé n'existe pas, on la créée
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
    if (!graphFileStream.good())
    {
        cerr << "Erreur ouverture fichier graphe (GraphString::CreateGraphVizFile)" << endl;
        return;
    }
    
    // 2) Ecriture du début du fichier
    graphFileStream << "digraph {" << endl;
    
    // 3) Ecriture du graphe
    Outer_cIterator outerIt;
    Outer_cIterator itOuterEnd = Outer_end();
    Inner_cIterator innerIt;
    for (outerIt = Outer_begin(); outerIt != itOuterEnd; ++outerIt)
    {
        // First : target string
        // Second : pair<map, int>
        Inner_cIterator itInnerEnd = outerIt->second.first.end();
        for (innerIt = outerIt->second.first.begin(); innerIt != itInnerEnd; ++innerIt)
        {
            // First : referer string
            // Second : links
            graphFileStream << "\"" << outerIt->first << "\" ";
            graphFileStream <<"->";
            graphFileStream << " \"" << innerIt->first << "\" ";
            graphFileStream << "[label=\"" << innerIt->second << "\"];" << endl;
            
        }
    }
    
    // 4) Ecriture de fin de fichier
    graphFileStream << "}" << endl;
    // 5) Fermeture du flux
    graphFileStream.close();
    cout << "Dot-file " << fileName << " generated" << endl;
    
} // ----- Fin de la méthode CreateGraphVizFile

multimap<int, string, greater<int>> GraphString::GetMostVisited(int numberOfLinks)
{
    // Fonction de comparaison pour ordre décroissant
    multimap<int, string, greater<int>> mostVisitedLinks;
    int lowestValue = 0;
    
    Outer_cIterator outerIt;
    Outer_cIterator itOuterEnd = Outer_end();
    for (outerIt = Outer_begin(); outerIt != itOuterEnd; ++outerIt)
    {
        if (outerIt->second.second >= lowestValue)
        {
            if (mostVisitedLinks.size() > numberOfLinks)
            {
                // On trouve le lien avec le moins de visite
                bool hasIterated = false;
                multimap<int, string, greater<int>>::const_iterator it, lowestPair;
                multimap<int, string, greater<int>>::const_iterator itEnd = mostVisitedLinks.end();
                for(it = mostVisitedLinks.begin(); it != itEnd; ++it)
                {
                    if (!hasIterated || it->first < lowestPair->first)
                    {
                        hasIterated = true;
                        lowestPair = it;
                    }
                }
                // Suppresion de l'élément
                mostVisitedLinks.erase(lowestPair);
            }
            // Ajout du nouveau lien
            mostVisitedLinks.insert(pair<int, string>(outerIt->second.second, outerIt->first));
            
            // Update lowest value
            multimap<int, string, greater<int>>::const_iterator it;
            multimap<int, string, greater<int>>::const_iterator itEnd = mostVisitedLinks.end();
            for(it = mostVisitedLinks.begin(); it != itEnd; ++it)
            {
                lowestValue = ((it->first < lowestValue) ? it->first : lowestValue);  
            }
        }
    }
    
    return mostVisitedLinks;
} // ----- Fin de la méthode GetMostVisited

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
