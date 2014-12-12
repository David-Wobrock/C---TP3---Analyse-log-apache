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
const string CommandReader::LOG_FILE_NAME_KEY = "LOG_FILE_NAME"; // Constante de classe
//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandReader::IsGood() const
{
    if (isGood)
    {
        return isGood; // True
    }
    else
    {
        if (errorMessage != "")
        {
            cerr << errorMessage << endl;
            displaySyntaxe();
        }
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

//-------------------------------------------- Constructeurs - destructeur
CommandReader::CommandReader (const int argc, char** const argv)
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandReader>" << endl;
#endif
    // Initialisation des attributs
    CommandReader::setError("");
    parameters = new map<string, string>;
    
    // Si les arguments contiennent -h, on affiche l'aide et on ne fait rien d'autre.
    if (argContains(argc, argv, "-h"))
    {
        displayHelp();
    }
    // Sinon on analyse la ligne de commande, ce qui remplit 
    else
    {
        analyzeCommand(argc, argv);
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
bool CommandReader::insertParameters(const string key, const string value)
{
    // Insert renvoie un itérateur sur un élémont dont la valeur (second) est un booléen
    // Vrai si une nouvelle paire a été insérée
    // Faux si la clé est déjà existante
    return parameters->insert(pair<string, string>(key, value)).second;
}

void CommandReader::setError(const string message)
{
    errorMessage = message;
    isGood = false;
}

bool CommandReader::argContains(const int argc, char** const argv, const string searchedArg)
{
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == searchedArg)
        {
            return true;
        }
    }
    
    return false;
}

void CommandReader::analyzeCommand(const int argc, char** const argv)
{
    set<string> optionWithoutArgs = {"-x", "-i", "-o"};
    bool hasFoundLogFile = false;
    bool hasTriedToFindLogFile = false;

    for (int i = 1; i < argc; ++i)
    {
        string arg = string(argv[i]);

        // ***** Si l'argument ne commence pas par un tiret, c'est le nom du fichier de log ***** //
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
            insertParameters(CommandReader::LOG_FILE_NAME_KEY, arg);
        }
        
        // ***** Si l'argument a un tiret ***** //
        else
        {
            // S'il n'y que un tiret
            if (arg.size() < 2)
            {
                setError("L'option a besoin d'un nom après le tiret.");
                break;
            } 

            // ***** Si c'est une option qui n'a pas besoin d'argument ***** //
            if (optionWithoutArgs.find(arg) != optionWithoutArgs.end())
            {
                if (!insertParameters(arg, ""))
                {
                    setError("L'argument " + arg + " est présent plus d'une fois.");
                    break;
                }
            }
            
            // ***** Si c'est une option qui a besoin d'un argument ***** //
            else
            {
                // S'il n'y a pas d'argument après (si c'est le dernier, ou celui ou le suivant commence par -)
                if (i+1 >= argc || argv[i+1][0] == '-')
                {
                    setError("Il manque l'argument après " + arg + ".");
                    break;
                }

                string argument = argv[i+1];

                // ** Cas spéciaux pour l'option -g ** //
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
                        setError("L'argument de l'option -g doit avoir l'extension .dot.");
                        break;
                    }
                }

                // ** Cas spéciaux pour l'option -t ** //
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
                }
                
                // ** Cas spéciaux pour l'option -l ** //
                if (arg == "-l")
                {
                    bool argIsDigit = true;
                    for (unsigned int i = 0; i < argument.size(); ++i)
                    {
                        if (!isdigit(argument[i]))
                        {
                            setError("L'argument de l'option -l n'est pas un entier.");
                            argIsDigit = false;
                            break;
                        }
                    }

                    if (!argIsDigit)
                    {
                        break;
                    }

                    int intArg = atoi(argument.c_str());

                    if (intArg < 0)
                    {
                        setError("L'argument de l'option -t doit être supérieur ou égal à 0.");
                        break;
                    }
                }

                // Insertion de l'option avec son paramètre. On incrémente ensuite pour sauter l'argument.
                if (!insertParameters(arg, argument))
                {
                    setError("L'argument " + arg + " est présent plus d'une fois.");
                    break;
                }
                i++;
            }
        }
    }

    if (!hasTriedToFindLogFile)
    {
        setError("Fichier de log apache manquant.");
    }
}

