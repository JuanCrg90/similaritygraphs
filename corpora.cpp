#include "corpora.h"

Corpora::Corpora()
{
}

void Corpora::setCorpora(vector<Corpus> corpora)
{
    this->corpora.clear();

    for(unsigned int i=0; i<corpora.size();i++)
        this->corpora.push_back(corpora[i]);

}

vector<Corpus> Corpora::getCorpora()
{
    return this->corpora;
}

void Corpora::addCorpus(Corpus corp)
{
    this->corpora.push_back(corp);

}

void Corpora::balance()
{
    map<string,int> corpi; //Tabla de Frecuencias del Corpus i
    map<string,int> corpj; //Tabla de Frecuencias del Corpus j

    std::map<string,int>::iterator it1;
    std::map<string,int>::iterator it2;

    for(unsigned int i=0;i<corpora.size();i++)
    {
        corpi = corpora[i].getFrecuencyTable();


        for(unsigned int j=0;j<corpora.size();j++)
        {
            corpj = corpora[j].getFrecuencyTable();


            it1=corpj.begin();

            //cout<<"Corpus "<<i<< " VS "<<j<<endl;

            while(it1!=corpj.end())
            {
                it2=corpi.find(it1->first);

                if(it2==corpi.end())
                {
                    //cout<<it1->first<<" No Existe"<<endl;
                    corpi.insert(pair<string,int> (it1->first,0));
                    corpora[i].setFrecuencyTable(corpi);
                }
                else
                {
                    //cout<<it1->first<<" Existe"<<endl;
                }
                it1++;
            }
        }
    }
}

void Corpora::generateGlobal()
{
    map<string,int> corpi; //Tabla de Frecuencias del Corpus i
    map<string,int> corpGlobal; //Tabla de Frecuencias global
    std::map<string,int>::iterator it1;
    std::map<string,int>::iterator it2;     

    for(unsigned int i=0;i<corpora.size();i++)
    {
        corpi = corpora[i].getFrecuencyTable();

        it1=corpi.begin();

        while(it1!=corpi.end())
        {
            it2=corpGlobal.find(it1->first);


            if(it2!=corpGlobal.end())
            {
                //cout<<it1->first<<" Existe "<< it2->second<<endl;
                it2->second+=it1->second;

            }
            else
            {
                //cout<<it1->first<<" No Existe"<<endl;
                corpGlobal.insert(pair<string,int> (it1->first,it1->second));
            }
            it1++;
        }


    }

    global.setFrecuencyTable(corpGlobal);


}

Corpus Corpora::getGlobal()
{
    return global;
}




