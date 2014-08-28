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
            tf1.insert(pair<string,int> (it1->first,0));
        }

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
    for(unsigned int i=0;i<c.getCorpora().size();i++)
    {
        for(unsigned int j=0;j<c.getCorpora().at(i).getCorp().size();j++)
        {
            //inserta al final el documento j del corpus i
            docs->push_back(c.getCorpora().at(i).getDocument(j));
        }

    }
}

void Metrics::copyfrecuencyTables(vector<map<string,int> > *fts, Corpora c)
{
    //Copiando las tablas de frecuencias
    for(unsigned int i=0;i<c.getCorpora().size();i++)
    {
        fts->push_back(c.getCorpus(i).getCorpusFrequencyTable());
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

vector<vector<float> > Metrics::rotate(vector<vector<float> > mat)
{
    vector<vector<float> > rot;


    rot.resize(mat.size());

    for(unsigned int i=0;i<mat.size();i++)
    {
        rot[i].resize(mat.size());
    }

    /*
     1 2 3      3 6 1
     4 1 6  --> 2 1 8
     7 8 1      1 4 7
     */


    for(unsigned int i=0;i<mat.size();i++)
    {
        for(unsigned int j=0;j<mat.size();j++)
        {
            rot[(mat.size()-1)-j][i]=mat[i][j];
        }
    }


    return rot;


}

void Metrics::operationMode(int &mode, Corpora &c, vector<Document> &docs, vector<map<string, int> > &fts, vector<vector<float> > &matrix)
{
    switch (mode)
    {
    case DOCS:
        copyDocsAndAllocate(c,docs,matrix);
        break;
    case CLASS:
        copyFtsAndAllocate(c,fts,matrix);
    default:
        break;
    }
}

void Metrics::copyDocsAndAllocate(Corpora &c,vector<Document> &docs, vector<vector<float> > &matrix)
{
    copyDocuments(&docs,c);

    matrix.resize(docs.size());

    for(unsigned int i=0;i<matrix.size();i++)
    {
        matrix[i].resize(docs.size());
    }
}

void Metrics::copyFtsAndAllocate(Corpora &c, vector<map<string,int> > &fts, vector<vector<float> > &matrix)
{
    copyfrecuencyTables(&fts,c);

    matrix.resize(fts.size());

    for(unsigned int i=0;i<matrix.size();i++)
    {
        matrix[i].resize(fts.size());
    }
}

vector<vector<float> > Metrics::multiplyByScalar(vector<vector<float> > mat,float  scalar)
{
    for(unsigned int i=0;i<mat.size();i++)
    {
        for(unsigned int j=0;j<mat[i].size();j++)
        {
            mat[i][j]*=scalar;
        }
    }

    return mat;

}

vector<vector<float> > Metrics::negativeMatrix(vector<vector<float> > mat,float val)
{
    for(unsigned int i=0;i<mat.size();i++)
    {
        for(unsigned int j=0;j<mat[0].size();j++)
        {
            mat[i][j]=val-mat[i][j];
        }
    }
    return mat;
}

vector<vector<float> > Metrics::normalizeMatrix(vector<vector<float> > mat)
{

    //Obteniendo el valor maximo en la matriz

    float maxVal=0;

    for(unsigned int i=0;i<mat.size();i++)
    {
        for(unsigned int j=0;j<mat[0].size();j++)
        {
            if(mat[i][j]>maxVal)
                maxVal = mat[i][j];
        }
    }

    //cout<<maxVal<<endl;
    //cout<<1.0/(maxVal*1.0)<<endl;

    //mat = multiplyByScalar(mat,static_cast<float>(1.0/(maxVal*1.0)));
    mat = multiplyByScalar(mat,1.0/(maxVal*1.0));

    return mat;
}

float Metrics::manhatan(Document d1, Document d2)
{
    map<string,int> doci; //Tabla de Frequencias del Corpus i
    map<string,int> docj; //Tabla de Frequencias del Corpus j

    doci = d1.getFrequencyTable();
    docj = d2.getFrequencyTable();

    return manhatan(doci,docj);
}

float Metrics::manhatan(map<string, int> doci, map<string, int> docj)
{

    std::map<string,int>::iterator wki;
    std::map<string,int>::iterator wkj;

    float dist=0.0;


    balance(doci,docj);

    //en caso de que ambos documentos esten vacios los saltamos
    if(doci.size() == 0 && docj.size() == 0) return 255;

    //cout<<"Balanceados"<<doci.size()<<" "<<docj.size()<<endl;

    wki=doci.begin();
    wkj=docj.begin();

    for(unsigned int i=0;i<doci.size();i++)
    {
        dist += abs(wki->second - wkj->second);
        wki++;
        wkj++;
    }

    return dist;

}

float Metrics::dice(Document d1, Document d2)
{
    map<string,int> doci; //Tabla de Frequencias del Corpus i
    map<string,int> docj; //Tabla de Frequencias del Corpus j

    doci = d1.getFrequencyTable();
    docj = d2.getFrequencyTable();
    return dice(doci,docj);
}

float Metrics::dice(map<string, int>  doci, map<string, int>  docj)
{

    std::map<string,int>::iterator wki;
    std::map<string,int>::iterator wkj;

    float numerator=0.0;
    float denominator=0.0;
    float denX=0.0;
    float denY=0.0;

    balance(doci,docj);

    //en caso de que ambos documentos esten vacios los saltamos
    if(doci.size() == 0 && docj.size() == 0) return 0;

    //cout<<"Balanceados"<<doci.size()<<" "<<docj.size()<<endl;

    wki = doci.begin();
    wkj = docj.begin();

    //Numerador
    for(unsigned int i=0;i<doci.size();i++)
    {
        numerator += (wki->second * wkj->second);
        wki++;
        wkj++;
    }

    numerator *= 2;

    wki=doci.begin();
    wkj=docj.begin();

    //Denominador
    for(unsigned int i=0;i<doci.size();i++)
    {
        denX += (wki->second * wki->second);
        denY += (wkj->second * wkj->second);

        wki++;
        wkj++;
    }

    denominator = denX + denY;

    return static_cast<float>(numerator) / static_cast<float> (denominator);
}

float Metrics::cosMetric(Document d1, Document d2)
{
    map<string,int> doci; //Tabla de Frequencias del Corpus i
    map<string,int> docj; //Tabla de Frequencias del Corpus j

    doci = d1.getFrequencyTable();
    docj = d2.getFrequencyTable();
    return cosMetric(doci,docj);
}

float Metrics::cosMetric(map<string, int>  doci, map<string, int>  docj)
{
    std::map<string,int>::iterator wki;
    std::map<string,int>::iterator wkj;

    float numerator=0.0;
    float denominator=0.0;
    float denX=0.0;
    float denY=0.0;

    balance(doci,docj);

    //en caso de que ambos documentos esten vacios los saltamos
    if(doci.size() == 0 && docj.size() == 0) return 0;

    //cout<<"Balanceados"<<doci.size()<<" "<<docj.size()<<endl;

    wki = doci.begin();
    wkj = docj.begin();

    //Numerador
    for(unsigned int i=0;i<doci.size();i++)
    {
        numerator += (wki->second * wkj->second);

        wki++;
        wkj++;
    }

    wki=doci.begin();
    wkj=docj.begin();

    //Denominador
    for(unsigned int i=0;i<doci.size();i++)
    {
        denX += (wki->second * wki->second); //x^2
        denY += (wkj->second * wkj->second); //y^2

        wki++;
        wkj++;
    }

    denominator = sqrt(static_cast<float>(denX * denY));

    //Evitamos una división por 0
    if(denominator==0) return 0;

    return static_cast<float>(numerator) / static_cast<float> (denominator);
}

float Metrics::jaccard(Document d1, Document d2)
{
    map<string,int> doci; //Tabla de Frequencias del Corpus i
    map<string,int> docj; //Tabla de Frequencias del Corpus j

    doci = d1.getFrequencyTable();
    docj = d2.getFrequencyTable();

    return jaccard(doci,docj);
}

float Metrics::jaccard(map<string, int> doci, map<string, int> docj)
{

    std::map<string,int>::iterator wki;
    std::map<string,int>::iterator wkj;

    float numerator=0.0;
    float denominator=0.0;
    float denX=0.0;
    float denY=0.0;
    float denXY=0.0;


    balance(doci,docj);

    //en caso de que ambos documentos esten vacios los saltamos
    if(doci.size() == 0 && docj.size() == 0) return 0;

    wki = doci.begin();
    wkj = docj.begin();

    //Numerador
    for(unsigned int i=0;i<doci.size();i++)
    {
        numerator += (wki->second * wkj->second);

        wki++;
        wkj++;
    }

    wki=doci.begin();
    wkj=docj.begin();

    //Denominador
    for(unsigned int i=0;i<doci.size();i++)
    {
        denX += (wki->second * wki->second);
        denY += (wkj->second * wkj->second);
        denXY += (wki->second * wkj->second);

        wki++;
        wkj++;
    }

    denominator = denX + denY-denXY;

    //Evitamos una división por 0
    if(denominator==0) return 0;


    return static_cast<float>(numerator) / static_cast<float> (denominator);

}

vector<vector<float> > Metrics::generateManhatan(Corpora c,int mode)
{
    vector<Document> docs;
    vector<map<string,int> > fts;
    vector<vector<float> > matrix;
    float result;
    unsigned int size;

    operationMode(mode,c,docs,fts,matrix);

    size=matrix.size();

    for(unsigned int i=0;i<size;i++)
    {
        for(unsigned int j=i;j<size;j++)
        {
            if(i==j)
                result=0.0;
            else
                (mode==DOCS) ? result=manhatan(docs[i],docs[j]) : result=manhatan(fts[i],fts[j]);

            matrix[i][j]=result;
            matrix[j][i]=result;
        }
    }

    if(mode==CLASS) matrix=rotate(matrix);

    return matrix;
}

vector<vector<float> > Metrics::generateDice(Corpora c, int mode)
{
    vector<Document> docs;
    vector<map<string,int> > fts;
    vector<vector<float> > matrix;
    float result;
    unsigned int size;

    operationMode(mode,c,docs,fts,matrix);

    size=matrix.size();

    for(unsigned int i=0;i<size;i++)
    {
        for(unsigned int j=i;j<size;j++)
        {
            if(i==j)
                result=1.0;
            else
                (mode==DOCS) ? result=dice(docs[i],docs[j]) : result=dice(fts[i],fts[j]);

            matrix[i][j]=result;
            matrix[j][i]=result;
        }
    }

    if(mode==CLASS) matrix=rotate(matrix);

    return matrix;
}

vector<vector<float> > Metrics::generateCos(Corpora c,int mode)
{
    vector<Document> docs;
    vector<map<string,int> > fts;
    vector<vector<float> > matrix;
    float result;
    unsigned int size;

    operationMode(mode,c,docs,fts,matrix);

    size=matrix.size();

    for(unsigned int i=0;i<size;i++)
    {
        for(unsigned int j=i;j<size;j++)
        {
            if(i==j)
                result=1.0;
            else
                (mode==DOCS) ? result=cosMetric(docs[i],docs[j]) : result=cosMetric(fts[i],fts[j]);

            matrix[i][j]=result;
            matrix[j][i]=result;
        }
    }

    if(mode==CLASS) matrix=rotate(matrix);

    return matrix;
}

vector<vector<float> > Metrics::generateJaccard(Corpora c,int mode)
{
    vector<Document> docs;
    vector<map<string,int> > fts;
    vector<vector<float> > matrix;
    float result;
    unsigned int size;

    operationMode(mode,c,docs,fts,matrix);

    size=matrix.size();

    for(unsigned int i=0;i<size;i++)
    {
        for(unsigned int j=i;j<size;j++)
        {
            if(i==j)
                result=1.0;
            else
                (mode==DOCS) ? result=jaccard(docs[i],docs[j]) : result=jaccard(fts[i],fts[j]);

            matrix[i][j]=result;
            matrix[j][i]=result;
        }
    }

    if(mode==CLASS) matrix=rotate(matrix);
    return matrix;
}
