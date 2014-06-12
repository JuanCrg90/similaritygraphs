/**
    @file: Corpora.h
    @author: Juan Carlos Ruiz González (jc.ruiz.gonzalez@ugto.mx)
    @date 12/08/2014
    @brief Class for handling a group of corpus
    @version 1.0

**/
#ifndef CORPORA_H

#define CORPORA_H
#include "corpus.h"


using namespace std;
/**
 * @brief The Corpora class
 */
class Corpora
{
private:
    /**
     * @brief corpora
     */
    vector<Corpus> corpora;
    /**
     * @brief global corpora
     */
    Corpus global;

public:
    Corpora();

    /**
     * @brief setCorpora
     * @param corpora
     */
    void setCorpora(vector<Corpus> corpora);

    /**
     * @brief getCorpora
     * @return vector<Corpus>
     */
    vector<Corpus> getCorpora();

    /**
     * @brief addCorpus
     * @param corp
     */
    void addCorpus(Corpus corp);

    /**
     * @brief balance the corpus with the same words
     */
    void balance();

    /**
     * @brief generateGlobal
     */

    void generateGlobal();

    Corpus getGlobal();





};

#endif // CORPORA_H
