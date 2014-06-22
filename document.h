/**
    @file: Document.h
    @author: Juan Carlos Ruiz González (jc.ruiz.gonzalez@ugto.mx)
    @date 21/06/2014
    @brief Class for handling the  Document text
    @version 1.0

**/

#ifndef DOCUMENT_H
#define DOCUMENT_H

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
 * @brief The Document class
 */

class Document
{


private:
    /**
     * @brief tags for tokenize the text
     */
    const string tags = " ,.;:?!#\"()\n\t";

    /**
     * @brief Document name
     */
    string name;

    /**
     * @brief text to handle
     */
    string fullText;

    /**
     * @brief Frequency table of the full text
     */
    map<string,int> frequencyTable;



public:
    /**
     * @brief Document constructor
     */
    Document();


    /**
     * @brief Document construcctor
     * @param name
     * @param fullText
     */

    Document(string name,string fullText);



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
     * @brief generateFrequencyTable
     * @return true or false
     */
    bool generateFrequencyTable();

    /**
     * @brief removeStopWords
     * @param stopW
     */
    void removeStopWords(vector<string> stopW);


    /**
     * @brief showText
     */
    void showText();

    /**
     * @brief setFrequencyTable
     * @param frequencyTable
     */
    void setFrequencyTable(map<string,int> frequencyTable);

    /**
     * @brief getFrequencyTable
     * @return map<string,int>
     */
    map<string,int> getFrequencyTable();



    /**
     * @brief showFrequencyTable
     */
    void showFrequencyTable();


};

#endif // DOCUMENT_H
