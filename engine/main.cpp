#include "pugixml/src/pugixml.cpp"
#include <iostream>
#include <fstream>      // std::fstream
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main(int argc, char** argv)
{
//TESTE


    std::fstream fs;
    fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    fs << " more lorem ipsum";

    fs.close();



    /*pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("test.xml");

    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;*/




    /*
    // controi um ficheiro xml
    pugi::xml_document doc;

    // tag::code[]
    // add node with some name
    pugi::xml_node node = doc.append_child("node");

    // add description node with text child
    pugi::xml_node descr = node.append_child("description");
    descr.append_child(pugi::node_pcdata).set_value("Simple node");

    // add param node before the description
    pugi::xml_node param = node.insert_child_before("param", descr);

    // add attributes to param node
    param.append_attribute("name") = "version";
    param.append_attribute("value") = 1.1;
    param.insert_attribute_after("type", param.attribute("name")) = "float";
    // end::code[]

    doc.print(fs);

    // save document to file
    //std::cout << "Saving result: " << doc.save_file("save_file_output.xml") << std::endl;*/
}
