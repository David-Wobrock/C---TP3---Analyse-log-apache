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
#include <cstdlib>
#include <map>
//------------------------------------------------------ Include personnel
#include "ApacheLogFileParser.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe
map<string, int> ApacheLogFileParser::months = {
  {"Jan", 0},
  {"Feb", 1},
  {"Mar", 2},
  {"Apr", 3},
  {"May", 4},
  {"Jun", 5},
  {"Jul", 6},
  {"Aug", 7},
  {"Sep", 8},
  {"Oct", 9},
  {"Nov", 10},
  {"Dec", 11},
};

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool ApacheLogFileParser::IsGood() const
{
	return good;
} // ----- Fin de la Méthode IsGood()

bool ApacheLogFileParser::GetLine(struct LogLine* const structLine)
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
                    //test regex ?
                    // IP Client
                    size_t deb = 0;
                    size_t fin = sLine.find(" ");
                    structLine->ll_ipClient = sLine.substr(deb, fin-deb);
                    // Userlog
                    deb = fin+1;    //on passe l'espace trouvé
                    fin = sLine.find(" ", deb);
                    structLine->ll_userLog = sLine.substr(deb, fin-deb);
                    // AuthenticatedUser
                    deb = fin+1;    // on passe l'espace
                    fin = sLine.find(" ", deb);
                    structLine->ll_authenticatedUser = sLine.substr(deb, fin-deb);

                    deb = fin+2;    // on passe l'espace et le crochet ouvrant
                    fin = sLine.find("/", deb);
                    structLine->ll_timeRequest.tm_mday = atoi(sLine.substr(deb, fin-deb).c_str());
                    deb = fin+1;
                    fin = sLine.find("/", deb);
                    structLine->ll_timeRequest.tm_mon = months[sLine.substr(deb, fin-deb)];
                    deb = fin+1;
                    fin = sLine.find(":", deb);
                    structLine->ll_timeRequest.tm_year = atoi(sLine.substr(deb, fin-deb).c_str()) - 1900;
                    deb = fin+1;
                    fin = sLine.find(":", deb);
                    structLine->ll_timeRequest.tm_hour = atoi(sLine.substr(deb, fin-deb).c_str());
                    deb = fin+1;
                    fin = sLine.find(":", deb);
                    structLine->ll_timeRequest.tm_min = atoi(sLine.substr(deb, fin-deb).c_str());
                    deb = fin+1;
                    fin = sLine.find(" ", deb);
                    structLine->ll_timeRequest.tm_sec = atoi(sLine.substr(deb, fin-deb).c_str());

                    deb = fin+1;
                    fin = sLine.find("]", deb);
                    structLine->ll_timeRequestGMT = sLine.substr(deb, fin-deb);

                    deb = fin+3;    // on passe le crochet fermant, l'espace et les doubles quotes
                    fin = sLine.find(" ", deb);
                    structLine->ll_method = sLine.substr(deb, fin-deb);

                    deb = fin+1;    // on passe l'espace
                    fin = sLine.find(" ", deb);
                    structLine->ll_url = sLine.substr(deb, fin-deb);

                    deb = fin+1;    // on passe l'espace
                    fin = sLine.find("\"", deb);
                    structLine->ll_httpVersion = sLine.substr(deb, fin-deb);

                    deb = fin+2;    // on passe les doubles quotes et l'espace
                    fin = sLine.find(" ", deb);
                    structLine->ll_status = atoi(sLine.substr(deb, fin-deb).c_str());

                    deb = fin+1;    // on passe l'espace
                    fin = sLine.find(" ", deb);
                    structLine->ll_dataSize = atoi(sLine.substr(deb, fin-deb).c_str());

                    deb = fin+2;    // on passe l'espace et les doubles quotes
                    fin = sLine.find("\"", deb);
                    structLine->ll_referer = sLine.substr(deb, fin-deb);

                    deb = fin+3;    // on passe les doubles quotes, l'espace et les doubles quotes
                    fin = sLine.find("\"", deb);
                    structLine->ll_browserIdentification = sLine.substr(deb, fin-deb);

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

string ApacheLogFileParser::GetLastError() const
{
	return "ERREUR : " + lastError;
} // ----- Fin de la Méthode GetLastError()


//-------------------------------------------- Constructeurs - destructeur
ApacheLogFileParser::ApacheLogFileParser(const string File)
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
