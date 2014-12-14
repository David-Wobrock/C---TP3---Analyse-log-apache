#include <iostream>
#include <cstdlib>
#include <set>

#include "CommandReader.h"
#include "ApacheLogFileParser.h"
#include "LogLine.h"
#include "GraphString.h"

using namespace std;

// Prototypes
void AnalogGraphe   (ApacheLogFileParser& apacheParser,
                    map<string, string>* parameters,
                    map<string, string>::const_iterator itOptionGraphe);
void Analog(ApacheLogFileParser& apacheParser, map<string, string>* parameters);
string CleanURL(string url);
bool CorrectExtension(string s);
void DisplayMostVisitedSet(set<pair<string, int>, compareVisitedLinks>& visitedLinks);
bool IsLocal(string url);

//Constantes
const string LOCAL_URL = "http://intranet-if";  //Addresse locale de l'intranet, à enlever
// peut par exemple être    http://intranet-if:90/
// ou                       http://intranet-if.insa-lyon.fr

int main(int argc, char** argv)
{
    CommandReader cm(argc, argv);
    map<string, string>* parameters = NULL;

    if (cm.IsGood())
    {
        parameters = cm.GetParameters();
    }
    else
    {
        return -1; // Fin du programme : mauvais paramètre ou aide demandée
    }

    ApacheLogFileParser apacheParser(parameters->find(CommandReader::LOG_FILE_NAME_KEY)->second);

    if(!apacheParser.IsGood())
    {
        cout << apacheParser.GetLastError() << endl;
        return -1;
    }

    map<string, string>::const_iterator itOptionGraphe = parameters->find("-g");
    // Si l'option -g est présente, alors on génère un graphe
    if (itOptionGraphe != parameters->end())
    {
        AnalogGraphe(apacheParser, parameters, itOptionGraphe);
    }
    else
    {
        Analog(apacheParser, parameters);
    }

    return 0;
}

