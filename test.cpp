#include <iostream>
#include <iomanip>
#include <string>
#include "tinyxml2.h"

// Classes, varibles and functions are declared in the namespace of tinyxml2
using namespace tinyxml2;

void readxml_example()
{
    // Create an object to contain the overall xml document
    XMLDocument doc;
    /**
        Load XML File from disk.
        Can also use Parse(const char* xml, size_t nBytes=static_cast<size_t>(-1)) to load xml file from string.
        @verbatim
        static const char* xml =
            "<?xml version=\"1.0\"?>"
            "<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
            "<PLAY>"
            "<TITLE>A Midsummer Night's Dream</TITLE>"
            "</PLAY>";
        doc.Parse( xml );
        @endverbatim
        or use LoadFile( FILE* ) to load file from a FILE pointer
    */
    doc.LoadFile("source.xml");
    // XMLHandle can safely handle error (so no need to have a bunch of if(){}...) and safe to copy.
    XMLHandle docHandle(&doc);

    // Output each type of node to demostrate doc have loaded everything
    // use FirstChildElement() or RootElement() to get the root element of an xml file
    XMLElement *rootchild = docHandle.FirstChildElement().ToElement();
    if (rootchild)
    {
        // get Element's name
        std::cout << "   " << rootchild->Name() << "   \n";
        // Get 2 Attributes' name and value;
        const char *Attri_name_1 = rootchild->FirstAttribute()->Name();
        std::cout << "   " << Attri_name_1 << " : " << rootchild->Attribute(Attri_name_1) << std::endl;
        const char *Attri_name_2 = rootchild->FirstAttribute()->Next()->Name();
        std::cout << "   " << Attri_name_2 << " : " << rootchild->Attribute(Attri_name_2) << std::endl;
    }
    std::cout << "-------------------------\n";
    // get child element from root
    XMLElement *foodchild = docHandle.FirstChildElement().FirstChildElement("food").ToElement();
    for (int i = 1;; i++)
    {
        if (foodchild) // To avoid invalid memory access
        {
            std::cout << "Food " << i << "   ";
            // get attribute names
            const char *food_attri = foodchild->FirstAttribute()->Name();
            // IntAttribute return integer form of attribute (Notice that all attributes' value should be given in a string form)
            std::cout << food_attri << " : " << foodchild->IntAttribute(food_attri) << std::endl;
            XMLElement *childelement;
            // output child elements' tag and content of food
            for (childelement = foodchild->FirstChildElement(); childelement != foodchild->LastChildElement(); childelement = childelement->NextSiblingElement())
            {
                std::cout << std::setw(12) << std::right << childelement->Name() << " : " << childelement->GetText() << std::endl;
            }
            std::cout << std::setw(12) << std::right << childelement->Name() << " : " << childelement->GetText() << std::endl;
        }
        else
        {
            break;
        }
        foodchild = foodchild->NextSiblingElement();
        std::cout << "-------------------------\n";
    }
}

void writexml_example()
{
    // Create a blank xml document
    XMLDocument doc;
    // Create a declaration node
    XMLDeclaration *decl = doc.NewDeclaration();
    // Add declaration node to the document
    doc.InsertFirstChild(decl);
    // Create a root element
    XMLElement *root = doc.NewElement("root_element");
    // Add the root element to the document
    doc.InsertEndChild(root);
    // Create a child element
    XMLElement *child = doc.NewElement("child_element_1");
    // Add the child element to the root element
    root->InsertFirstChild(child);
    // Add Text content for child
    /**
        can also use:
        @verbatim
        XMLText *text = doc.NewText("This is a text content");
        child->InsertFirstChild(text);
        @endverbatim
        to set text content
    */
    child->SetText("This is a text content");
    // Create another child element
    XMLElement *child2 = doc.NewElement("child_element_2");
    // Add the child element after the first child element
    root->InsertAfterChild(child, child2);
    // Add Attribute for root
    root->SetAttribute("root_attribute", "root_attribute_value");
    // Add Comment for root
    /**
        The following 2 lines can be replaced by:
        @verbatim
        XMLComment *comment = root->InsertNewComment("This is a comment")
        @endverbatim
        however it'll be add the end of the root element
     */
    XMLComment *comment = doc.NewComment("This is a comment");
    root->InsertFirstChild(comment);
    // Print the xml document
    doc.Print();
    // Delete a child element
    root->DeleteChild(child2);
    // Delete comment from root
    root->DeleteChild(comment);
    // Save the xml document to a file
    doc.SaveFile("destination.xml");
}

int main()
{
    // Read part of the example
    readxml_example();
    // Write part of the example
    writexml_example();
    return 0;
}