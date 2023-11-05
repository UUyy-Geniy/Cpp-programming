#include "XML_resource.h"


int main() {
    /*XML_document* doc = new XML_document();

    doc->load("./test.txt");
    doc->print();*/

    auto T = XML_resource::create();
    T->load("./test.txt");
    T->print();
    T->save("./save_test.xml");

    return 0;
};