void AnalogGraphe   (ApacheLogFileParser& apacheParser,
                    map<string, string>* parameters,
                    map<string, string>::const_iterator itOptionGraphe)
{
    struct LogLine *ptLogLine;
    ptLogLine = new LogLine;
    GraphString graph;

    bool optionX = false;
    bool optionI = false;
    int optionT = -1;
    bool insert;

    if (parameters->find("-x") != parameters->end())
    {
        optionX = true;
    }
    if (parameters->find("-i") != parameters->end())
    {
        optionI = true;
    }
    map<string, string>::const_iterator itOptionTemps = parameters->find("-t");
    if (itOptionTemps != parameters->end())
    {
        optionT = atoi((itOptionTemps->second).c_str());
    }

    while(apacheParser.GetLine(ptLogLine))
    {
        // Pour chaque ligne du fichier
//        cout << "|" << ptLogLine->ll_ipClient << "|\t\tll_ipClient" << endl;
//        cout << "|" << ptLogLine->ll_userLog << "|\t\tll_userLog" << endl;
//        cout << "|" << ptLogLine->ll_authenticatedUser << "|\t\tll_authenticatedUser" << endl;
//        cout << "|" << ptLogLine->ll_timeRequest.tm_mday << "|\t\ttm_mday" << endl;
//        cout << "|" << ptLogLine->ll_timeRequest.tm_mon << "|\t\ttm_mon" << endl;
//        cout << "|" << ptLogLine->ll_timeRequest.tm_year << "|\t\ttm_year" << endl;
//        cout << "|" << ptLogLine->ll_timeRequest.tm_hour << "|\t\ttm_hour" << endl;
//        cout << "|" << ptLogLine->ll_timeRequest.tm_min << "|\t\ttm_min" << endl;
//        cout << "|" << ptLogLine->ll_timeRequest.tm_sec << "|\t\ttm_sec" << endl;
//        cout << "|" << ptLogLine->ll_timeRequestGMT << "|\t\tll_timeRequestGMT" << endl;
//        cout << "|" << ptLogLine->ll_method << "|" << endl;
//        cout << "|" << ptLogLine->ll_url << "|" << endl;
//        cout << "|" << ptLogLine->ll_httpVersion << "|" << endl;
//        cout << "|" << ptLogLine->ll_status << "|" << endl;
//        cout << "|" << ptLogLine->ll_dataSize << "|" << endl;
//        cout << "|" << ptLogLine->ll_referer << "|" << endl;
//        cout << "|" << ptLogLine->ll_browserIdentification << "|" << endl << endl;
        insert = true;
        if(optionI)
        {
            if(!IsLocal(ptLogLine->ll_referer))
            {
                insert = false;
            }
        }
        // Epuration des URL
        ptLogLine->ll_referer = CleanURL(ptLogLine->ll_referer);
        ptLogLine->ll_url = CleanURL(ptLogLine->ll_url);

        if (optionX && insert)
        {
            if (!CorrectExtension(ptLogLine->ll_url))
            {
                insert = false;
            }
        }
        if (optionT != -1 && insert)
        {
            if (ptLogLine->ll_timeRequest.tm_hour != optionT)
            {
                insert = false;
            }
        }
        if (insert)
        {
            graph.Insert(ptLogLine->ll_referer, ptLogLine->ll_url);
        }
    }
    delete ptLogLine;

    // Génération du graphe
    string graphName = itOptionGraphe->second;
    graph.CreateGraphVizFile(graphName);

    // Affichage des 10 sites les plus visités
    int numberOfLinks = 10;
    map<string, string>::const_iterator itLinkOption = parameters->find("-l");
    if (itLinkOption != parameters->end())
    {
        numberOfLinks = atoi(itLinkOption->second.c_str());
    }
    set<pair<string, int>, compareVisitedLinks> s = graph.GetMostVisited(numberOfLinks);
    DisplayMostVisitedSet(s);

    // Si on souhaite générer l'image
    if (parameters->find("-o") != parameters->end())
    {
        string imageName = graphName.substr(0, graphName.size() - 3) + "png";
        // dot -Tpng -o IMAGE.png GRAPHE.dot
        string generateImageCommand = "dot -Tpng -o " + imageName + " " + itOptionGraphe->second;
        // shotwell IMAGE.png&
        string displayImageCommand = "shotwell " + imageName + "&";

        cout << "Generating " << imageName << ". Please wait... (this might take a while)" << endl;
        system(generateImageCommand.c_str());
        cout << "Image generated." << endl;
        system(displayImageCommand.c_str());
    }
}

