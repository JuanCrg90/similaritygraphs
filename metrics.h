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

    vector<vector<float> > transpose(vector<vector<float> > mat );



    /**
     * @brief manhatan
     * @param d1
     * @param d2
     * @return
     */
    float manhatan(Document d1,Document d2);








public:
    Metrics();


    vector < vector <float > > generateManhatan(Corpora c);

};

#endif // METRICS_H
