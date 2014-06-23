#include "corpora.h"


Corpora::Corpora()
{
}

void Corpora::setCorpora(const vector<Corpus> &value)
{
    //corpora = value;
}

vector<Corpus> Corpora::getCorpora() const
{
    return corpora;
}

void Corpora::addCorpus(Corpus corp)
{
    corpora.push_back(corp);
}

Corpus Corpora::getCorpus(int index)
{
    return corpora[index];
}


void Corpora::setCorporaFrequencyTable(const map<string, int> &value)
{
    corporaFrequencyTable = value;
}

map<string, int> Corpora::getCorporaFrequencyTable() const
{
    return corporaFrequencyTable;
}

void Corpora::generateCorporaFrequencyTable()
{
    map<string,int> corpi; //Tabla de Frecuencias del Corpus i
    std::map<string,int>::iterator it1;
    std::map<string,int>::iterator it2;

    corporaFrequencyTable.clear();

    for(unsigned int i=0;i<corpora.size();i++)
    {
        corpi = corpora[i].getCorpusFrequencyTable();

        it1=corpi.begin();

        while(it1!=corpi.end())
        {
            it2=corporaFrequencyTable.find(it1->first);


            if(it2!=corporaFrequencyTable.end())
            {
                //cout<<it1->first<<" Existe "<< it2->second<<endl;
                it2->second+=it1->second;

            }
            else
            {
                //cout<<it1->first<<" No Existe"<<endl;
                corporaFrequencyTable.insert(pair<string,int> (it1->first,it1->second));
            }
            it1++;
        }


    }

}

void Corpora::showCorporaFrequencyTable()
{
    std::map<string,int>::iterator it;
    it=corporaFrequencyTable.begin();

    cout<<"----------------------------"<<endl;
    cout<<"Corpora Frequency Table:"<<endl;
    while(it!=corporaFrequencyTable.end())
    {
        cout<<it->first<<" "<<it->second<<endl;
        it++;
    }
    cout<<"----------------------------"<<endl;
}
