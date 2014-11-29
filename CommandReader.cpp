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
        cout << errorMessage << endl;
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
    parameters = new map<string, string>;
    isGood = false;
    
    bool hasFoundLogFile = false;
            
    for (int i = 1; i < argc; ++i)
    {
        string arg = string(argv[i]);
        
        // Si l'argument ne commence pas par un tiret, c'est le nom du fichier de log
        if (arg[0] != '-')
        {
            if (hasFoundLogFile)
            {
                errorMessage = "Plus d'un fichier de log apache a été détecté.";
                isGood = false;
                break;
            }
            // Le nom du fichier doit au moins faire 5 (a.log par exemple)
            if (arg.size() < 5)
            {
                errorMessage = "Le nom du fichier log apache est trop court.";
                isGood = false;
                break;  
            }
            // Vérification de l'extension (.txt ou .log)
            string argExtension = arg.substr(arg.size()-4, arg.size());
            if (argExtension != ".txt" && argExtension != ".log")
            {
                errorMessage = "L'extension du fichier de log apache est invalide.";
                isGood = false;
                break;
            }
                
            isGood = true;
            hasFoundLogFile = true;
            parameters->insert(pair<string, string>(arg, ""));
        }
        // Si l'argument a un tiret
        else
        {
            
        }
        // si après un truc avec un tiret avec lequel on attend une suite
        
        // Si après un truc avec un tiret on attend rien
    }
    
    
    // TODO : Faire analyse de la ligne de commande + remplissage erreur + isGood 
    /*
    def trait_arg(argv):
	saisie={}
	argIdx = 0
	nbitems=len(argv)
	for argItem in argv:

		if argItem.find('-',0,1) != -1 and argIdx +1 < nbitems and argv[argIdx+1].find('-',0,1) == -1:
			# on recherche les paramètres commençant par un moins.
			# si ils sont suivis par un autre paramètre ne commençant pas
			# par un moins, on associe le paramètre suivant a ce paramètre.
			saisie[argItem]=argv[argIdx+1]
		elif argItem.find('-',0,1) != -1 and argIdx +1 < nbitems and argv[argIdx+1].find('-',0,1) == 0:
			saisie[argItem]=''
		elif argItem.find('-',0,1) != -1 and argIdx +1 >= nbitems:
			saisie[argItem]=''
	
		argIdx += 1
	return saisie
    */
} //----- Fin de CommandReader


CommandReader::~CommandReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandReader>" << endl;
#endif
    
    delete parameters;
} //----- Fin de ~CommandReader


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void CommandReader::displayHelp() const
{
    cout << "Help syntaxe" << endl;
} //---- Fin de la méthode displayHelp

//------------------------------------------------------- Méthodes privées
