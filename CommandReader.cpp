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
#include <set>
#include <stdlib.h>

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
    
    set<string> optionWithoutArgs = {"-x"};
    bool hasFoundLogFile = false;
    bool hasTriedToFindLogFile = false;
            
    for (int i = 1; i < argc; ++i)
    {
        string arg = string(argv[i]);
        
        // Si l'argument ne commence pas par un tiret, c'est le nom du fichier de log
        if (arg[0] != '-')
        {
            hasTriedToFindLogFile = true;
            
            if (hasFoundLogFile)
            {
                setError("Plus d'un fichier de log apache a été détecté.");
                break;
            }
            // Le nom du fichier doit au moins faire 5 (a.log par exemple)
            if (arg.size() < 5)
            {
                setError("Le nom du fichier log apache est trop court.");
                break;  
            }
            // Vérification de l'extension (.txt ou .log)
            string argExtension = arg.substr(arg.size()-4, arg.size());
            if (argExtension != ".txt" && argExtension != ".log")
            {
                setError("L'extension du fichier de log apache est invalide.");
                break;
            }
                
            isGood = true;
            hasFoundLogFile = true;
            insertParameters(arg, "");
        }
        // Si l'argument a un tiret
        else
        {
            // S'il n'y que un tiret
            if (arg.size() < 2)
            {
                setError("L'option a besoin d'un nom après le tiret.");
                break;
            }
            
            // Si c'est une option qui n'a pas besoin d'argument
            if (optionWithoutArgs.find(arg) != optionWithoutArgs.end())
            {
                insertParameters(arg, "");
            }
            // Si c'est une option qui a besoin d'un argument
            else
            {
                // S'il n'y a pas d'argument après (si c'est le dernier, ou celui ou le suivant commence par -)
                if (i+1 >= argc || argv[i+1][0] == '-')
                {
                    setError("Il manque l'argument après " + arg + ".");
                    break;
                }
                
                string argument = argv[i+1];
                
                // Cas spéciaux pour l'option -g
                if (arg == "-g")
                {
                    // Si l'argument est trop court
                    if (argument.size() < 5)
                    {
                        setError("L'argument de l'option -g est trop court.");
                        break;
                    }
                    // Si l'extension est invalide (.dot)
                    if (argument.substr(argument.size()-4, argument.size()) != ".dot")
                    {
                        setError("L'argument de l'option -g doit avoir l'extension .dot");
                        break;
                    }
                }
                
                // Cas spéciaux pour l'option -t
                if (arg == "-t")
                {
                    bool argIsDigit = true;
                    for (unsigned int i = 0; i < argument.size(); ++i)
                    {
                        if (!isdigit(argument[i]))
                        {
                            setError("L'argument de l'option -t n'est pas un entier.");
                            argIsDigit = false;
                            break;
                        }
                    }
                    
                    if (!argIsDigit)
                    {
                        break;
                    }
                    
                    int intArg = atoi(argument.c_str());
                    
                    if (intArg < 0 || 23 < intArg)
                    {
                        setError("L'argument de l'option -t n'est pas compris entre 0 et 23.");
                        break;
                    }
                    
                    insertParameters(arg, argument);
                }
                
                // ++i pour incrémenter d'abord prendre la valeur à i+1, puis la boucle for réincrémentera pour sauter le traitement de l'argument
                insertParameters(arg, string(argv[++i]));
            }
        }
    }
    
    if (!hasTriedToFindLogFile)
    {
        setError("Fichier de log apache manquant.");
    }
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
    cout << "Help syntaxe..." << endl;
} //---- Fin de la méthode displayHelp

void CommandReader::insertParameters(string key, string value)
{
    parameters->insert(pair<string, string>(key, value));
}

void CommandReader::setError(string message)
{
    errorMessage = message;
    isGood = false;
}

//------------------------------------------------------- Méthodes privées
