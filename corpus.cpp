#include "corpus.h"


Corpus::Corpus() {}

void Corpus::setName(string name)
{
    this->name=name;
}

string Corpus::getName()
{
    return name;
}


void Corpus::setCorp(const vector<Document> &value)
{
    //corp = value;
}

vector<Document> Corpus::getCorp() const
{
    return corp;
}

void Corpus::addDocument(Document doc)
{
    this->corp.push_back(doc);
}

Document Corpus::getDocument(int index)
{
    return this->corp.at(index);
}

void Corpus::generateCorpusFrequencyTable()
{
    map<string,int> doci; //Tabla de Frecuencias del Documento i
    std::map<string,int>::iterator it1;
    std::map<string,int>::iterator it2;


    corpusFrequencyTable.clear();

    for(unsigned int i=0;i<corp.size();i++)
    {
        doci = corp[i].getFrequencyTable();

        it1=doci.begin();

        while(it1!=doci.end())
        {
            it2=corpusFrequencyTable.find(it1->first);


            if(it2!=corpusFrequencyTable.end())
            {
                //cout<<it1->first<<" Existe "<< it2->second<<endl;
                it2->second+=it1->second;

            }
            else
            {
                //cout<<it1->first<<" No Existe"<<endl;
                corpusFrequencyTable.insert(pair<string,int> (it1->first,it1->second));
            }
            it1++;
        }


    }

}

void Corpus::showCorpusFrequencyTable()
{
    std::map<string,int>::iterator it;
    it=corpusFrequencyTable.begin();

    cout<<"----------------------------"<<endl;
    cout<<"Corpus Frequency Table:"<<endl;
    while(it!=corpusFrequencyTable.end())
    {
        cout<<it->first<<" "<<it->second<<endl;
        it++;
    }
    cout<<"----------------------------"<<endl;


}


map<string, int> Corpus::getCorpusFrequencyTable() const
{
    return corpusFrequencyTable;
}

void Corpus::setCorpusFrequencyTable(const map<string, int> &value)
{
    corpusFrequencyTable = value;
}

void Corpus::balanceCorpus()
{
    map<string,int> doci; //Tabla de Frequencias del Corpus i
    map<string,int> docj; //Tabla de Frequencias del Corpus j

    std::map<string,int>::iterator it1;
    std::map<string,int>::iterator it2;

    for(unsigned int i=0;i<corp.size();i++)
    {
        doci = corp[i].getFrequencyTable();


        for(unsigned int j=0;j<corp.size();j++)
        {
            docj = corp[j].getFrequencyTable();


            it1=docj.begin();

            cout<<"Corpus "<<i<< " VS "<<j<<endl;

            while(it1!=docj.end())
            {
                it2=doci.find(it1->first);

                if(it2==doci.end())
                {
                    //cout<<it1->first<<" No Existe"<<endl;
                    doci.insert(pair<string,int> (it1->first,0));
                    corp[i].setFrequencyTable(doci);
                }
                else
                {
                    //cout<<it1->first<<" Existe"<<endl;
                }
                it1++;
            }
        }
    }
    generateCorpusFrequencyTable();
}

void Corpus::threshold(int th)
{
    map<string,int> auxiliarCorp;
    std::map<string,int>::iterator it;

    for(unsigned int i=0;i<corp.size();i++)
    {
        auxiliarCorp=corp[i].getFrequencyTable();
        it=auxiliarCorp.begin();

        while(it!=auxiliarCorp.end())
        {
            if(it->second < th)
            {
                auxiliarCorp.erase(it);                                
            }
            it++;
        }
        corp[i].setFrequencyTable(auxiliarCorp);
    }

    generateCorpusFrequencyTable();

}

void Corpus::corpusThreshold(int th)
{
    std::map<string,int>::iterator it;

    it=corpusFrequencyTable.begin();

    while(it!=corpusFrequencyTable.end())
    {
        if(it->second < th)
        {
            corpusFrequencyTable.erase(it);
        }
        it++;
    }


}


