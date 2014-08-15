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

void Preprocesor::removeIlegalAmp()
{
    const regex rgx_url("&");
    string blank(" ");

    fullText=regex_replace(fullText,rgx_url,blank);
}

void Preprocesor::removeHtmlTagsInXML()
{
    const regex rgx_gt("&gt;");
    string gt(" ");

    const regex rgx_lt("&lt;");
    string lt(" ");

    const regex rgx_amp("&amp;");
    string amp(" ");

    const regex rgx_apos("&apos;");
    string apos(" ");

    const regex rgx_quot("&quot;");
    string quot(" ");



    //removiendo caracteres de xml

    fullText=regex_replace(fullText,rgx_gt,gt);
    fullText=regex_replace(fullText,rgx_lt,lt);
    fullText=regex_replace(fullText,rgx_amp,amp);
    fullText=regex_replace(fullText,rgx_apos,apos);
    fullText=regex_replace(fullText,rgx_quot,quot);


}

void Preprocesor::removeSpecialcharacters()
{
    const regex rgx_url("\\032");
    string blank(" ");

    fullText=regex_replace(fullText,rgx_url,blank);
}


void Preprocesor::removeUrls()
{
    const regex rgx_url("((([A-Za-z]{3,9}:(?:\\/\\/)?)(?:[\\-;:&=\\+\\$,\\w]+@)?[A-Za-z0-9\\.\\-]+|(?:www\\.|[\\-;:&=\\+\\$,\\w]+@)[A-Za-z0-9\\.\\-]+)((?:\\/[\\+~%\\/\\.\\w\\-_]*)?\\?\?(?:[\\-\\+=&;%@\\.\\w_]*)#?(?:[\\.\\!\\/\\\\\\w]*))?)");
    string blank("");

    fullText=regex_replace(fullText,rgx_url,blank);

}

void Preprocesor::removePunctiationMarks()
{

    const regex rgx_punctiation("[^\\w\\sáéíóúñ]");
    string blank(" ");


    fullText=regex_replace(fullText,rgx_punctiation,blank);

}

void Preprocesor::removeNumbers()
{
    const regex rgx_numbers("(\\+|-)?[0-9]*(\\.([0-9][0-9]*)?)?((E|e)(\\+|-)?[0-9]+)?");
    string blank("");


    fullText=regex_replace(fullText,rgx_numbers,blank);

}

void Preprocesor::toLower()
{

    transform(fullText.begin(), fullText.end(), fullText.begin(), ::tolower);

}
