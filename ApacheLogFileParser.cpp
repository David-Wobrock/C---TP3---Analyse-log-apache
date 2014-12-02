/*************************************************************************
                           ApacheLogFileParser  -  Description
                             -------------------
    d�but                : 29/11/2014
    copyright            : (C) 2014 par Lo�c Touzard et David Wobrock
*************************************************************************/

//---------- R�alisation de la classe <ApacheLogFileParser> (fichier ApacheLogFileParser.cpp) --

//---------------------------------------------------------------- INCLUDE
#include "LogLine.h"

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "ApacheLogFileParser.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types priv�s


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- M�thodes publiques
// type ${file_base}::M�thode ( liste de param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode

bool ApacheLogFileParser::IsGood()
{
	return good;
} // ----- Fin de la M�thode IsGood()

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
            lastError = "GetLine : Pointeur en param�tre = null";
            return false;
        }
    }
    else
    {
        //si bool est a false, le lastError aura d�j� �t� renseign�. Pas besoin de le mettre � jour
        return false;
    }
} // ----- Fin de la M�thode GetLine()

string ApacheLogFileParser::GetLastError()
{
	return "ERREUR : " + lastError;
} // ----- Fin de la M�thode GetLastError()


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

//----------------------------------------------------- M�thodes prot�g�es

//------------------------------------------------------- M�thodes priv�es
