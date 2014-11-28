/*************************************************************************
                           CommandReader  -  description
                             -------------------
    début                : 28/11/14
    copyright            : (C) 14 par Loïc Touzard et David Wobrock
*************************************************************************/

//---------- Réalisation de la classe <CommandReader> (fichier CommandReader.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "CommandReader.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandReader::IsGood()
{
    if (isGood)
    {
        return isGood; // True
    }
    else
    {
        // affiche message d'erreur
        displayHelp();
        return isGood; // False
    }
    
} //----- Fin de la méthode IsGood

map<string, string>* CommandReader::GetParameters()
{
    if (!isGood)
    {
        return NULL;
    }
    
    return parameters;
} //----- Fin de la méthode GetParameters

CommandReader::CommandReader (int argc, char** argv)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandReader>" << endl;
#endif
    
    // TODO : Faire analyse de la ligne de commande + remplissage erreur + isGood 
    
} //----- Fin de CommandReader


CommandReader::~CommandReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandReader>" << endl;
#endif
    
    if (parameters != NULL)
    {
        delete parameters;
    }
    
} //----- Fin de ~CommandReader


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void CommandReader::displayHelp() const
{
    cout << "TODO" << endl;
} //---- Fin de la méthode displayHelp

//------------------------------------------------------- Méthodes privées
