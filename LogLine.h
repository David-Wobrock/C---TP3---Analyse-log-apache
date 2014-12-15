/*************************************************************************
                           LogLine  -  Description
                             -------------------
    début                : 28/11/2014
    copyright            : (C) 2014 par Loïc Touzard et David Wobrock
*************************************************************************/

//---------- Interface de la structure <LogLine> (fichier LogLine.h) ------
#if ! defined ( LOGLINE_H )
#define LOGLINE_H

//--------------------------------------------------- Interfaces utilisées
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

//------------------------------------------------------------- Constantes


//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogLine>
//	Structure permettant le stockage d'une ligne de log d'une requête apache sous différentes données
//
//------------------------------------------------------------------------

struct LogLine
{
//----------------------------------------------------------------- PUBLIC
//------------------------------------------------------- Attributs publics
	// Partie distinctes d'un log, réparties :

        string ll_ipClient;				// Adresse IP du client émmetteur de la requête
	string ll_userLog;				// User Logname, le nom d'utilisateur du visiteur
	string ll_authenticatedUser;                    // Authenticated User, nom de l'utilisateur qu'il s'est lui-même donné
	struct tm ll_timeRequest;			// Représentation en structure tm de la date et heure de la requête
	string ll_timeRequestGMT;                       // GMT de la requete, différence par rapport à l'heure de Greenwich
	string ll_method;				// Méthode ou type d'action utilisée (GET, POST, OPTIONS, etc.)
	string ll_url;					// URL du document demandé, cible de notre requête
	string ll_httpVersion;				// Version HTTP de la requête
	int ll_status;					// Code de retour, statut de la requête
	int ll_dataSize;				// Taille en octet de la réponse, quantité de données tranférées au serveur distant
	string ll_referer;				// Referer, adresse d'où provient la requête
	string ll_browserIdentification;                // Identification de la version et du type du navigateur du client
};


#endif // LOGLINE_H
