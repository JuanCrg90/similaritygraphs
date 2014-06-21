#include "document.h"


Document::Document() {}


Document::Document(string name, string fullText):name(name),fullText(fullText){}


void Document::setText(string fullText)
{
    this->fullText=fullText;
}

string Document::getText()
{
    return this->fullText;
}


bool Document::generateFrecuencyTable()
{



    if(!fullText.empty())
    {

        std::map<string,int>::iterator it;
        char *token;
        char *dup = strdup(fullText.c_str());

        token=strtok(dup,tags.c_str()) ;
        while(token != NULL)
        {
            it=frecuencyTable.find(token);

            if(it!=frecuencyTable.end())
            {
                it->second++;
            }
            else
            {
                frecuencyTable.insert(pair<string,int> (token,1));
            }
            token=strtok(NULL,tags.c_str());
        }

        free(dup);

        return true;
    }
    else
    {
        return false;
    }

}

void Document::removeStopWords(vector<string> stopW)
{
    std::map<string,int>::iterator it;

    for(unsigned int i=0;i<stopW.size();i++)
    {

        it=frecuencyTable.find(stopW[i]);

        if(it!=frecuencyTable.end())
        {
            frecuencyTable.erase(it);
        }
        else
        {
            continue;
        }
    }

}

void Document::showText()
{
    cout<<"----------------------------"<<endl;
    cout<<"Full Text:"<<endl;
    cout<<fullText<<endl;
    cout<<"----------------------------"<<endl;
}

void Document::setFrecuencyTable(map<string, int> frecuencyTable)
{
    this->frecuencyTable.clear();
    this->frecuencyTable=frecuencyTable;
}

map<string, int> Document::getFrecuencyTable()
{
    return this->frecuencyTable;
}

void Document::showFrecuencyTable()
{
    std::map<string,int>::iterator it;
    it=frecuencyTable.begin();

    cout<<"----------------------------"<<endl;
    cout<<"Frequency Table:"<<endl;
    while(it!=frecuencyTable.end())
    {
        cout<<it->first<<" "<<it->second<<endl;
        it++;
    }
    cout<<"----------------------------"<<endl;
}
