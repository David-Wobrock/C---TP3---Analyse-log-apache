#include <iostream>

#include "CommandReader.h"
#include "ApacheLogFileParser.h"
#include "LogLine.h"
#include "GraphString.h"

using namespace std;

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

    ApacheLogFileParser apacheParser(parameters->find("LOG_FILE_NAME")->second);

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
        graph.Insert(ptLogLine->ll_referer, ptLogLine->ll_url);
        graph.Insert("autreReFEreR", ptLogLine->ll_url);
        graph.Insert("Encore Autre referer", ptLogLine->ll_url);
        cout << "liens entre : " << ptLogLine->ll_referer << " et " << ptLogLine->ll_url << " : " << graph.GetLinks(ptLogLine->ll_referer, ptLogLine->ll_url) << endl;
        cout << "liens totaux allant a : " << ptLogLine->ll_url << " : " << graph.GetAllLinks(ptLogLine->ll_url) << endl;
    }
//    cout << apacheParser.GetLastError() << endl;
    //graph.Display();

    //parcours et affichage du graphe
    for(GraphString::Outer_cIterator i = graph.Outer_begin(), iend = graph.Outer_end(); i != iend; ++i)//du debut a la fin du graph
    {
        cout << "cible : (" << i->second.second << ")" << endl << i->first << endl;
        cout << "\treferer : " << endl;
        for (GraphString::Inner_cIterator j = graph.Inner_begin(i->first), jend = graph.Inner_end(i->first); j != jend; ++j)
        {
               cout << "\t- " << j->first << "(" << j->second << ")" << endl;
        }
    }

    cout << "taille du graphe : " << graph.Size() << endl;
    return 0;
}

