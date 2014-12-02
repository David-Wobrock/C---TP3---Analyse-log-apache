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
	return this->good;
} // ----- Fin de la Méthode IsGood()

bool ApacheLogFileParser::GetLine(struct LogLine)
{

} // ----- Fin de la Méthode GetLine()

string ApacheLogFileParser::GetLastError()
{
	return lastError;
} // ----- Fin de la Méthode GetLastError()


//-------------------------------------------- Constructeurs - destructeur
ApacheLogFileParser::ApacheLogFileParser(string LogFile)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ApacheLogFileParser>" << endl;
#endif
} //----- Fin de ApacheLogFileParser


ApacheLogFileParser::~ApacheLogFileParser( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ApacheLogFileParser>" << endl;
#endif
} //----- Fin de ~ApacheLogFileParser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
void ApacheLogFileParser::setLastError(string msg)
{
	this->lastError = "ERROR : " + msg;
}