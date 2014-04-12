/**
    @file: Corpus.h
    @author: Juan Carlos Ruiz González (jc.ruiz.gonzalez@ugto.mx)
    @date 12/04/2014
    @brief Class for handling the text corpus
    @version 1.0

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


using namespace std;

/**
 * @brief The Corpus class
 */

class Corpus
{


private:
    /**
     * @brief tags for tokenize the text
     */
    const string tags = " ,.;:?!#\"()\n\t";

    /**
     * @brief text to handle
     */
    string fullText;

    /**
     * @brief Frecuency table of the full text
     */
    map<string,int> frecuencyTable;



public:
    /**
     * @brief Corpus constructor
     */
    Corpus();

    /**
     * @brief Corpus constructor
     * @param fullText
     */
    Corpus(string fullText);

    /**
     * @brief setText
     * @param fullText
     */
    void setText(string fullText);

    /**
     * @brief getText
     * @return fullText
     */
    string getText();

    /**
     * @brief generateFrecuencyTable
     * @return true or false
     */
    bool generateFrecuencyTable();

    /**
     * @brief showText
     */
    void showText();

    /**
     * @brief showFrecuencyTable
     */
    void showFrecuencyTable();


};

#endif // CORPUS_H