void CommandReader::displayHelp() const
{
    cout << "\t***** Aide du programme analog *****";
    
    cout << endl << "NOM" << endl;
    cout << "\tanalog - analise un fichier de log apache" << endl;
    
    cout << endl << "SYNOPSIS" << endl;
    cout << "\tanalog [OPTION] FICHIERLOG" << endl;
    
    cout << endl << "DESCRIPTION" << endl;
    cout << "\tAffiche sur la sortie standard les dix documents les plus visités, par ordre décroissant." << endl;
    cout << "\tLe FICHIERLOG doit se terminer par l'extension .log ou .txt." << endl;
    cout << "\tLes arguments peuvent être écrit dans n'importe quel ordre." << endl;
    
    
    cout << endl << "\tOPTION :" << endl;
    
    cout << "\t-h" << endl;
    cout << "\t\tAffiche l'aide du programme analog." << endl;
    
    cout << "\t-x" << endl;
    cout << "\t\tIgnore les documents qui ont une extension de type image, css ou javascript." << endl;
    cout << "\t\tListe complète des extensions ignorées :" << endl;
    cout << "\t\t\t.css, .js, .png, .jpg, .jpeg, .bmp, .gif, .svg, .ico" << endl;
    
    cout << endl << "\t-g FICHIERGRAPH" << endl;
    cout << "\t\tGénère un fichier FICHIERGRAPH au format GraphViz. Ce document contient tous les noeuds et arcs, ainsi que le nombre de parcours." << endl;
    cout << "\t\tFICHIERGRAPH doit se finir par .dot." << endl;
    cout << "\t\tSi FICHIERGRAPH existe, il est écrasé et remplacé par le nouveau fichier." << endl;
    
    cout << endl << "\t-t HEURE" << endl;
    cout << "\t\tLe programme ne prend que en compte les hits effectue dans l'intervalle de HEURE à HEURE+1." << endl;
    cout << "\t\tHEURE est un entier compris entre 0 et 23 (inclus)." << endl;
    
    cout << endl << "\t-i" << endl;
    cout << "\t\tMode interne. Le programme n'affiche que les navigations internes du site web. Les accès depuis l'extérieur ou autres seront inutiles." << endl;
    
    cout << endl << "\t-o" << endl;
    cout << "\t\tOpen. Génere l'image (en format .png) correspondant au graphe obtenu par l'option -g, et l'affiche." << endl;
    cout << "\t\tNécessite que l'utilitaire 'dot' et 'shotwell' soit installés sur le poste de travail." << endl;
    cout << "\t\tCette option sera ignorée si l'option -g n'est pas présente." << endl;
    cout << "\t\tLa génération d'image peut devenir longue selon la taille du graphe généré." << endl;
    
    cout << endl << "\t-l [NBLINKS=10]" << endl;
    cout << "\t\tAffiche les NBLINKS liens les plus visités sur le site." << endl;
    cout << "\t\tNBLINKS doit être supérieur ou égale à 0. Par défaut, celui-ci est à 10." << endl;
    
            
    cout << endl << "AUTHOR" << endl;
    cout << "\tEcrit par Loïc Touzard et David Wobrock (2014)" << endl;
} //---- Fin de la méthode DisplayHelp

void CommandReader::displaySyntaxe() const
{
    cerr << "./analog FICHIERLOG [-g FICHIERGRAPH] [-t HEURE] [-l NBLIENS=10] [-x] [-i] [-s] [-o]" << endl;
}

//------------------------------------------------------- Méthodes privées
