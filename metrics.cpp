#include "metrics.h"

Metrics::Metrics()
{
}


void Metrics::balance(map<string, int> &tf1, map<string, int> &tf2)
{
    std::map<string,int>::iterator it1;
    std::map<string,int>::iterator it2;


    //Balanceando tf2 con tf1
    it1=tf1.begin();


    while(it1!=tf1.end())
    {
        it2=tf2.find(it1->first);

        if(it2==tf2.end())
        {
            tf2.insert(pair<string,int> (it1->first,0));
        }
        it1++;
    }

    //Balanceando tf1 con tf2
    it1=tf2.begin();

    while(it1!=tf2.end())
    {
        it2=tf1.find(it1->first);

        if(it2==tf1.end())
        {
            tf1.insert(pair<string,int> (it1->first,0));        }

        it1++;
    }

}

void Metrics::show(map<string, int> tf1)
{
    std::map<string,int>::iterator it;
    it=tf1.begin();

    cout<<"----------------------------"<<endl;
    cout<<"Corpus Frequency Table:"<<endl;
    while(it!=tf1.end())
    {
        cout<<it->first<<" "<<it->second<<endl;
        it++;
    }
    cout<<"----------------------------"<<endl;
}

void Metrics::copyDocuments(vector<Document> *docs,Corpora c)
{

    //Copiando los documentos al vector
    for(int i=0;i<c.getCorpora().size();i++)
    {
        for(int j=0;j<c.getCorpora().at(i).getCorp().size();j++)
        {            
            //inserta al final el documento j del corpus i
            docs->push_back(c.getCorpora().at(i).getDocument(j));
        }

    }
}

vector<vector<float> > Metrics::transpose(vector<vector<float> > mat)
{
    vector<vector<float> > trans;

    trans.resize(mat.size());

    for(unsigned int i=0;i<mat.size();i++)
    {
        trans[i].resize(mat.size());
    }


    for(unsigned int i=0;i<mat.size();i++)
    {
        for(unsigned int j=0;j<mat.size();j++)
        {
            trans[j][i]=mat[i][j];
        }
    }

    return trans;
}

float Metrics::manhatan(Document d1, Document d2)
{
    map<string,int> doci; //Tabla de Frequencias del Corpus i
    map<string,int> docj; //Tabla de Frequencias del Corpus j
    std::map<string,int>::iterator wki;
    std::map<string,int>::iterator wkj;

    float dist=0.0;

    doci = d1.getFrequencyTable();
    docj = d2.getFrequencyTable();

    balance(doci,docj);

    wki=doci.begin();
    wkj=docj.begin();



    for(int i=0;i<doci.size();i++)
    {
        dist += abs(wki->second - wkj->second);
        wki++;
        wkj++;
    }

    return dist;
}


vector<vector<float> > Metrics::generateManhatan(Corpora c)
{
    vector<Document> docs;
    vector<vector<float> > matrix;

     copyDocuments(&docs,c);

     matrix.resize(docs.size());

     for(unsigned int i=0;i<matrix.size();i++)
     {
         matrix[i].resize(docs.size());
     }

     for(unsigned int i=0;i<matrix.size();i++)
     {
         for(unsigned int j=0;j<matrix.size();j++)
         {
             matrix[i][j]=manhatan(docs[i],docs[j]);
         }
     }

     //matrix = transpose(matrix);


     return matrix;
}
