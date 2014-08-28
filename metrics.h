#ifndef METRICS_H
#define METRICS_H

#include "corpora.h"
#include <cmath>


#define DOCS 0
#define CLASS 1



class Metrics
{

private:

    /**
     * @brief balance
     * @param tf1
     * @param tf2
     */
    void balance(map<string,int>  &tf1 , map<string,int>  &tf2);

    /**
     * @brief show
     * @param tf1
     */
    void show(map<string,int>  tf1);

    /**
     * @brief copyDocuments
     * @param docs
     * @param c
     */
    void copyDocuments(vector<Document> *docs,Corpora c);

    /**
     * @brief copyfrecuency
     * @param docs
     * @param c
     */
    void copyfrecuencyTables(vector<map<string, int> > *fts, Corpora c);

    /**
     * @brief transpose
     * @param mat
     * @return
     */
    vector<vector<float> > transpose(vector<vector<float> > mat );

    /**
     * @brief rotate
     * @param mat
     * @return
     */
    vector<vector<float> > rotate(vector<vector<float> > mat );


    /**
     * @brief operationMode
     * @param c
     * @param docs
     * @param matrix
     */
    void operationMode(int &mode,Corpora &c,vector<Document> &docs,vector<map<string,int> > &fts,vector<vector<float> > &matrix);


    /**
     * @brief copyDocsAndAllocate
     * @param c
     * @param docs
     * @param matrix
     */
    void copyDocsAndAllocate(Corpora &c,vector<Document> &docs,vector<vector<float> > &matrix);

    /**
     * @brief copyFtsAndAllocate
     * @param c
     * @param fts
     * @param matrix
     */
    void copyFtsAndAllocate(Corpora &c, vector<map<string, int> > &fts, vector<vector<float> > &matrix);



    /**
     * @brief manhatan
     * @param d1
     * @param d2
     * @return
     */
    float manhatan(Document d1,Document d2);

    /**
     * @brief manhatan
     * @param doci
     * @param docj
     * @return
     */
    float manhatan(map<string, int>  doci, map<string, int>  docj);

    /**
     * @brief dice
     * @param d1
     * @param d2
     * @return
     */
    float dice(Document d1,Document d2);

    /**
     * @brief dice
     * @param doci
     * @param docj
     * @return
     */
    float dice(map<string, int>  doci, map<string, int>  docj);

    /**
     * @brief cosMetric
     * @param d1
     * @param d2
     * @return
     */
    float cosMetric(Document d1,Document d2);

    /**
     * @brief cosMetric
     * @param doci
     * @param docj
     * @return
     */
    float cosMetric(map<string, int>  doci, map<string, int>  docj);



    /**
     * @brief jaccard
     * @param d1
     * @param d2
     * @return
     */
    float jaccard(Document d1,Document d2);


    /**
     * @brief jaccard
     * @param doci
     * @param docj
     * @return
     */
    float jaccard(map<string, int>  doci, map<string, int>  docj);


public:
    Metrics();


    /**
     * @brief generateManhatan
     * @param c
     * @return
     */
    vector < vector <float > > generateManhatan(Corpora c, int mode);

    /**
     * @brief generateDice
     * @param c
     * @return
     */
    vector < vector <float > > generateDice(Corpora c, int mode);

    /**
     * @brief generateCos
     * @param c
     * @return
     */
    vector < vector <float > > generateCos(Corpora c, int mode);

    /**
     * @brief generateJaccard
     * @param c
     * @return
     */
    vector < vector <float > > generateJaccard(Corpora c, int mode);


    vector<vector<float> > multiplyByScalar(vector<vector<float> > mat , float scalar);

    vector<vector<float> > negativeMatrix(vector<vector<float> > mat , float val);

    vector<vector<float> > normalizeMatrix(vector<vector<float> > mat);






};

#endif // METRICS_H
