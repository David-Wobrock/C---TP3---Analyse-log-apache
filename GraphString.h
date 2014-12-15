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
#include <map>
#include <set>

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef map<string, int> Inner_map; //map interne, contenant la cible et son nombre de liens
typedef pair<Inner_map, int> Inner_pair;
typedef map<string, Inner_pair> Outer_map;

// Structure de comparaison pour les statistiques : liens les plus visités
struct compareVisitedLinks
{
    bool operator() (const pair<string, int>& left, const pair<string, int>& right)
    {
        return left.second >= right.second;
    }
};


//------------------------------------------------------------------------
// Rôle de la classe <GraphString>
//  Représente un graphe de chaîne de caractères.
//
//------------------------------------------------------------------------

class GraphString
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    typedef Outer_map::iterator Outer_iterator;
    typedef Outer_map::const_iterator Outer_cIterator;
    typedef Inner_map::iterator Inner_iterator;
    typedef Inner_map::const_iterator Inner_cIterator;

    Outer_iterator Outer_begin() { return graph.begin(); }

    Outer_iterator Outer_end() { return graph.end(); }

    Inner_iterator Inner_begin(string k)  { return graph[k].first.begin(); }

    Inner_iterator Inner_end(string k)  { return graph[k].first.end(); }

    void Insert(const string referer, const string target);
    // Mode d'emploi :
    //  Ajoute un lien dans le graph, partant du referer vers la target

    int GetLinks(const string referer, const string target);
    // Mode d'emploi :
    //  renvoie le nombre de lien du graph allant du referrer à la targer

    int GetAllLinks(const string target);
    // Mode d'emploi :
    //  renvoie le nombre total de liens allant vers la target donnée

    void Display() const;

    void CreateGraphVizFile(const string fileName);
    // Mode d'emploi :
    //  Créer le fichier texte .dot au format GraphViz
    //  Ce fichier représente le graphe
    // Contrat :
    //  Paramètre nom de fichier non nul ni vide

    set<pair<string, int>, compareVisitedLinks> GetMostVisited(const unsigned int numberOfLinks) const;
    // Mode d'emploi : 
    //  Renvoie les "numberOfLinks" liens les plus visités dans l'ordre décroissant des visites
    //  Sous la forme <nomDuLien, nombreDeVisitesTotales>
    //  Si le nombre de liens à afficher est supérieur au nombre de liens existant dans le graphe, on affiche le maximum de liens possible
    // Contrat :
    //
    
//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
    GraphString ( const GraphString & unGraphString );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    GraphString ( );
    // Mode d'emploi :
    //  Instancie un objet GraphString, pas de particularité.
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
        Outer_map graph;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <GraphString>

#endif // GRAPHSTRING_H
