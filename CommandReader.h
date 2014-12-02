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
//  Interpréteur de la ligne commande passée avec le programme analog
//  Affiche les messages d'erreur et la syntaxe si une erreur est détectée 
//  Affiche la page d'aide (man) si celle-ci est demandée (par l'option -h) 
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
    //  Les paramètres passés sont ceux qui sont passés à la fonction d'entrée du programme : main()

    virtual ~CommandReader ( );
    // Mode d'emploi :
    //  Détruit proprement l'instance de CommandReader.
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    bool insertParameters(std::string key, std::string value);
    // Mode d'emploi :
    //  Insert une paire de chaînes de caractères dans la structure de données de l'interpréteur.
    //  Renvoie false si l'ajout n'a pas pu être effectué = option déjà présent dans la strucuture.
    // Contrat :
    //
    
    void setError(std::string message);
    // Mode d'emploi :
    //  Met l'interpréteur de ligne de commande dans un état d'erreur.
    //  Met à jour le booléen isGood et le message d'erreur avec le paramètre.
    // Contrat :
    //  
    
    void displayHelp() const;
    // Mode d'emploi :
    //  Affiche l'aide (la page de man) de la commande analog.
    // Contrat :
    //
    
    void displaySyntaxe();
    // Mode d'emploi :
    //  Affiche un rappel de la syntaxe de la commande analog
    // Contrat :
    //  
    
private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    bool isGood; // Renseigne l'état de l'instance
    std::map<std::string, std::string>* parameters; // Les paramètres passés sur la ligne de commande
    
    std::string errorMessage; // Message d'erreur à afficher
    
private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <CommandReader>

#endif // COMMANDREADER_H
