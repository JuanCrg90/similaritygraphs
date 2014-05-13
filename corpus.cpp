#include "corpus.h"


Corpus::Corpus() {}


Corpus::Corpus(string name, string fullText):name(name),fullText(fullText){}


void Corpus::setText(string fullText)
{
    this->fullText=fullText;
}

string Corpus::getText()
{
    return this->fullText;
}


bool Corpus::generateFrecuencyTable()
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

void Corpus::showText()
{
    cout<<"----------------------------"<<endl;
    cout<<"Full Text:"<<endl;
    cout<<fullText<<endl;
    cout<<"----------------------------"<<endl;
}

void Corpus::showFrecuencyTable()
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
