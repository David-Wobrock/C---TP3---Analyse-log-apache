/*************************************************************************
                           ApacheLogFileParser  -  Description
                             -------------------
    début                : 28/11/2014
    copyright            : (C) 2014 par Loïc Touzard et David Wobrock
*************************************************************************/

//---------- Interface de la classe <ApacheLogFileParser> (fichier ApacheLogFileParser.h) ------
#if ! defined ( APACHELOGFILEPARSER_H )
#define APACHELOGFILEPARSER_H

//--------------------------------------------------- Interfaces utilisées
#include "LogLine.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <ApacheLogFileParser>
//  ApacheLogFileParser peut ouvrir un fichier de log Apache (supposé bien formé)
//  Le fichier est associé à la classe
//  Cette classe lit ce fichier et renvoie son contenu ligne par ligne formaté dans un structure LogLine
//------------------------------------------------------------------------ 

class ApacheLogFileParser
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    bool IsGood();
    // Mode d'emploi :
    //  Renvoie un booleen pour connaître l'etat du fichier de log
    //      - true : Le fichier existe, est lisible, ouvert correctement.
    //      - false : Il y a eu un problème avec le fichier. Ce problème n'est pas renseigné ici.

    bool GetLine(struct LogLine *line);
    // Mode d'emploi : 
    //  Lit une ligne du fichier de log.
    //  Remplit la structure LogLine avec son contenu
    //  Le prochain appel a là fonction lira la ligne suivante
    //  La fonction renvoie un code de retour :
    //      - true : tout s'est bien passé, la ligne a été lue correctement
    //      - false :  il y a eu une erreur dans la lecture de la ligne, la structure LogLine n'a pas été modifiée
    //  L'erreur est renseignée dans la classe et peut être affichée par GetLastError();
    //
    // Contrat :
    //  Le pointeur de structure passé en paramètre est supposé non null.

    string GetLastError();
    // Mode d'emploi : 
    //  Renvoie une string contenant une explication sur la dernière erreur survenue dans la Classe


//-------------------------------------------- Constructeurs - destructeur
    ApacheLogFileParser (string logFile);
    // Mode d'emploi :
    //  Construit le parser sur le fichier passé en paramètre.
    //  Une ouverture du fichier en lecture est tentée dans le constructeur.
    //  Si une erreur survient le parser se construit mais ne pourra pas lire le fichier, sa methode IsGood() renverra donc false.
    //  Différentes erreurs sont possible :
    //      - Si le fichier n'est pas accessible ou lisible
    //      - Si le fihier ne fini pas par .txt ou .log
    // L'erreur est renseignée dans la classe et peut être affichée par GetLastError();

    virtual ~ApacheLogFileParser ( );
    // Mode d'emploi :
    //  Détruit la classe et referme le fichier de log potentiellement ouvert

//------------------------------------------------------------------ PRIVE 

private:
//------------------------------------------------------- Méthodes privées
    void setLastError(string msg = "ERROR : ");
    // Mode d'emploi : 
    //  Met a jour la variable contenant la dernière erreur survenue dans la classe
    //  Ecrase l'ancienne valeur

protected:
//----------------------------------------------------- Attributs protégés
    /**** TODO *****/
    string lastError;


};


#endif // APACHELOGFILEPARSER_H
