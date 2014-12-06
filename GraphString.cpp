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

//------------------------------------------------------ Include personnel
#include "GraphString.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type GraphString::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
GraphString & GraphString::operator = ( const GraphString & unGraphString )
// Algorithme :
//
{
} //----- Fin de operator =


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
