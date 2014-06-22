#include "document.h"


Document::Document() {}


Document::Document(string name, string fullText):name(name),fullText(fullText){}

void Document::setName(string name)
{
    this->name=name;
}

string Document::getName()
{
    return name;
}


void Document::setText(string fullText)
{
    this->fullText=fullText;
}

string Document::getText()
{
    return this->fullText;
}


bool Document::generateFrequencyTable()
{



    if(!fullText.empty())
    {

        std::map<string,int>::iterator it;
        char *token;
        char *dup = strdup(fullText.c_str());

        token=strtok(dup,tags.c_str()) ;
        while(token != NULL)
        {
            it=frequencyTable.find(token);

            if(it!=frequencyTable.end())
            {
                it->second++;
            }
            else
            {
                frequencyTable.insert(pair<string,int> (token,1));
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

        it=frequencyTable.find(stopW[i]);

        if(it!=frequencyTable.end())
        {
            frequencyTable.erase(it);
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

void Document::setFrequencyTable(map<string, int> frequencyTable)
{
    this->frequencyTable.clear();
    this->frequencyTable=frequencyTable;
}

map<string, int> Document::getFrequencyTable()
{
    return this->frequencyTable;
}

void Document::showFrequencyTable()
{
    std::map<string,int>::iterator it;
    it=frequencyTable.begin();

    cout<<"----------------------------"<<endl;
    cout<<"Frequency Table:"<<endl;
    while(it!=frequencyTable.end())
    {
        cout<<it->first<<" "<<it->second<<endl;
        it++;
    }
    cout<<"----------------------------"<<endl;
}
