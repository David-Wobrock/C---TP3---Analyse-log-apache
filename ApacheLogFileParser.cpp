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
	return this->good;
} // ----- Fin de la M�thode IsGood()

bool ApacheLogFileParser::GetLine(struct LogLine)
{

} // ----- Fin de la M�thode GetLine()

string ApacheLogFileParser::GetLastError()
{
	return lastError;
} // ----- Fin de la M�thode GetLastError()


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

//----------------------------------------------------- M�thodes prot�g�es

//------------------------------------------------------- M�thodes priv�es
void ApacheLogFileParser::setLastError(string msg)
{
	this->lastError = "ERROR : " + msg;
}