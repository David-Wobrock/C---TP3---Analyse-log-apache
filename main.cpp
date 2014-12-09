#include <iostream>

#include "CommandReader.h"
#include "ApacheLogFileParser.h"
#include "LogLine.h"
#include "GraphString.h"

using namespace std;

string CleanURL(string url);

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

    cout << parameters->find(CommandReader::LOG_FILE_NAME_KEY)->second << endl;

    ApacheLogFileParser apacheParser(parameters->find(CommandReader::LOG_FILE_NAME_KEY)->second);

    if(!apacheParser.IsGood())
    {
        cout << apacheParser.GetLastError() << endl;
        return -1;
    }

    struct LogLine *ptLogLine;
    ptLogLine = new LogLine;
    GraphString graph;

    cout << "taille du graphe : " << graph.Size() << endl;
    while(apacheParser.GetLine(ptLogLine))
    {
        //pour chaque ligne du fichier

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
        ptLogLine->ll_referer = CleanURL(ptLogLine->ll_referer);
        ptLogLine->ll_url = CleanURL(ptLogLine->ll_url);
        graph.Insert(ptLogLine->ll_referer, ptLogLine->ll_url);
    }
//    cout << apacheParser.GetLastError() << endl;
    return 0;
}

string CleanURL(string url)
//  Nettoie une url de ses paramètres
//  ENleve la partie local de l'url lorsqu'on est sur l'intranet
{
    //Constantes de la fonction
    const string localURL = "http://intranet-if";  //Addresse locale de l'intranet, à enlever
    // peut par exemple être    http://intranet-if:90/
    // ou                       http://intranet-if.insa-lyon.fr
    size_t deb = 0;
    size_t end = 0;
    if(url.find(localURL) != string::npos)// si la chaine a été trouvée on est sur l'intranet
    {
        deb = url.find("/", localURL.size());

    }
    if((end = url.find("?",deb)) == string::npos)// si on ne trouve pas de parametrage par point d'interrogation
    {
        if((end = url.find(";",deb)) == string::npos)// on teste le parametrage par point virgule
        {
            //pas de parametrage
            end = url.size();
        }
    }
    //on enleve maintenant le slash s'il se trouve a la fin de l'url
    if(url.at(url.length()-1) == '/')
    {
        url.pop_back();
    }
    return url.substr(deb, end-deb);
}
