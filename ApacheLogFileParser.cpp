/*************************************************************************
                           ApacheLogFileParser  -  Description
                             -------------------
    début                : 29/11/2014
    copyright            : (C) 2014 par Loïc Touzard et David Wobrock
*************************************************************************/

//---------- Réalisation de la classe <ApacheLogFileParser> (fichier ApacheLogFileParser.cpp) --

//---------------------------------------------------------------- INCLUDE
#include "LogLine.h"

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "ApacheLogFileParser.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type ${file_base}::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

bool ApacheLogFileParser::IsGood()
{
	return good;
} // ----- Fin de la Méthode IsGood()

bool ApacheLogFileParser::GetLine(struct LogLine * structLine)
{
    if(good)
    {
        if(structLine != NULL){
            if(!logFile.eof())
            {
                char cLine[1024];
                if(logFile.getline(cLine, 1024))
                {
                    string sLine(cLine);
                    cout << sLine << endl;
                    return true;
                }
                else
                {
                    good = false;
                    lastError = "GetLine : Erreur lors de la lecture de la ligne";
                    return false;
                }
            }
            else
            {
                good = false;
                lastError = "GetLine : Fin du fichier atteinte";
                return false;
            }

        }
        else
        {
            lastError = "GetLine : Pointeur en paramètre = null";
            return false;
        }
    }
    else
    {
        //si bool est a false, le lastError aura déjà été renseigné. Pas besoin de le mettre à jour
        return false;
    }
} // ----- Fin de la Méthode GetLine()

string ApacheLogFileParser::GetLastError()
{
	return "ERREUR : " + lastError;
} // ----- Fin de la Méthode GetLastError()


//-------------------------------------------- Constructeurs - destructeur
ApacheLogFileParser::ApacheLogFileParser(string File)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ApacheLogFileParser>" << endl;
#endif
    logFile.open(File);
    if(logFile.is_open())
    {
        good = true;
    }
    else
    {
        lastError="Constructeur : Ouverture du fichier impossible.";
        good = false;
    }
} //----- Fin de ApacheLogFileParser


ApacheLogFileParser::~ApacheLogFileParser( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ApacheLogFileParser>" << endl;
#endif
    if(logFile.is_open())
    {
        logFile.close();
    }
} //----- Fin de ~ApacheLogFileParser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
