#include <iostream>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

int main()
{
    XMLDocument doc;

    /************************************************************************
                            Wrong File Demostration
    ************************************************************************/
    const int error_num = 6;
    std::string file_name[error_num] = {
        "a_normal_one.xml",
        "no_such_file.xml",
        "wrong_attribute_format.xml",
        "empty.xml",
        "wrong_end_tag.xml",
        "lack_end_tag.xml"};

    for (int i = 0; i < error_num; i++)
    {
        std::cout << "File name: " << file_name[i] << std::endl;
        doc.LoadFile(("error_demostrating_file/" + file_name[i]).c_str());
        if (doc.Error())
        {
            doc.PrintError();
        }
        else
        {
            std::cout << "No error detected\n";
        }
    }
    std::cout << "-------------------------\n";
    /************************************************************************
                            Wrong Query Demostration
    ************************************************************************/
    doc.LoadFile("error_demostrating_file/a_normal_one.xml");
    std::cout << "Wrong Atrribute Name Test" << std::endl;
    XMLElement *node = doc.FirstChildElement("breakfast_menu");
    int value = 0;
    XMLError errorID = node->QueryIntAttribute("price", &value);
    if (errorID)
    {
        std::cout << "Error: " << XMLDocument::ErrorIDToName(errorID) << "\n";
    }
    else
    {
        std::cout << "No error detected\n";
    }
    std::cout << "Wrong Atrribute Type Test" << std::endl;
    errorID = node->QueryIntAttribute("target", &value);
    if (errorID)
    {
        std::cout << "Error: " << XMLDocument::ErrorIDToName(errorID) << "\n";
    }
    else
    {
        std::cout << "No error detected\n";
    }
    std::cout << "No Text Error Test" << std::endl;
    errorID = node->QueryIntText(&value);
    if (errorID)
    {
        std::cout << "Error: " << XMLDocument::ErrorIDToName(errorID) << "\n";
    }
    else
    {
        std::cout << "No error detected\n";
    }
    return 0;
}