void Analog(ApacheLogFileParser& apacheParser, map<string, string>* parameters)
{
    struct LogLine *ptLogLine;
    ptLogLine = new LogLine;
    map<string, int> visitedLinks;

    bool optionX = false;
    bool optionI = false;
    int optionT = -1;
    bool insert;

    if (parameters->find("-x") != parameters->end())
    {
        optionX = true;
    }
    if (parameters->find("-i") != parameters->end())
    {
        optionI = true;
    }
    map<string, string>::const_iterator itOptionTemps = parameters->find("-t");
    if (itOptionTemps != parameters->end())
    {
        optionT = atoi((itOptionTemps->second).c_str());
    }

    // Parcours des lignes du fichier de log
    while(apacheParser.GetLine(ptLogLine))
    {
        insert = true;
        if (optionI)
        {
            if (!IsLocal(ptLogLine->ll_referer))
            {
                insert = false;
            }
        }
        // Epuration des URL
        ptLogLine->ll_referer = CleanURL(ptLogLine->ll_referer);
        ptLogLine->ll_url = CleanURL(ptLogLine->ll_url);

        if (optionX && insert)
        {
            if (!CorrectExtension(ptLogLine->ll_url))
            {
                insert = false;
            }
        }
        if (optionT != -1 && insert)
        {
            if (ptLogLine->ll_timeRequest.tm_hour != optionT)
            {
                insert = false;
            }
        }

        if (insert)
        {
            visitedLinks[ptLogLine->ll_url]++;
        }

    }

    delete ptLogLine;

    // 10 sites les plus visités
    unsigned int numberOfLinks = 10;
    map<string, string>::const_iterator itLinkOption = parameters->find("-l");
    if (itLinkOption != parameters->end())
    {
        numberOfLinks = atoi(itLinkOption->second.c_str());
    }

    if (numberOfLinks != 0)
    {
        set<pair<string, int>, compareVisitedLinks> mostVisitedLinks;
        // Parcours de tous les liens
        map<string, int>::const_iterator it;
        map<string, int>::const_iterator itEnd = visitedLinks.end();
        for (it = visitedLinks.begin(); it != itEnd; ++it)
        {
            if (mostVisitedLinks.size() < numberOfLinks)
            {
                mostVisitedLinks.insert(pair<string, int>(it->first, it->second));
            }
            else
            {
                set<pair<string, int>, compareVisitedLinks>::const_iterator i = mostVisitedLinks.begin();
                advance(i, numberOfLinks-1);

                if (it->second > i->second)
                {
                    mostVisitedLinks.erase(i);
                    mostVisitedLinks.insert(pair<string, int>(it->first, it->second));
                }
            }
        }

        DisplayMostVisitedSet(mostVisitedLinks);
    }
}

string CleanURL(string url)
//  Nettoie une url de ses paramètres
//  ENleve la partie local de l'url lorsqu'on est sur l'intranet
{
    size_t deb = 0;
    size_t end = 0;
    if(url.find(LOCAL_URL) != string::npos)// si la chaine a été trouvée on est sur l'intranet
    {
        deb = url.find("/", LOCAL_URL.size());

    }
//    else if(url.find(localURL2) != string::npos)
//    {
//        deb = url.find("/", localURL2.size());
//    }


    if((end = url.find("?",deb)) == string::npos)// si on ne trouve pas de parametrage par point d'interrogation
    {
        if((end = url.find(";",deb)) == string::npos)// on teste le parametrage par point virgule
        {
            //pas de parametrage
            end = url.size();
        }
    }
    //on enleve maintenant le slash s'il se trouve a la fin de l'url si l'url restante n'est pas un slash seul.
    string result = url.substr(deb, end-deb);
    if (result.at(result.length()-1) == '/' && result != "/")
    {
        result.pop_back();
    }
    return result;
}

bool CorrectExtension(string s)
// Mode d'emploi : vérifie si l'extension de la chaîne s en paramètre ne se finit pas avec une des extensions ci-dessous
{
    set<string> extensionsToIgnore = {".css", ".js", ".png", ".jpg", ".jpeg", ".bmp", ".gif", ".svg", ".ico"};
    size_t pos = s.find_last_of('.');
    if(pos != string::npos)// si on a trouvé
    {
        if (extensionsToIgnore.find(s.substr(pos, s.size() - pos)) == extensionsToIgnore.end())
        {
            return true;
        }
        else
        {
                return false;
        }
    }
    else
    {
        return true;
    }
}

void DisplayMostVisitedSet(set<pair<string, int>, compareVisitedLinks>& visitedLinks)
{
    set<pair<string, int>, compareVisitedLinks>::const_iterator it;
    set<pair<string, int>, compareVisitedLinks>::const_iterator itEnd = visitedLinks.end();
    for (it = visitedLinks.begin(); it != itEnd; ++it)
    {
        cout << it->first << " (" << it->second << " hits)" << endl;
    }
}

bool IsLocal(string url)
{
    //regarde si l'url du local a été trouvée
    //ayant "http://" dans la locale, cela assure que la locale se trouve en début de l'url
    return(url.find(LOCAL_URL) != string::npos);
}