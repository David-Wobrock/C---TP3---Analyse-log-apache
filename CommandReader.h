/*************************************************************************
                           CommandReader  -  description
                             -------------------
    début                : 28/11/14
    copyright            : (C) 2014 par Loïc Touzard et David Wobrock
*************************************************************************/

//---------- Interface de la classe <CommandReader> (fichier CommandReader.h) ------
#if ! defined ( COMMANDREADER_H )
#define COMMANDREADER_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <string>

//------------------------------------------------------------- Constantes 
//#define MAP
//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandReader>
//
//
//------------------------------------------------------------------------ 

class CommandReader
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    bool IsGood();
    // Mode d'emploi :
    //  Renvoie VRAI si les arguments passés en paramètres sont corrects.
    //  Si le retour est FAUX, GetParameters() renverra un pointeur nul.
    //  Cette méthode affiche en plus un message d'erreur et un rappel de syntaxe si le retour est FAUX.
    // Contrat :
    //  
    
    std::map<std::string, std::string>* GetParameters();
    // Mode d'emploi :
    //  Nécessite d'appelé IsGood() avant pour savoir s'il y a une erreur.
    //  Si on appelle GetParameters() et qu'il y a une erreur, on se saura pas laquelle.
    //  Si tout s'est bien passé, cette méthode retourne des couples <"-option", "arg">
    //  Si on sait que l'option passée n'attend pas d'argument (comme -x par exemple, l'argument sera nul.
    // Contrat :
    //  
    
    CommandReader (int argc, char** argv);
    // Mode d'emploi :
    //  Construit un objet de lecture de la ligne de commande.
    //  Renseigne un attribut témoignant de la bonne écriture de la ligne de commande, et donc que l'instance est correcte.
    //  Cet attribut peut être consulté avec la méthode IsGood(). Il est fortement recommandé d'appeler cette méthode directement après le constructeur.
    // Contrat :
    //  

    virtual ~CommandReader ( );
    // Mode d'emploi :
    //  Détruit proprement l'instance de CommandReader.
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    void displayHelp() const;
    // Mode d'emploi :
    //  Affiche l'aide (et la syntaxe) de la commande analog.
    // Contrat :
    //
    
private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    bool isGood; // Renseigne l'état de l'instance
    std::map<std::string, std::string>* parameters; // Les paramètres passés sur la ligne de commande
    
    std::string errorMessage;
    
private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <CommandReader>

#endif // COMMANDREADER_H
