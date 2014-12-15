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
typedef map<string, int> Inner_map; // Map interne, contenant le referer et son nombre de liens
typedef pair<Inner_map, int> Inner_pair; // La paire interne, contenant une map interne et le nombre d'accès à la cible
typedef map<string, Inner_pair> Outer_map; // Map externe, contenant la cible et une paire interne associée


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

void GraphString::Insert(const string referer, const string target)
{
    if(graph.find(target) != graph.end())
    {
        // La clé existe
        Inner_pair* currentPair = &graph[target];
        Inner_map* currentInnerMap = &currentPair->first;
        currentPair->second++;// on incrémente le compteur de liens totaux
        (*currentInnerMap)[referer]++;
    }
    else
    {
        // La clé n'existe pas, on la créée
        Inner_map newMap;
        newMap[referer] = 1;
        Inner_pair newPair(newMap, 1);
        graph[target] = newPair;
    }
}


int GraphString::GetLinks(const string referer, const string target)
{
    return graph[target].first[referer];
}

int GraphString::GetAllLinks(const string target)
{
    return graph[target].second;
}

void GraphString::Display() const
{
    for(Outer_cIterator i = graph.begin(), iend = graph.end(); i != iend; ++i)//du debut a la fin du graph
    {
        cout << "Cible : (" << i->second.second << ")" << endl << i->first << endl;
        cout << "\tReferer : " << endl;
        for (Inner_cIterator j = i->second.first.begin(), jend = i->second.first.end(); j != jend; ++j)
        {
               cout << "\t- " << j->first << "(" << j->second << ")" << endl;
        }
    }
}

void GraphString::CreateGraphVizFile(const string fileName)
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
            graphFileStream << "\"" << innerIt->first << "\" ";
            graphFileStream <<"->";
            graphFileStream << " \"" << outerIt->first << "\" ";
            graphFileStream << "[label=\"" << innerIt->second << "\"];" << endl;
            
        }
    }
    
    // 4) Ecriture de fin de fichier
    graphFileStream << "}" << endl;
    // 5) Fermeture du flux
    graphFileStream.close();
    cout << "Dot-file " << fileName << " generated" << endl;
    
} // ----- Fin de la méthode CreateGraphVizFile

set<pair<string, int>, compareVisitedLinks> GraphString::GetMostVisited(const unsigned int numberOfLinks) const
{
    set<pair<string, int>, compareVisitedLinks> mostVisitedLinks;
    
    if (numberOfLinks == 0)
    {
        return mostVisitedLinks;
    }
    
    // Parcours de tous les liens
    Outer_cIterator outerIt;
    Outer_cIterator outerItEnd = graph.end();
    for (outerIt = graph.begin(); outerIt != outerItEnd; ++outerIt)
    {
        // S'il y a encore de la place dans l'ensemble
        if (mostVisitedLinks.size() < numberOfLinks)
        {
            mostVisitedLinks.insert(pair<string, int>(outerIt->first, outerIt->second.second));
        }
        else
        {
            // Sinon, on place un itérateur sur le dernier élément (étant le moins populaire, car l'ensemble est trié par ordre décroissant)
            set<pair<string, int>, compareVisitedLinks>::const_iterator i = mostVisitedLinks.begin();
            advance(i, numberOfLinks-1);
            
            // Si la cible actuelle est plus populaire que le dernier élément de l'ensemble, on le remplace
            if (outerIt->second.second > i->second)
            {
                mostVisitedLinks.erase(i);
                mostVisitedLinks.insert(pair<string, int>(outerIt->first, outerIt->second.second));
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
