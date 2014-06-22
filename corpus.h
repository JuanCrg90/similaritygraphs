/**
    @file: Corpus.h
    @author: Juan Carlos Ruiz González (jc.ruiz.gonzalez@ugto.mx)
    @date 21/06/2014
    @brief Class for handling the documents
    @version 2.0

**/

#ifndef CORPUS_H
#define CORPUS_H

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <algorithm>


#include "document.h"


using namespace std;

/**
 * @brief The Corpus class
 */

class Corpus
{


private:
    
    string name;
    vector<Document> corp;
    map<string,int> corpusFrequencyTable;
    
    



public:
    /**
     * @brief Corpus constructor
     */
    Corpus();

    /**
     * @brief setName
     * @param name
     */
    void setName(string name);

    /**
     * @brief getName
     * @return
     */
    string getName();

    /**
     * @brief addDocument
     * @param doc
     */
    void addDocument(Document doc);

    /**
     * @brief getDocument
     * @param index
     * @return
     */
    Document getDocument(int index);

    /**
     * @brief generateCorpusFrequencyTable
     */

    void generateCorpusFrequencyTable();

    /**
     * @brief showCorpusFrequencyTable
     */
    void showCorpusFrequencyTable();

    /**
     * @brief getCorpusFrequencyTable
     * @return
     */
    map<string, int> getCorpusFrequencyTable() const;

    /**
     * @brief setCorpusFrequencyTable
     * @param value
     */
    void setCorpusFrequencyTable(const map<string, int> &value);


    /**
     * @brief balanceCorpus: add the non existent words with 0 frequency
     */
    void balanceCorpus();

    /**
     * @brief remove the words in each map under the threshold
     * @param th
     */
    void threshold(int th);







};

#endif // CORPUS_H
