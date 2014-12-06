/*************************************************************************
                           GraphString  -  description
                             -------------------
    début                : 05/12/2014
    copyright            : (C) 2014 par Loïc Touzard et David Wobrock
*************************************************************************/

//---------- Interface de la classe <GraphString> (fichier GraphString.h) ------
#if ! defined ( GRAPHSTRING_H )
#define GRAPHSTRING_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//------------------------------------------------------------------------
// Rôle de la classe <GraphString>
//
//
//------------------------------------------------------------------------

class GraphString
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    GraphString & operator = ( const GraphString & unGraphString );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    GraphString ( const GraphString & unGraphString );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    GraphString ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~GraphString ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégées
private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <GraphString>

#endif // GRAPHSTRING_H
