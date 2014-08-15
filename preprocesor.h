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
#include <algorithm>
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
     * @brief removeIlegalAmp
     * &[^(lt|gt|apos|amp|quot)]+
     * [\S]&[\S|\s]
     */
    void removeIlegalAmp();

    void removeHtmlTagsInXML();

    /**
     * @brief removeSpecialcharacters
     * \032
     */
    void removeSpecialcharacters();


    /**
     * @brief removeUrls
     */
    void removeUrls();

    /**
     * @brief removePunctiationMarks
     * [^\w\sáéíóúñ]
     */

    void removePunctiationMarks();

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
