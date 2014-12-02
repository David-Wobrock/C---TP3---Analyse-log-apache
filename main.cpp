#include <iostream>

#include "CommandReader.h"
#include "ApacheLogFileParser.h"
#include "LogLine.h"

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

    cout << "Autre traitement..." << endl;

    cout << parameters->find("LOG_FILE_NAME")->second << endl;

    ApacheLogFileParser apacheParser(parameters->find("LOG_FILE_NAME")->second);

    if(!apacheParser.IsGood())
    {
        cout << apacheParser.GetLastError() << endl;
        return -1;
    }

    struct LogLine *ptLogLine;
    ptLogLine = new LogLine;

    while(apacheParser.GetLine(ptLogLine))
    {
        //pour chaque ligne du fichier
        /*
        cout << "|" << ptLogLine->ll_ipClient << "|" << endl;
        cout << "|" << ptLogLine->ll_userLog << "|" << endl;
        cout << "|" << ptLogLine->ll_authenticatedUser << "|" << endl;
        cout << "|" << ptLogLine->ll_browserIdentification << "|" << endl;
        cout << "|" << ptLogLine->ll_method << "|" << endl;
        cout << "|" << ptLogLine->ll_url << "|" << endl;
        cout << "|" << ptLogLine->ll_httpVersion << "|" << endl;
        cout << "|" << ptLogLine->ll_status << "|" << endl;
        cout << "|" << ptLogLine->ll_dataSize << "|" << endl;
        cout << "|" << ptLogLine->ll_referer << "|" << endl;
        cout << "|" << ptLogLine->ll_browserIdentification << "|" << endl << endl;
        */
    }
    //cout << apacheParser.GetLastError() << endl;


    return 0;
}

