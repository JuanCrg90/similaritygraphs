/**
    @file: preprocesor.h
    @author: Juan Carlos Ruiz González (jc.ruiz.gonzalez@ugto.mx)
    @date 8/05/2014
    @brief Class for handling the text corpus
    @version 1.0

**/



#ifndef PREPROCESOR_H
#define PREPROCESOR_H


#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iterator>
#include <boost/regex.hpp>



#define SPANISH 1
#define EN_STD 2
#define EN_LONG 3




using namespace std;
using namespace boost;


/**
 * @brief The Preprocesor class
 */

class Preprocesor
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




public:

    /**
     * @brief Preprocesor Constructor
     */
    Preprocesor();

    /**
     * @brief Preprocesor Constructor
     * @param fullText
     */
    Preprocesor(string fullText);

    /**
     * @brief setText
     * @param fullText
     */
    void setText(string fullText);

    /**
     * @brief getText
     * @return string
     */
    string getText();


    /**
     * @brief remove the html tags from the text
     */
    void removeHtmlTags();

    /**
     * @brief removeUrls
     */
    void removeUrls();


    void removePunctiationMarks();

    /**
     * @brief removeStopWords
     * @param language 1 Spanish, 2 English std, 3 English Long
     */

    void removeStopWords(int language);

    /**
     * @brief removeNumbers
     */
    void removeNumbers();


    /**
     * @brief toLower
     */
    void toLower();










};

#endif // PREPROCESOR_H
