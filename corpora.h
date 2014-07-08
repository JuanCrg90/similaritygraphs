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
     * @brief corporaFrequencyTable
     */
    map<string,int> corporaFrequencyTable;

public:

    /**
     * @brief Corpora
     */
    Corpora();

    /**
     * @brief setCorpora
     * @param value
     */
    void setCorpora(const vector<Corpus> &value);

    /**
     * @brief getCorpora
     * @return
     */
    vector<Corpus> getCorpora() const;

    /**
     * @brief addCorpus
     * @param corp
     */
    void addCorpus(Corpus corp);

    /**
     * @brief getCorpus
     * @param index
     * @return
     */
    Corpus getCorpus(int index);

    /**
     * @brief setCorporaFrequencyTable
     * @param value
     */
    void setCorporaFrequencyTable(const map<string, int> &value);

    /**
     * @brief getCorporaFrequencyTable
     * @return
     */
    map<string, int> getCorporaFrequencyTable() const;

    /**
     * @brief generateCorporaFrequencyTable
     */
    void generateCorporaFrequencyTable();


    /**
     * @brief threshold
     * @param th
     */
    void threshold(int th);


    /**
     * @brief clear
     */

    void clear();



    /**
     * @brief showCorporaFrequencyTable
     */
    void showCorporaFrequencyTable();

};

#endif // CORPORA_H
