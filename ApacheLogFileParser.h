/*************************************************************************
                           ApacheLogFileParser  -  Description
                             -------------------
    d�but                : 28/11/2014
    copyright            : (C) 2014 par Lo�c Touzard et David Wobrock
*************************************************************************/

//---------- Interface de la classe <ApacheLogFileParser> (fichier ApacheLogFileParser.h) ------
#if ! defined ( APACHELOGFILEPARSER_H )
#define APACHELOGFILEPARSER_H

//--------------------------------------------------- Interfaces utilis�es
#include "LogLine.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <ApacheLogFileParser>
//  ApacheLogFileParser peut ouvrir un fichier de log Apache (suppos� bien form�)
//  Le fichier est associ� � la classe
//  Cette classe lit ce fichier et renvoie son contenu ligne par ligne format� dans un structure LogLine
//------------------------------------------------------------------------ 

class ApacheLogFileParser
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    bool IsGood();
    // Mode d'emploi :
    //  Renvoie un booleen pour conna�tre l'etat du fichier de log
    //      - true : Le fichier existe, est lisible, ouvert correctement.
    //      - false : Il y a eu un probl�me avec le fichier. Ce probl�me n'est pas renseign� ici.

    bool GetLine(struct LogLine *line);
    // Mode d'emploi : 
    //  Lit une ligne du fichier de log.
    //  Remplit la structure LogLine avec son contenu
    //  Le prochain appel a l� fonction lira la ligne suivante
    //  La fonction renvoie un code de retour :
    //      - true : tout s'est bien pass�, la ligne a �t� lue correctement
    //      - false :  il y a eu une erreur dans la lecture de la ligne, la structure LogLine n'a pas �t� modifi�e
    //  L'erreur est renseign�e dans la classe et peut �tre affich�e par GetLastError();
    //
    // Contrat :
    //  Le pointeur de structure pass� en param�tre est suppos� non null.

    string GetLastError();
    // Mode d'emploi : 
    //  Renvoie une string contenant une explication sur la derni�re erreur survenue dans la Classe


//-------------------------------------------- Constructeurs - destructeur
    ApacheLogFileParser (string logFile);
    // Mode d'emploi :
    //  Construit le parser sur le fichier pass� en param�tre.
    //  Une ouverture du fichier en lecture est tent�e dans le constructeur.
    //  Si une erreur survient le parser se construit mais ne pourra pas lire le fichier, sa methode IsGood() renverra donc false.
    //  Diff�rentes erreurs sont possible :
    //      - Si le fichier n'est pas accessible ou lisible
    //      - Si le fihier ne fini pas par .txt ou .log
    // L'erreur est renseign�e dans la classe et peut �tre affich�e par GetLastError();

    virtual ~ApacheLogFileParser ( );
    // Mode d'emploi :
    //  D�truit la classe et referme le fichier de log potentiellement ouvert

//------------------------------------------------------------------ PRIVE 

private:
//------------------------------------------------------- M�thodes priv�es
    void setLastError(string msg = "ERROR : ");
    // Mode d'emploi : 
    //  Met a jour la variable contenant la derni�re erreur survenue dans la classe
    //  Ecrase l'ancienne valeur

protected:
//----------------------------------------------------- Attributs prot�g�s
    /**** TODO *****/
    string lastError;


};


#endif // APACHELOGFILEPARSER_H
