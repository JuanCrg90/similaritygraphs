#ifndef METRICS_H
#define METRICS_H

#include "corpora.h"
#include <cmath>

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
     * @brief transpose
     * @param mat
     * @return
     */
    vector<vector<float> > transpose(vector<vector<float> > mat );



    /**
     * @brief manhatan
     * @param d1
     * @param d2
     * @return
     */
    float manhatan(Document d1,Document d2);

    /**
     * @brief dice
     * @param d1
     * @param d2
     * @return
     */
    float dice(Document d1,Document d2);

    /**
     * @brief cosMetric
     * @param d1
     * @param d2
     * @return
     */

    float cosMetric(Document d1,Document d2);

    /**
     * @brief jaccard
     * @param d1
     * @param d2
     * @return
     */
    float jaccard(Document d1,Document d2);


public:
    Metrics();


    /**
     * @brief generateManhatan
     * @param c
     * @return
     */
    vector < vector <float > > generateManhatan(Corpora c);

    /**
     * @brief generateDice
     * @param c
     * @return
     */
    vector < vector <float > > generateDice(Corpora c);

    /**
     * @brief generateCos
     * @param c
     * @return
     */
    vector < vector <float > > generateCos(Corpora c);

    /**
     * @brief generateJaccard
     * @param c
     * @return
     */
    vector < vector <float > > generateJaccard(Corpora c);



};

#endif // METRICS_H
