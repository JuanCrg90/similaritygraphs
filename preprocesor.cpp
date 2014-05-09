#include "preprocesor.h"

Preprocesor::Preprocesor()
{

}

Preprocesor::Preprocesor(string fullText)
{
    this->fullText=fullText;
}

void Preprocesor::setText(string fullText)
{
    this->fullText=fullText;
}

string Preprocesor::getText()
{
    return fullText;
}

void Preprocesor::removeHtmlTags()
{


    const regex rgx_gt("&gt;");
    string gt(">");

    const regex rgx_lt("&lt;");
    string lt("<");

    const regex rgx_amp("&amp;");
    string amp("&");

    const regex rgx_apos("&apos;");
    string apos("\'");

    const regex rgx_quot("&quot;");
    string quot("\"");


    const regex rgx_html("<[^>]*>");
    string blank("");


    //conviertiendo caracteres de xml a html

    fullText=regex_replace(fullText,rgx_gt,gt);
    fullText=regex_replace(fullText,rgx_lt,lt);
    fullText=regex_replace(fullText,rgx_amp,amp);
    fullText=regex_replace(fullText,rgx_apos,apos);
    fullText=regex_replace(fullText,rgx_quot,quot);

    //removiendo toda cadena html
    fullText=regex_replace(fullText,rgx_html,blank);

}

void Preprocesor::removeUrls()
{
    const regex rgx_url("((https?|s?ftp|ssh|):\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$");
    string blank("");

    fullText=regex_replace(fullText,rgx_url,blank);

    cout<<fullText<<endl;

}

void Preprocesor::removePunctiationMarks()
{

    const regex rgx_punctiation("[^\\w\\s]");
    string blank(" ");


    fullText=regex_replace(fullText,rgx_punctiation,blank);

    cout<<fullText<<endl;

}

void Preprocesor::removeStopWords(int language)
{

}

void Preprocesor::removeNumbers()
{

}

void Preprocesor::toLower()
{

}
